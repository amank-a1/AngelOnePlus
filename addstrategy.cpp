#include "addstrategy.h"
#include "ui_addstrategy.h"

AddStrategy::AddStrategy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStrategy)
{
    ui->setupUi(this);
}

AddStrategy::~AddStrategy()
{
    delete ui;
}

void AddStrategy::on_submit_clicked()
{
    QStringList list;
    list.append(ui->strategyName->text());
    list.append(ui->strategyDesc->text());
    list.append(ui->buy->text());
    list.append(ui->sell->text());

    emit UpdateData(list);
    close();
}

