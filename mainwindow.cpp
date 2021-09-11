#include "mainwindow.h"
#include "./ui_mainwindow.h"

//#include<QSqlDatabase>
//#include<QSqlQuery>
#include <QFile>
#include <QTextStream>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen_CSV_File, SIGNAL(triggered()), this, SLOT(openCSV()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

//    checkAll = new QAction(tr("Show All"), this);
//    uncheckAll = new QAction(tr("Hide All"), this);
//    ui->menuStock_Indicators->addAction(checkAll);
//    ui->menuStock_Indicators->addAction(uncheckAll);

    connect(ui->actionShow_All, SIGNAL(triggered()), this, SLOT(checkAllAction()));
    connect(ui->actionHide_All, SIGNAL(triggered()), this, SLOT(uncheckAllAction()));


    fileString = "";



    priceMenu = new QMenu(tr("Price"), this);
    openAct = new QAction("Open", this);
    highAct = new QAction("High", this);
    lowAct = new QAction("Low", this);
    closeAct = new QAction("Close", this);
    adjCloseAct = new QAction("Adj Close", this);
    volumeAct = new QAction("Vomune", this);

    openAct->setCheckable(true);
    highAct->setCheckable(true);
    lowAct->setCheckable(true);
    closeAct->setCheckable(true);
    adjCloseAct->setCheckable(true);
    volumeAct->setCheckable(true);

    openAct->setChecked(true);
    highAct->setChecked(false);
    lowAct->setChecked(false);
    closeAct->setChecked(false);
    adjCloseAct->setChecked(false);
    volumeAct->setChecked(false);

    priceMenu->addAction(openAct);
    priceMenu->addAction(highAct);
    priceMenu->addAction(lowAct);
    priceMenu->addAction(closeAct);
    priceMenu->addAction(adjCloseAct);
    priceMenu->addAction(volumeAct);

    ui->menuStock_Indicators->addMenu(priceMenu);

    maMenu = new QMenu(tr("Moving Average (MA)"), this);
    ma5Act = new QAction(tr("5 days"), this);
    ma10Act = new QAction(tr("10 days"), this);
    ma20Act = new QAction(tr("20 days"), this);
    ma30Act = new QAction(tr("30 days"), this);
    ma60Act = new QAction(tr("60 days"), this);
    ma120Act = new QAction(tr("120 days"), this);

    ma5Act->setCheckable(true);
    ma10Act->setCheckable(true);
    ma20Act->setCheckable(true);
    ma30Act->setCheckable(true);
    ma60Act->setCheckable(true);
    ma120Act->setCheckable(true);

    ma5Act->setChecked(false);
    ma10Act->setChecked(false);
    ma20Act->setChecked(false);
    ma30Act->setChecked(false);
    ma60Act->setChecked(false);
    ma120Act->setChecked(false);

    maMenu->addAction(ma5Act);
    maMenu->addAction(ma10Act);
    maMenu->addAction(ma20Act);
    maMenu->addAction(ma30Act);
    maMenu->addAction(ma60Act);
    maMenu->addAction(ma120Act);

    ui->menuStock_Indicators->addMenu(maMenu);

    emaMenu = new QMenu(tr("Exponential Moving Average (EMA)"), this);
    ema5Act = new QAction(tr("5 days"), this);
    ema10Act = new QAction(tr("10 days"), this);
    ema20Act = new QAction(tr("20 days"), this);
    ema30Act = new QAction(tr("30 days"), this);
    ema60Act = new QAction(tr("60 days"), this);
    ema120Act = new QAction(tr("120 days"), this);

    ema5Act->setCheckable(true);
    ema10Act->setCheckable(true);
    ema20Act->setCheckable(true);
    ema30Act->setCheckable(true);
    ema60Act->setCheckable(true);
    ema120Act->setCheckable(true);

    ema5Act->setChecked(false);
    ema10Act->setChecked(false);
    ema20Act->setChecked(false);
    ema30Act->setChecked(false);
    ema60Act->setChecked(false);
    ema120Act->setChecked(false);

    emaMenu->addAction(ema5Act);
    emaMenu->addAction(ema10Act);
    emaMenu->addAction(ema20Act);
    emaMenu->addAction(ema30Act);
    emaMenu->addAction(ema60Act);
    emaMenu->addAction(ema120Act);

    ui->menuStock_Indicators->addMenu(emaMenu);



    macdMenu = new QMenu(tr("Moving Average Convergence Divergence (MACD)"), this);
    macdAct = new QAction(tr("MACD"), this);
    macdSignalAct = new QAction(tr("MACD Signal Band"), this);

    macdAct->setCheckable(true);
    macdSignalAct->setCheckable(true);

    macdAct->setChecked(false);
    macdSignalAct->setChecked(false);

    macdMenu->addAction(macdAct);
    macdMenu->addAction(macdSignalAct);

    ui->menuStock_Indicators->addMenu(macdMenu);



    bollMenu = new QMenu(tr("BOLLinger Bands"), this);
    bollAct = new QAction(tr("BOLL"), this);
    boolUpperAct = new QAction(tr("BOLL Upper Band"), this);
    boolLowerAct = new QAction(tr("BOLL Lower Band"), this);

    bollAct->setCheckable(true);
    boolUpperAct->setCheckable(true);
    boolLowerAct->setCheckable(true);

    bollAct->setChecked(false);
    boolUpperAct->setChecked(false);
    boolLowerAct->setChecked(false);

    bollMenu->addAction(bollAct);
    bollMenu->addAction(boolUpperAct);
    bollMenu->addAction(boolLowerAct);

    ui->menuStock_Indicators->addMenu(bollMenu);



    kdjMenu = new QMenu(tr("KDJ"), this);
    kdjKAct = new QAction(tr("KDJ-K"), this);
    kdjDAct = new QAction(tr("KDJ-D"), this);
    kdjJAct = new QAction(tr("KDJ-J"), this);

    kdjKAct->setCheckable(true);
    kdjDAct->setCheckable(true);
    kdjJAct->setCheckable(true);

    kdjKAct->setChecked(false);
    kdjDAct->setChecked(false);
    kdjJAct->setChecked(false);

    kdjMenu->addAction(kdjKAct);
    kdjMenu->addAction(kdjDAct);
    kdjMenu->addAction(kdjJAct);

    ui->menuStock_Indicators->addMenu(kdjMenu);

    rsiMenu = new QMenu(tr("Raw Stochahstic Value (RSV)"), this);
    rsi6Act = new QAction(tr("6 days"), this);
    rsi12Act = new QAction(tr("12 days"), this);
    rsi24Act = new QAction(tr("24 days"), this);

    rsi6Act->setCheckable(true);
    rsi12Act->setCheckable(true);
    rsi24Act->setCheckable(true);

    rsi6Act->setChecked(false);
    rsi12Act->setChecked(false);
    rsi24Act->setChecked(false);

    rsiMenu->addAction(rsi6Act);
    rsiMenu->addAction(rsi12Act);
    rsiMenu->addAction(rsi24Act);

    ui->menuStock_Indicators->addMenu(rsiMenu);

    connect(ui->menuStock_Indicators, SIGNAL(triggered(QAction*)), this, SLOT(updatePlot(QAction*)));

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui->customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete csvModel;
}

