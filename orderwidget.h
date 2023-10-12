#ifndef ORDERWIDGET_H
#define ORDERWIDGET_H

#include <QWidget>

namespace Ui {
class OrderWidget;
}

class OrderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrderWidget(QWidget *parent = nullptr);
    ~OrderWidget();
    QString mTypeName;

    QString mExchSeg;
    QString mSymbol;
    QString mQuantity;
    QString mToken;
    QString mPrice;

    void setDetails();
    void setColor(QString color);

private:
    Ui::OrderWidget *ui;
};

#endif // ORDERWIDGET_H
