#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"newteamdialog.h"
#include"showallteamdialog.h"
#include"addmatchdialog.h"
#include"removeteamdialog.h"
#include"showallmatchdialog.h"
#include"removematchdialog.h"
#include"matchplayersmanagerdialog.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include<QMessageBox>
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QList<PlayerPerformance> l_Performances;//用于储存所有球员的场次表现
private slots:
    void on_actionAddTeam_triggered();// 从主窗口显示addteam对话框

    void on_actionshowAllTeam_triggered();//从主窗口显示showAllTeamDialog

    void on_actionAddMatch_triggered();//从主窗口显示AddMatchDialog

    void on_actionRemoveTeam_triggered();//从主窗口显示RemoveTeam对话框

    void on_actionShowAllMatch_triggered();//从主窗口显示ShowAllMatchDialog

    void on_actionRemoveMatch_triggered();//从主窗口显示RemoveMatchDialog

    void on_actionMatchManager_triggered();//从主窗口显示MatchPlayersManagerDialog

    void on_pushButtonMatchQuery_clicked();//主窗口查询场次

    void on_pushButtonTeamQuery_clicked();//查询球队

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