void MainWindow::loadCSV()
{
    dataX.clear();
    dataX = QVector<double>();

    dataY.clear();
    dataY = QVector<QVector<double>>(29, QVector<double>());

    // https://evileg.com/en/post/158/
    // Create a data model for the mapping table from a CSV file
        csvModel = new QStandardItemModel(this);
        csvModel->setColumnCount(30);
        //csvModel->setHorizontalHeaderLabels(QStringList() << "Марка" << "Модель" << "Цена");
        QStringList headerLabel = (QStringList()
                                   << "Date" << "Open" << "High" << "Low" << "Close"
                                   << "Adj Close" << "Volume" << "ma:5,close"
                                   << "ma:10,close" << "ma:20,close" << "ma:30,close"
                                   << "ma:60,close" << "ma:120,close" << "ema:5,close"
                                   << "ema:10,close" << "ema:20,close" << "ema:30,close"
                                   << "ema:60,close" <<	"ema:120,close" <<	"macd:12,26"
                                   << "macd.signal:12,26,9" <<	"boll:20,close"
                                   << "boll.upper:20,2.0,close" <<	"boll.lower:20,2.0,close"
                                   << "kdj.k:9,3,50.0" << "kdj.d:9,3,3,50.0" << "kdj.j:9,3,3,50.0"
                                   << "rsi:6" << "rsi:12" << "rsi:24"
                                   );
        csvModel->setHorizontalHeaderLabels(headerLabel);

        ui->tableView->setModel(csvModel);

        // Open the file from the resources. Instead of the file
        // Need to specify the path to your desired file
        QFile file(fileString);
        if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
            qDebug() << "File not exists";
        } else {
            // Create a thread to retrieve data from a file
            QTextStream in(&file);

            //Read first line, but not use it... Too difficult to split the string
            QString firstLine = in.readLine();
//            QStringList firstList = firstLine.split(",");
//            csvModel->setHorizontalHeaderLabels(firstList);

            //Reads the data up to the end of file
            //int i = 0;
            while (!in.atEnd())
            {
                QString line = in.readLine();
                // Adding to the model in line with the elements
                QList<QStandardItem *> standardItemsList;
                // consider that the line separated by semicolons into columns
                int j = 0;
                for (QString item : line.split(",")) {
                    //skip first column
                    if (j != 0) {
                        standardItemsList.append(new QStandardItem(item));
                        //Here convert date to o seconds since Epoch (1. Jan 1970, 00:00 UTC)
                        if (j == 1) {
                            QDate da = QDate::fromString(item, "yyyy-MM-dd");
                            dataX.push_back(QCPAxisTickerDateTime::dateTimeToKey(da));
                        }

                        //also save data copy
                        if (j >1) {
                            dataY[j - 2].push_back(item.toDouble());
                        }
                    }
                    j++;
                }
                csvModel->insertRow(csvModel->rowCount(), standardItemsList);
                //i++;
            }
            file.close();
        }

}

