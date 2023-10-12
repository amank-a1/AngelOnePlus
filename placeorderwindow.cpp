#include "placeorderwindow.h"
#include "ui_placeorderwindow.h"
#include <QGridLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtCharts>

PlaceOrderWindow::PlaceOrderWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlaceOrderWindow)
{
    ui->setupUi(this);
    connect(ui->calculateBtn,SIGNAL(clicked(bool)),SLOT(on_calculateBtn_clicked()));
}

PlaceOrderWindow::~PlaceOrderWindow()
{
    delete ui;
}

void PlaceOrderWindow::setDetailsToUI()
{
    ui->strategyname->setText(mStrategyName);

    int totalOrderCount = mBuyOrderCount + mSellOrderCount;
    QGridLayout *layout = new QGridLayout(ui->widget);

    //42705 - NIFTY09NOV2319500CE
    //42734 - NIFTY09NOV2319700CE
    //42667 - NIFTY09NOV2319200PE

    QStringList stockList;
    stockList.append("42705");
    stockList.append("42734");
    stockList.append("42667");
    stockList.append("44435");

    OrderWidget *ow[stockList.size()];

    for (int i = 0 ; i < totalOrderCount ; i++)
    {
        int randomValue = rand() % 100;
        CalculateMarginArray marginarray;
        ow[i] = new OrderWidget(this);
        if (i < mBuyOrderCount)
        {
            ow[i]->mTypeName = "Buy";
            ow[i]->mExchSeg = "NFO";
            ow[i]->mSymbol = "NIFTY09NOV2319500CE";
            ow[i]->mQuantity = "50";
            ow[i]->mPrice = QString::number(randomValue);
            ow[i]->mToken = stockList[i];
            ow[i]->setColor("background-color: blue");
            ow[i]->setDetails();
            marginarray.Exchange = ow[i]->mExchSeg;
            marginarray.Token = ow[i]->mToken;
            marginarray.TradeType = "BUY";
            marginarray.Quantity = ow[i]->mQuantity.toInt();

        } else {
            ow[i]->mTypeName = "Sell";
            ow[i]->mExchSeg = "NFO";
            ow[i]->mSymbol = "NIFTY09NOV2319200PE";
            ow[i]->mQuantity = "50";
            ow[i]->mPrice = QString::number(randomValue);
            ow[i]->mToken = stockList[i];
            ow[i]->setColor("background-color: red");
            ow[i]->setDetails();
            marginarray.Exchange = ow[i]->mExchSeg;
            marginarray.Token = ow[i]->mToken;
            marginarray.TradeType = "SELL";
            marginarray.Quantity = ow[i]->mQuantity.toInt();
        }

        mMarginArrayList.push_back(marginarray);

        layout->addWidget(ow[i]);
    }

    ui->widget->setLayout(layout);
    return;
}

