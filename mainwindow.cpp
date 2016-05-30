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
    QFont font("Arial",10,QFont::Normal);
    textQuery->document()->setDefaultFont(font);

    tablesView = new QListView(this);
    connect(tablesView,SIGNAL(clicked(QModelIndex)),this,SLOT(seeTable(QModelIndex)));

    queryListModel = new QSqlQueryModel(this);
    queryTableModel = new QSqlQueryModel(this);
    tableLabel = new QLabel;
    statusQuery = new QLabel;

    connectAction = new QAction(tr("Connect"),this);
    connect(connectAction,SIGNAL(triggered()),this,SLOT(connectProcedure()));
    disconnectAction = new QAction(tr("Disconnect"),this);
    connect(disconnectAction,SIGNAL(triggered()),this,SLOT(disconnectProcedure()));
    runAction = new QAction(tr("Run"),this);
    connect(runAction,SIGNAL(triggered()),this,SLOT(runProcedure()));
    aboutAction = new QAction(tr("About"),this);
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(aboutProcedure()));
    exitAction = new QAction(tr("Exit"),this);
    connect(exitAction,SIGNAL(triggered()),this,SLOT(exitProcedure()));

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
    tableLabel->setText(connectDialog.connectionString());

    queryListModel->setQuery("select tbl_name from sqlite_master where type = 'table'");
    tablesView->setModel(queryListModel);
    tablesView->setAlternatingRowColors(true);
}

void MainWindow::seeTable(QModelIndex index)
{
//    for(int i=0; i<tableView->model()->columnCount();i++){
//        QAbstractItemDelegate* delegate = tableView->itemDelegateForColumn( i );
//        //Remove the delegate from the view
//        tableView->setItemDelegateForColumn( i, NULL );
//        delete delegate;
//    }
    tableView->clearSpans();
    queryTableModel->clear();
    QSqlRecord record = queryListModel->record(index.row());
    QString tableName = record.value("tbl_name").toString();
    QString textQ = "SELECT * FROM ";
    textQ += tableName;

    queryTableModel->setQuery(textQ);

//    QHeaderView *head = tableView->horizontalHeader();
    //connect(head,SIGNAL(sectionClicked(int)),this,SLOT(sortTable(int)));
    tableView->setModel(queryTableModel);
    QHeaderView *head = tableView->horizontalHeader();
    tableView->setAlternatingRowColors(true);
    tableView->setColumnWidth(1,300);
    head->setStretchLastSection(true);
}

void MainWindow::disconnectProcedure()
{
    tableLabel->clear();
    tableView->setModel(0);
    tablesView->setModel(0);
}

void MainWindow::runProcedure()
{
    QTextDocument *doc = textQuery->document();
    //qDebug()<<
    QString query = doc->toPlainText();
    queryTableModel->clear();
    queryTableModel->setQuery(query);
    if(queryTableModel->lastError().text() != " "){
        QMessageBox::warning(this,"Attantion!",tr("Query text error!!!"
                                                  " %1").arg(queryTableModel->lastError().text()));
    }
}

void MainWindow::aboutProcedure()
{
    QPalette pal;
    pal.setColor(QPalette::Base,Qt::black);
    pal.setColor(QPalette::Text,Qt::darkGreen);
    QFont font("Arial",12,QFont::Bold);
    textQuery->document()->setDefaultFont(font);
    textQuery->setPalette(pal);
}

void MainWindow::exitProcedure()
{
    //textQuery->clear();
    QPalette pal;
    pal.setColor(QPalette::Base,Qt::white);
    pal.setColor(QPalette::Text,Qt::black);
    QFont font("Arial",10,QFont::Normal);
    textQuery->document()->setDefaultFont(font);
    textQuery->setPalette(pal);
}