void MainWindow::drawIndicator(int col)
{
//    QStandardItem* oItem = csvModel->index(i, col);

//    ui->customPlot->graph()->setData();
}

void MainWindow::openCSV()
{
    fileString =  QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    if (!fileString.isEmpty()) {
        this->loadCSV();
        this->updatePlot(openAct);
    }
    else {
        QMessageBox msg;
        msg.setText("Invalid file name!");
        msg.exec();
    }
}

void MainWindow::checkAllAction()
{
    openAct->setChecked(true);
    highAct->setChecked(true);
    lowAct->setChecked(true);
    closeAct->setChecked(true);
    adjCloseAct->setChecked(true);
    volumeAct->setChecked(true);

    ma5Act->setChecked(true);
    ma10Act->setChecked(true);
    ma20Act->setChecked(true);
    ma30Act->setChecked(true);
    ma60Act->setChecked(true);
    ma120Act->setChecked(true);

    ema5Act->setChecked(true);
    ema10Act->setChecked(true);
    ema20Act->setChecked(true);
    ema30Act->setChecked(true);
    ema60Act->setChecked(true);
    ema120Act->setChecked(true);

    macdAct->setChecked(true);
    macdSignalAct->setChecked(true);

    bollAct->setChecked(true);
    boolUpperAct->setChecked(true);
    boolLowerAct->setChecked(true);

    kdjKAct->setChecked(true);
    kdjDAct->setChecked(true);
    kdjJAct->setChecked(true);

    rsi6Act->setChecked(true);
    rsi12Act->setChecked(true);
    rsi24Act->setChecked(true);

    this->updatePlot(openAct);
}

