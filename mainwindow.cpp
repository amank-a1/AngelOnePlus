#include "mainwindow.h"
#include "QtCore/qforeach.h"
#include "QtCore/qobjectdefs.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <MainHeaders.h>
#include <map>
#include <QRegularExpression>
#include <placeorderwindow.h>
#include <addstrategy.h>

std::map<QString,std::map<QString,ScripMaster>> scripMasterExchangeWise;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->OIChainTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
    listStrategies();
    ui->createStrategy->setDefault(true);
    ui->scripSubmit->setDefault(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionDownload_DSM_triggered()
{
    QString val;
    QFile file;

    file.setFileName(":/OpenAPIScripMaster.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonArray maps = QJsonDocument::fromJson(val.toUtf8()).array();

    foreach (const QJsonValue & v, maps){
        QString exchangeName = v.toObject().value("exch_seg").toString();

        std::map<QString,ScripMaster> symbol;
        ScripMaster s;
        s.ExchangeSeg = v.toObject().value("exch_seg").toString();
        s.Expiry = v.toObject().value("expiry").toString();
        s.InstrumentType = v.toObject().value("instrumenttype").toString();
        s.LotSize = v.toObject().value("lotsize").toString();
        s.Name = v.toObject().value("name").toString();
        s.StrikePrice = v.toObject().value("strike").toString();
        s.Symbol = v.toObject().value("symbol").toString();
        s.TickSize = v.toObject().value("tick_size").toString();
        s.Token = v.toObject().value("token").toString();

        s.StrikePrice.remove( QRegularExpression("\\.?0+$") );

        symbol[v.toObject().value("token").toString()] = s;

        auto itr = scripMasterExchangeWise.find(exchangeName);

        if (itr == scripMasterExchangeWise.end()) {
            scripMasterExchangeWise.insert({exchangeName, symbol});
            qDebug()<<exchangeName;
        }
        else
        {
            itr->second[v.toObject().value("token").toString()] = s;
        }
    }

    qDebug()<<scripMasterExchangeWise.size();

    return;
}



void MainWindow::on_scripSubmit_clicked()
{
    //    QString scripName = ui->scripSearch->text();
    //    std::map<QString,bool> list;
    //    ui->OIChainTable->setRowCount(0);
    //    for (auto itr = scripMasterExchangeWise.begin(); itr != scripMasterExchangeWise.end(); itr++)
    //    {
    //        if (itr->first == ui->comboExchange->currentText()){
    //            for (auto itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++)
    //            {
    //                if (itr2->second.Name == scripName){
    //                    if(itr2->second.StrikePrice == "-1")
    //                        continue;
    //                    list[itr2->second.StrikePrice] = true;
    //                }

    //            }
    //        }
    //    }

    //    qDebug()<<list.size();
    //    ui->OIChainTable->setRowCount(list.size());

    //    int row = 0;
    //    for (auto itr = list.begin() ; itr != list.end();itr++)
    //    {
    //        qDebug()<<itr->first;
    //        int strikePrice = itr->first.toInt()/100;
    //        ui->OIChainTable->setItem(row,0,new QTableWidgetItem(""));
    //        ui->OIChainTable->setItem(row,1,new QTableWidgetItem(QString::number(strikePrice)));
    //        ui->OIChainTable->setItem(row,2,new QTableWidgetItem(""));
    //        row++;
    //    }

    QFile file(":/SymbolDetails.csv");

    QString data;
    QStringList rowOfData;
    QStringList rowData;
    data.clear();
    rowOfData.clear();
    rowData.clear();

    if (file.open(QFile::ReadOnly))
    {
        data = file.readAll();
        rowOfData = data.split("\n");  //Value on each row
        file.close();
    }

    int r=rowOfData.size();
    ui->OIChainTable->setRowCount(r);

    for (int x = 0; x < rowOfData.size(); x++)   //rowOfData.size() gives the number of row
    {
        rowData = rowOfData.at(x).split("|");  //Number of collumn

        ui->OIChainTable->setItem(x,0,new QTableWidgetItem(rowData[0]));
        ui->OIChainTable->setItem(x,1,new QTableWidgetItem(rowData[1]));
        ui->OIChainTable->setItem(x,2,new QTableWidgetItem(rowData[2]));

    }

    for (int i = 0 ; i < ui->OIChainTable->rowCount();i++)
    {
        int strikePrice = ui->OIChainTable->item(i,1)->text().toFloat();
        if (strikePrice > ui->nifty->text().toFloat()){
            ui->OIChainTable->selectRow(i);
            ui->OIChainTable->selectedItems();
            break;
        }
    }
}

void MainWindow::listStrategies()
{
    ui->strategyTreeWidget->header()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->strategyTreeWidget->header()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    ui->strategyTreeWidget->expandAll();

    for(int i = 0 ; i < ui->strategyTreeWidget->topLevelItemCount() ; i++)
    {
        QTreeWidgetItem *item = ui->strategyTreeWidget->topLevelItem(i);
        if ( item->childCount() > 0 )
        {
            for (int j = 0 ; j < item->childCount() ; j++)
            {
                QTreeWidgetItem *childitem = item->child(2);
                QPushButton *placeOrder = new QPushButton("Place Order");
                placeOrder->setDefault(true);

                ui->strategyTreeWidget->setItemWidget(childitem,1,placeOrder);

                connect(placeOrder,&QPushButton::clicked,[item,i](){

                    int buyOrder = item->child(0)->text(1).toInt();
                    int sellOrder = item->child(1)->text(1).toInt();
                    QString strategyName = item->text(0);

                    PlaceOrderWindow placeorder;
                    placeorder.mBuyOrderCount = buyOrder;
                    placeorder.mSellOrderCount = sellOrder;
                    placeorder.mStrategyName = strategyName;
                    placeorder.mExampleCode = i;

                    placeorder.setDetailsToUI();
                    placeorder.exec();
                });
            }
        }
    }
}

void MainWindow::on_createStrategy_clicked()
{
    AddStrategy as;
    connect(&as,SIGNAL(UpdateData(QStringList)),this,SLOT(UpdateStategy(QStringList)));
    as.exec();
}

void MainWindow::UpdateStategy(QStringList list)
{
    qDebug()<<"TTT";
    QTreeWidgetItem *item = new QTreeWidgetItem();

    item->setText(0,list[0]);
    item->setText(1,list[1]);
    QLabel *buy = new QLabel("CE/PE Buy Orders");
    QLabel *sell = new QLabel("CE/PE Sell Orders");
    QLabel *buyQty = new QLabel(list[2]);
    QLabel *sellQty = new QLabel(list[3]);

    QTreeWidgetItem *childItem1 = new QTreeWidgetItem();
    QTreeWidgetItem *childItem = new QTreeWidgetItem();
    QTreeWidgetItem *childItemPO = new QTreeWidgetItem();

    item->addChild(childItem);
    item->addChild(childItem1);
    item->addChild(childItemPO);

    ui->strategyTreeWidget->setItemWidget(childItem, 0, buy);
    ui->strategyTreeWidget->setItemWidget(childItem1, 0, sell);

    ui->strategyTreeWidget->setItemWidget(childItem, 1, buyQty);
    ui->strategyTreeWidget->setItemWidget(childItem1, 1, sellQty);


    QPushButton *placeOrder = new QPushButton("Place Order");
    placeOrder->setDefault(true);
    ui->strategyTreeWidget->setItemWidget(childItemPO, 0, new QLabel("Action"));
    ui->strategyTreeWidget->setItemWidget(childItemPO,1,placeOrder);

    ui->strategyTreeWidget->addTopLevelItem(item);
    ui->strategyTreeWidget->expandAll();
    connect(placeOrder,&QPushButton::clicked,[item,list](){

        int buyOrder = list[2].toInt();
        int sellOrder = list[3].toInt();
        QString strategyName = list[0];

        PlaceOrderWindow placeorder;
        placeorder.mBuyOrderCount = buyOrder;
        placeorder.mSellOrderCount = sellOrder;
        placeorder.mStrategyName = strategyName;
        placeorder.mExampleCode = 4;

        placeorder.setDetailsToUI();
        placeorder.exec();
    });
}

