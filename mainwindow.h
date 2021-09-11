#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString fileString;
    QStandardItemModel *csvModel;
    QVector<double> dataX;
    QVector<QVector<double>> dataY;

    QMenu* priceMenu;
    QAction* openAct;
    QAction* highAct;
    QAction* lowAct;
    QAction* closeAct;
    QAction* adjCloseAct;
    QAction* volumeAct;

    QMenu* maMenu;
    QAction* ma5Act;
    QAction* ma10Act;
    QAction* ma20Act;
    QAction* ma30Act;
    QAction* ma60Act;
    QAction* ma120Act;

    QMenu* emaMenu;
    QAction* ema5Act;
    QAction* ema10Act;
    QAction* ema20Act;
    QAction* ema30Act;
    QAction* ema60Act;
    QAction* ema120Act;

    QMenu* macdMenu;
    QAction* macdAct;
    QAction* macdSignalAct;

    QMenu* bollMenu;
    QAction* bollAct;
    QAction* boolUpperAct;
    QAction* boolLowerAct;

    QMenu* kdjMenu;
    QAction* kdjKAct;
    QAction* kdjDAct;
    QAction* kdjJAct;

    QMenu* rsiMenu;
    QAction* rsi6Act;
    QAction* rsi12Act;
    QAction* rsi24Act;

    QAction* checkAll;
    QAction* uncheckAll;

    void loadCSV();
    void drawIndicator(int col);

private slots:
    void openCSV();
    void checkAllAction();
    void uncheckAllAction();
    void updatePlot(QAction* oAction);
    void mousePress();
    void mouseWheel();
    void selectionChanged();
};
#endif // MAINWINDOW_H
