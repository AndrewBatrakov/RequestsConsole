#include "connectdialog.h"
#include <QtSql>

ConnectDialog::ConnectDialog(QWidget *parent,
                             const QString &mode,
                             const QString &host,
                             int port,
                             const QString &dbName,
                             const QString &userName) :
    QDialog(parent)
{
    nameMode = new QLabel(tr("Mode:"));
    nameMode->setAlignment(Qt::AlignRight);
    editMode = new QComboBox;
    editSQLite = new QCheckBox(tr("SQLite"));
    editSQLite->setLayoutDirection(Qt::RightToLeft);
    connect(editSQLite,SIGNAL(stateChanged(int)),this,SLOT(connectDBButton()));

    openDBButton = new QToolButton;
    openDBButton->setText("...");
    connect(openDBButton,SIGNAL(clicked()),this,SLOT(openSQLite()));

    QHBoxLayout *baseLayOut = new QHBoxLayout;
    baseLayOut->addWidget(editMode);
    baseLayOut->addWidget(editSQLite);

    editHostCh = new QCheckBox;
    editHostCh->setText(tr("Host:"));
    editHostCh->setLayoutDirection(Qt::RightToLeft);
    editHost = new QLineEdit;

    editPortCh = new QCheckBox;
    editPortCh->setText(tr("Port:"));
    editPortCh->setLayoutDirection(Qt::RightToLeft);
    editPortVal = new QSpinBox;

    nameDB = new QLabel(tr("Data Base:"));
    nameDB->setAlignment(Qt::AlignRight);
    editDB = new QLineEdit;

    QHBoxLayout *dbLayout = new QHBoxLayout;
    dbLayout->addWidget(editDB);
    dbLayout->addWidget(openDBButton);
    openDBButton->setVisible(false);

    nameUser = new QLabel(tr("User:"));
    nameUser->setAlignment(Qt::AlignRight);
    editUser = new QLineEdit;

    namePassword = new QLabel(tr("Password:"));
    namePassword->setAlignment(Qt::AlignRight);
    editPassword = new QLineEdit;

    QStringList drivers = QSqlDatabase::drivers();
    drivers.removeAll("QSQLITE");
    drivers.removeAll("QMYSQL");
    drivers.removeAll("QOCI8");
    drivers.removeAll("QODBC3");
    drivers.removeAll("QPSQL7");
    drivers.removeAll("QTDS7");
    editMode->addItems(drivers);

    //QSqlDatabase db;
    //db = QSqlDatabase::addDatabase("QSQLITE");

    int i = editMode->findText(mode, Qt::MatchFixedString);
    if(i > -1)
        editMode->setCurrentIndex(i);
    if(!host.isEmpty()){
        editHostCh->setCheckState(Qt::Checked);
        editHost->setText(host);
    }else{
        editHostCh->setCheckState(Qt::Unchecked);
        editHost->clear();
    }
    if(port > 0){
        editPortCh->setCheckState(Qt::Checked);
        editPortVal->setValue(port);
    }else {
        editPortCh->setCheckState(Qt::Unchecked);
        editPortVal->setValue(0);
    }
    editDB->setText(dbName);
    editUser->setText(userName);
    editPassword->clear();

    QVBoxLayout *nameLayout = new QVBoxLayout;
    nameLayout->addWidget(nameMode);
    nameLayout->addWidget(editHostCh);
    nameLayout->addWidget(nameDB);
    nameLayout->addWidget(nameUser);

    QVBoxLayout *editLayOut = new QVBoxLayout;
    editLayOut->addLayout(baseLayOut);
    editLayOut->addWidget(editHost);
    editLayOut->addLayout(dbLayout);
    editLayOut->addWidget(editUser);

    QHBoxLayout *allLayout = new QHBoxLayout;
    allLayout->addLayout(nameLayout);
    allLayout->addLayout(editLayOut);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(allLayout);

    setLayout(mainLayout);
}

ConnectDialog::~ConnectDialog()
{

}

void ConnectDialog::connectDBButton()
{
    if(editSQLite->isChecked()){
        openDBButton->setVisible(true);
    }else{
        openDBButton->setVisible(false);
    }
}

void ConnectDialog::openSQLite()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open file"),".","*.dat");
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)){
        QSqlDatabase db;
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(file.fileName());
        if(!db.open()){
            QMessageBox::warning(this,tr("Attantion!"),tr("Data Base %1, don't open!").arg(file.fileName()));
        }else{
            conString = file.fileName();
            emit accept();
        }
    }
}

void ConnectDialog::done(int result)
{
    QDialog::done(result);
}
