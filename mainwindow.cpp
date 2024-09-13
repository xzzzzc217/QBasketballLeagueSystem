/**
 * @file mainwindow.cpp
 * @brief MainWindow 类的实现文件
 *
 * 该文件实现了 MainWindow 类，负责管理应用程序的主窗口及其相关的功能。通过主窗口，用户可以访问各种管理界面，
 * 如添加球队、显示所有球队、添加比赛、显示所有比赛、删除球队和比赛，以及管理比赛中的球员。
 * 主窗口还提供了两个查询功能，用户可以根据比赛场地和球队名称来查询相关信息。
 *
 *
 * 文件中的主要功能：
 * - on_actionAddTeam_triggered()：打开添加球队的对话框。
 * - on_actionshowAllTeam_triggered()：打开显示所有球队的对话框并填充球队数据。
 * - on_actionAddMatch_triggered()：打开添加比赛的对话框，并填充参赛队伍信息。
 * - on_actionRemoveTeam_triggered()：打开删除球队的对话框，并填充球队列表。
 * - on_actionShowAllMatch_triggered()：打开显示所有比赛的对话框并填充比赛数据。
 * - on_actionRemoveMatch_triggered()：打开删除比赛的对话框，并填充比赛列表。
 * - on_actionMatchManager_triggered()：打开比赛球员管理对话框，并填充比赛 ID 列表。
 * - on_pushButtonQuery_clicked()：根据用户输入的比赛场地，查询并显示相关比赛信息。
 * - on_pushButtonTeamQuery_clicked()：根据用户输入的球队名称（不带“队”字），查询并显示相关球队球员信息。
 * 依赖项：
 * - mainwindow.h：包含 MainWindow 类声明的头文件。
 * - removeteamdialog.h：用于操作 RemoveTeamDialog 对话框。
 * - team.h：用于操作 Team 类，管理队伍和球员列表。
 *
 * 作者:赵子辰
 * @date 2024-09-10
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"removeteamdialog.h"
#include"team.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAddTeam_triggered()//点开球队管理-点击addteam
{
    NewTeamDialog newTeamDialog(this);  // 创建对话框
    newTeamDialog.exec();  // 从主窗口显示addteam对话框
}


void MainWindow::on_actionshowAllTeam_triggered()//点开球队管理-点击showAllTeam
{
    ShowAllTeamDialog showAllTeamDialog(this);//创建对话框

    // 调用 populateShowAllTeamTable() 来填充球队数据
    showAllTeamDialog.populateShowAllTeamTable();

    showAllTeamDialog.exec();//从主窗口显示showAllTeamDialog
}


void MainWindow::on_actionAddMatch_triggered()//点开场次管理-点击AddMatch
{
    // 创建并显示 AddMatchDialog
    AddMatchDialog addMatchDialog(this);//创建对话框
    addMatchDialog.AddMatchTeam1Options();//将team填充进combobox1
    addMatchDialog.AddMatchTeam2Options();//将team填充进combobox2
    addMatchDialog.exec();//从主窗口显示AddMatchDialog
}



void MainWindow::on_actionRemoveTeam_triggered()//球队管理-RemoveTeam
{

    RemoveTeamDialog removeTeamTableDialog(this);//创建对话框
    removeTeamTableDialog.populateTeamList();//将team填充进combobox
    removeTeamTableDialog.exec();//从主窗口显示RemoveTeamDialog
}



void MainWindow::on_actionShowAllMatch_triggered()//场次管理-showAllMatch
{
    ShowAllMatchDialog showAllMatchDialog(this); //创建对话框
    showAllMatchDialog.populateShowAllMatchTable();
    showAllMatchDialog.exec();//从主窗口显示showAllMatchDialog
}


void MainWindow::on_actionRemoveMatch_triggered()//场次管理-removeMatch
{
    RemoveMatchDialog removeMatchDialog(this); //创建对话框
    removeMatchDialog.populateMatchList();//将match列表填充进combobox
    removeMatchDialog.exec();//从主窗口显示removeMatchDialog
}


void MainWindow::on_actionMatchManager_triggered()//场次管理-MatchPlayersManager
{
    MatchPlayersManagerDialog matchPlayersManagerDialog(this);//创建对话框
    matchPlayersManagerDialog.populateMatchID();//将matchID填充进combobox
    matchPlayersManagerDialog.exec();//从主窗口显示matchPlayersManagerDialog
}

void MainWindow::on_pushButtonMatchQuery_clicked()//点击“查询”
{
    // 获取用户的输入
    QString str_MatchQuery = ui->lineEditMatchQuery->text();


    QList<Match> l_MatchesQuery;

    // 遍历所有比赛，查找在该场地举行的比赛
    for (Match& match : Match::m_MatchList)
    {
        if (match.getMatchSite() == str_MatchQuery) // 比较场地名称
        {
            l_MatchesQuery.append(match); // 将符合条件的比赛加入列表
        }
    }

    // 如果有比赛则弹出窗口显示比赛信息
    if (!l_MatchesQuery.isEmpty())
    {
        QString str_MatchInfo;
        for (Match& match : l_MatchesQuery)
        {
            QString str_Team1Name = match.getTeam1().getTeamName();
            QString str_Team2Name = match.getTeam2().getTeamName();
            QString str_MatchTime = match.getMatchDate().toString();
            str_MatchInfo += QString("比赛时间: %1\n比赛双方: %2 vs %3\n\n").arg(str_MatchTime).arg(str_Team1Name).arg(str_Team2Name);
        }

        QMessageBox::information(this, "比赛查询结果", str_MatchInfo);
    }
    else
    {
        QMessageBox::information(this, "比赛查询结果", "该场地没有相关比赛。");
    }


}

void MainWindow::on_pushButtonTeamQuery_clicked() // 点击“查询”
{
    // 获取用户的输入
    QString str_TeamQuery = ui->lineEditTeamQuery->text();
    bool b_TeamFound = false; // 标记是否找到球队

    // 遍历所有球队
    for (int i = 0; i < Team::m_TeamList.size(); i++)
    {
        Team t_CurrentTeam = Team::m_TeamList[i]; // 获取当前球队
        if (t_CurrentTeam.getTeamName() == str_TeamQuery) // 比较球队名称
        {
            b_TeamFound = true; // 标记找到球队

            // 如果找到匹配的球队，则弹出窗口显示球队信息
            QString str_TeamInfo;
            str_TeamInfo += QString("球队名：%1\n").arg(str_TeamQuery);

            // 遍历球队球员并输出球队球员信息
            for (int j = 0; j < t_CurrentTeam.getTeamPlayers().size(); j++)
            {
                QString str_PlayerID = QString::number(t_CurrentTeam.getTeamPlayers()[j].getPlayerID());
                QString str_PlayerName = t_CurrentTeam.getTeamPlayers()[j].getPlayerName();
                str_TeamInfo += QString("球员编号：%1，球员姓名：%2\n").arg(str_PlayerID).arg(str_PlayerName);
            }

            // 显示找到的球队和球员信息
            QMessageBox::information(this, "球队查询结果", str_TeamInfo);

            break; // 找到匹配的球队后退出循环
        }
    }

    // 如果没有找到球队，显示提示信息
    if (!b_TeamFound)
    {
        QMessageBox::information(this, "球队查询结果", "没有找到相关球队。");
    }
}
