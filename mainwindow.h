#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtSql>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void createRightPanel();
    void writeSettings();
    void readSettings();

    void connectProcedure();
    void seeTable(QModelIndex);
    void disconnectProcedure();
    void runProcedure();
    void aboutProcedure();
    void exitProcedure();

private:
    QWidget *centWidget;

    QTableView *tableView;
    QLabel *tableLabel;
    //QSqlQuery *query;
    QSqlQueryModel *queryListModel;
    QSqlQueryModel *queryTableModel;
    //QStringList tables;
    //QStringListModel *tablesModel;
    QListView *tablesView;
    QTextEdit *textQuery;
    QLabel *statusQuery;

    QToolBar *toolBar;

    QAction *connectAction;
    QAction *disconnectAction;
    QAction *runAction;
    QAction *aboutAction;
    QAction *exitAction;
};

#endif // MAINWINDOW_H
