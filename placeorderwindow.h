#ifndef PLACEORDERWINDOW_H
#define PLACEORDERWINDOW_H

#include <QDialog>
#include <orderwidget.h>
#include <vector>

namespace Ui {
class PlaceOrderWindow;
}

typedef struct mCalculateMarginArray{
    QString Exchange;
    QString Token;
    int Quantity;
    QString TradeType;
}CalculateMarginArray;

class PlaceOrderWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PlaceOrderWindow(QWidget *parent = nullptr);
    ~PlaceOrderWindow();
    int mBuyOrderCount;
    int mSellOrderCount;
    int mExampleCode;
    QString mStrategyName;


    std::vector<CalculateMarginArray> mMarginArrayList;

    void setDetailsToUI();
    void showExample(int code);
    void showExampleCustom();

private slots:
    void on_calculateBtn_clicked();

    void on_calculateBtn_pressed();

private:
    Ui::PlaceOrderWindow *ui;
};

#endif // PLACEORDERWINDOW_H
