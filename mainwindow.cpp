#include "mainwindow.h"
#include "connectdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    createRightPanel();

    QSplitter *splitter1 = new QSplitter(Qt::Vertical);
    splitter1->setFrameStyle(QFrame::StyledPanel);
    splitter1->addWidget(tableLabel);
    //splitter1->setStretchFactor(1,1);

    QSplitter *splitter2 = new QSplitter(Qt::Horizontal);
    QSplitter *splitter3 = new QSplitter(Qt::Vertical);
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(textQuery);

    splitter3->addWidget(textQuery);
    splitter3->addWidget(tableView);

    splitter2->addWidget(tablesView);
    splitter2->addWidget(splitter3);

    splitter1->addWidget(splitter2);

    splitter1->setStretchFactor(0,1);
    splitter1->setStretchFactor(1,5);

    splitter2->setStretchFactor(0,1);
    splitter2->setStretchFactor(1,3);

    splitter3->setStretchFactor(0,1);
    splitter3->setStretchFactor(1,5);

    setCentralWidget(splitter1);

}

MainWindow::~MainWindow()
{
}
void MainWindow::createRightPanel()
{
    centWidget = new QWidget(this);
    tableView = new QTableView(this);
    textQuery = new QTextEdit(this);
    tablesView = new QListView(this);
    queryModel = new QSqlQueryModel(this);
    tableLabel = new QLabel;
    statusQuery = new QLabel;

    connectAction = new QAction(tr("Connect"),this);
    connect(connectAction,SIGNAL(triggered()),this,SLOT(connectProcedure()));
    disconnectAction = new QAction(tr("Disconnect"),this);
    runAction = new QAction(tr("Run"),this);
    aboutAction = new QAction(tr("About"),this);
    exitAction = new QAction(tr("Exit"),this);

    toolBar = addToolBar(tr("ToolBar"));
    toolBar->addAction(connectAction);
    toolBar->addAction(disconnectAction);
    toolBar->addAction(runAction);
    toolBar->addAction(aboutAction);
    toolBar->addAction(exitAction);

    statusBar()->setVisible(true);
}

void MainWindow::writeSettings()
{

}

void MainWindow::readSettings()
{

}

void MainWindow::connectProcedure()
{
    ConnectDialog connectDialog(this);
    connectDialog.exec();
}
