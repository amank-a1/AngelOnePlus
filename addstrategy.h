#ifndef ADDSTRATEGY_H
#define ADDSTRATEGY_H

#include <QDialog>

namespace Ui {
class AddStrategy;
}

class AddStrategy : public QDialog
{
    Q_OBJECT

public:
    explicit AddStrategy(QWidget *parent = nullptr);
    ~AddStrategy();

signals:
    emit void UpdateData(QStringList);
private slots:
    void on_submit_clicked();

private:
    Ui::AddStrategy *ui;
};

#endif // ADDSTRATEGY_H