void MainWindow::uncheckAllAction()
{
    openAct->setChecked(false);
    highAct->setChecked(false);
    lowAct->setChecked(false);
    closeAct->setChecked(false);
    adjCloseAct->setChecked(false);
    volumeAct->setChecked(false);

    ma5Act->setChecked(false);
    ma10Act->setChecked(false);
    ma20Act->setChecked(false);
    ma30Act->setChecked(false);
    ma60Act->setChecked(false);
    ma120Act->setChecked(false);

    ema5Act->setChecked(false);
    ema10Act->setChecked(false);
    ema20Act->setChecked(false);
    ema30Act->setChecked(false);
    ema60Act->setChecked(false);
    ema120Act->setChecked(false);

    macdAct->setChecked(false);
    macdSignalAct->setChecked(false);

    bollAct->setChecked(false);
    boolUpperAct->setChecked(false);
    boolLowerAct->setChecked(false);

    kdjKAct->setChecked(false);
    kdjDAct->setChecked(false);
    kdjJAct->setChecked(false);

    rsi6Act->setChecked(false);
    rsi12Act->setChecked(false);
    rsi24Act->setChecked(false);

    this->updatePlot(openAct);
}

void MainWindow::updatePlot(QAction* oAction)
{
    ui->customPlot->clearGraphs();
    ui->customPlot->clearPlottables();

    // configure bottom axis to show date instead of number:
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("d. MM\nyyyy");
    ui->customPlot->xAxis->setTicker(dateTicker);

    ui->customPlot->xAxis->setLabel("Date");
    ui->customPlot->yAxis->setLabel("Index/Price");

    //Graph number
    int i =0;
    if(openAct->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("Open price");
        ui->customPlot->graph()->rescaleAxes();
    }

    i++;
    if(highAct->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("High price");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(lowAct->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("Low price");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(closeAct->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("Close price");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(adjCloseAct->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("Adj Close price");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(volumeAct->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("Volume");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(ma5Act->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("MA-5");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(ma10Act->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("MA-10");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(ma20Act->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("MA-20");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(ma30Act->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("MA-30");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(ma60Act->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("MA-60");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(ma120Act->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("MA-120");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(ema5Act->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("EMA-5");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(ema10Act->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("EMA-10");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(ema20Act->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("EMA-20");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(ema30Act->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("EMA-30");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(ema60Act->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("EMA-60");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(ema120Act->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("EMA-120");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(macdAct->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("MACD");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(macdSignalAct->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("MACD-Siganl");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(bollAct->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("BOLL");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(boolUpperAct->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("BOLL-Upper");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(boolLowerAct->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("BOLL-Lower");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(kdjKAct->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("KDJ-K");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(kdjDAct->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("KDJ-D");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(kdjJAct->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("KDJ-J");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(rsi6Act->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("RSI-6");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(rsi12Act->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("RSI-12");
        ui->customPlot->graph()->rescaleAxes(true);
    }
    i++;
    if(rsi24Act->isChecked())
    {
        ui->customPlot->addGraph();
        ui->customPlot->graph()->setPen(QColor(rand() % 255, rand() % 255, rand() % 255, 255));
        ui->customPlot->graph()->setData(dataX, dataY[i]);
        ui->customPlot->graph()->setName("RSI-24");
        ui->customPlot->graph()->rescaleAxes(true);
    }


    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // show legend with slightly transparent background brush:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 150));


    ui->customPlot->replot();
}

void MainWindow::mousePress()
{
    // if an axis is selected, only allow the direction of that axis to be dragged
    // if no axis is selected, both directions may be dragged

    if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->customPlot->axisRect()->setRangeDrag(ui->customPlot->xAxis->orientation());
    else if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->customPlot->axisRect()->setRangeDrag(ui->customPlot->yAxis->orientation());
    else
        ui->customPlot->axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
}

void MainWindow::mouseWheel()
{
    // if an axis is selected, only allow the direction of that axis to be zoomed
    // if no axis is selected, both directions may be zoomed

    if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->customPlot->axisRect()->setRangeZoom(ui->customPlot->xAxis->orientation());
    else if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->customPlot->axisRect()->setRangeZoom(ui->customPlot->yAxis->orientation());
    else
        ui->customPlot->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);
}

void MainWindow::selectionChanged()
{

}