void PlaceOrderWindow::showExample(int code)
{
    QChartView *chartView = new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);

    auto low = new QBarSet("Min");
    auto high = new QBarSet("Max");

    QColor colorGreen("green");
    QColor colorRed("red");
    low->setColor(colorRed);
    high->setColor(colorGreen);

    int currentStkPrice = 19500;
    int stepCount = 50;

    double arr[41] = {0};

    arr[20] = currentStkPrice;

    for (int i = 20 ; i < 41 ;i++)
    {
        if (i == 20)
            continue;
        arr[i] = arr[i-1]+stepCount;
    }
    for (int i = 20 ; i >= 0 ;i--)
    {
        if (i == 20)
            continue;
        arr[i] = arr[i+1]-stepCount;
    }

    int lowRange,highRange;

    if (code == 0)
    {
        *low << -340<<-290<<-240<<-190<<-140<<-90<<-40<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<-40<<-90<<-140;
        *high << 0<<0<<0<<0<<0<<0<<0<<10<<60<<110<<160<<210<<260<<310<<360<<410<<460<<510<<560<<610<<660<<710<<760<<710<<660<<610<<560<<510<<460<<410<<360<<310<<260<<210<<160<<110<<60<<10<<0<<0<<0;

        highRange = 800;
        lowRange = 0-highRange;
    }
    else if (code == 1)
    {
        *low << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<-4<<-54<<-104<<-154<<-204<<-254<<-304;
        *high << 196<<196<<196<<196<<196<<196<<196<<196<<196<<196<<196<<196<<196<<196<<196<<246<<296<<346<<396<<446<<496<<546<<596<<546<<496<<446<<396<<346<<296<<246<<196<<146<<96<<46<<0<<0<<0<<0<<0<<0<<0;

        highRange = 600;
        lowRange = 0-highRange;
    }
    else if (code == 2)
    {
        *low << -400<<-400<<-400<<-400<<-400<<-400<<-400<<-400<<-400<<-400<<-400<<-400<<-400<<-400<<-400<<-400<<-400<<-350<<-300<<-250<<-200<<-150<<-100<<-50<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0;
        *high << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<50<<100<<150<<200<<250<<300<<350<<400<<450<<500<<550<<600<<650<<700<<750<<800;

        highRange = 850;
        lowRange = 0-highRange;
    }
    else if (code == 4)
    {
        *low << -400<<-400<<-400<<-400<<-400<<-400<<-400<<-400<<-400<<-400<<-400<<-400<<-400<<-400<<-400<<-400<<-400<<-350<<-300<<-250<<-200<<-150<<-100<<-50<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0;
        *high << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<50<<100<<150<<200<<250<<300<<350<<400<<450<<500<<550<<600<<650<<700<<750<<800;

        highRange = 850;
        lowRange = 0-highRange;
    }
    else {
        *low <<0;
        *high << 0;

        highRange = 0;
        lowRange = 0-highRange;
    }


    auto series = new QStackedBarSeries;
    series->append(low);
    series->setLabelsVisible(true);
    series->setLabelsAngle(-90);
    series->setLabelsFormat("@value");
    series->append(high);


    auto chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("Payoff Graph");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    for (int i =0 ; i < 41 ; i++)
    {
        categories.append(QString::number(arr[i]));
    }

    auto axisX = new QBarCategoryAxis;
    axisX->append(categories);
    axisX->setTitleText("Strike Prices");
    axisX->setLabelsAngle(-90);
    chart->addAxis(axisX, Qt::AlignBottom);
    auto axisY = new QValueAxis;
    axisY->setRange(lowRange, highRange);
    axisY->setTitleText("Profit Amount");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView->setChart(chart);

    QGridLayout *gl = new QGridLayout(ui->chart);
    gl->addWidget(chartView,0,0);
    ui->chart->setLayout(gl);
}


void PlaceOrderWindow::showExampleCustom()
{

}

void PlaceOrderWindow::on_calculateBtn_clicked()
{
    QJsonObject jsonObj;
    QJsonArray positionArray;

    for (int i = 0 ; i < mMarginArrayList.size() ; i++)
    {
        QJsonObject position;
        position["exchange"] = mMarginArrayList[i].Exchange;
        position["qty"] = mMarginArrayList[i].Quantity;
        position["token"] = mMarginArrayList[i].Token;
        position["tradeType"] = mMarginArrayList[i].TradeType;

        positionArray.append(position);
    }

    jsonObj["position"] = positionArray;

    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl("https://margin-calc-arom-prod.angelbroking.com/margin-calculator/SPAN"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = QJsonDocument(jsonObj).toJson();
    qDebug()<<data;

    QEventLoop loop;
    QNetworkReply *reply = manager.post(request, data);
    QObject::connect(reply, &QNetworkReply::finished, &loop,&QEventLoop::quit);
    loop.exec();
    QByteArray m_buffer;
    if(reply->error() == QNetworkReply::NoError){
        m_buffer = reply->readAll();
    }
    reply->deleteLater();

    qDebug()<<m_buffer;

    QJsonDocument jsonResponseDocument = QJsonDocument::fromJson(m_buffer);
    QJsonObject jsonObject = jsonResponseDocument.object();

    QJsonObject marginObject = jsonObject["margin"].toObject();
    double netPremium = marginObject["netPremium"].toDouble();
    double totalMargin = marginObject["totalMargin"].toDouble();
    double marginbenefit = marginObject["marginBenefit"].toDouble();

    QJsonArray positionMarginArray = jsonObject["positionMargin"].toArray();


    ui->netPremium->setText(QString::number(netPremium));
    ui->totalMargin->setText(QString::number(netPremium));
    ui->marginBenefit->setText(QString::number(marginbenefit));

    switch (mExampleCode) {
    case 0:
        showExample(mExampleCode);
        break;
    case 1:
        showExample(mExampleCode);
        break;
    case 2:
        showExample(mExampleCode);
        break;
    case 4:
        showExample(mExampleCode);
        break;
    default:
        showExampleCustom();
        break;
    }
}


void PlaceOrderWindow::on_calculateBtn_pressed()
{
    qDebug()<<"clicked";
}

