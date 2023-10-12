#include "orderwidget.h"
#include "ui_orderwidget.h"

OrderWidget::OrderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderWidget)
{
    ui->setupUi(this);
}

OrderWidget::~OrderWidget()
{
    delete ui;
}

void OrderWidget::setDetails()
{
    ui->type->setText(mTypeName);
    ui->exchSeg->setText(mExchSeg);
    ui->symbol->setText(mSymbol);
    ui->quantity->setText(mQuantity);
    ui->token->setText(mToken);
    ui->price->setText(mPrice);
}

void OrderWidget::setColor(QString color)
{
    ui->color->setStyleSheet(color);
}
