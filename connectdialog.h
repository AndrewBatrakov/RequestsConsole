#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QtWidgets>

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    ConnectDialog(QWidget *parent = 0,
                  const QString& mode = "",
                  const QString& host = "",
                  int port = 0,
                  const QString& dbName = "",
                  const QString& userName = "");
    ~ConnectDialog();

private:
    QLabel *nameMode;
    QComboBox *editMode;
    QCheckBox *editSQLite;
    QCheckBox *editHostCh;
    QLineEdit *editHost;
    QCheckBox *editPortCh;
    QSpinBox *editPortVal;
    QLabel *nameDB;
    QLineEdit *editDB;
    QLabel *nameUser;
    QLineEdit *editUser;
    QLabel *namePassword;
    QLineEdit *editPassword;
};

#endif // CONNECTDIALOG_H
