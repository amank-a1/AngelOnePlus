#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionDownload_DSM_triggered();

    void on_scripSubmit_clicked();

    void listStrategies();

    void on_createStrategy_clicked();

    void UpdateStategy(QStringList list);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
