/**
 * @file showallmatchdialog.cpp
 * @brief ShowAllMatchDialog 类的实现文件
 *
 * 该文件实现了 ShowAllMatchDialog 类，用于显示、导入和导出所有比赛信息。比赛信息通过表格（QTableWidget）展示，
 * 用户可以导入或导出比赛数据，包括比赛的编号、日期、地点，以及参赛队伍信息。
 *
 * 文件中的主要功能：
 * - populateShowAllMatchTable()：初始化表格，填充所有比赛的信息。
 * - exportMatches()：导出比赛信息到文本文件，供用户保存。
 * - importMatches()：从文本文件中导入比赛信息，并更新全局比赛列表。
 *
 * 依赖项：
 * - showallmatchdialog.h：包含 ShowAllMatchDialog 类声明的头文件。
 * - match.h：用于操作 Match 类，管理比赛及其相关信息。
 * - team.h：用于操作 Team 类，管理球队信息。
 *
 * 作者: 赵子辰
 * @date 2024-09-10
 */

#include "showallmatchdialog.h"
#include "ui_showallmatchdialog.h"
#include<QDebug>
ShowAllMatchDialog::ShowAllMatchDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShowAllMatchDialog)
{
    ui->setupUi(this);
}

ShowAllMatchDialog::~ShowAllMatchDialog()
{
    delete ui;
}

void ShowAllMatchDialog::populateShowAllMatchTable()//填充tableWidget
{
    QList<Match>matchList=Match::getMatchList();//获取比赛列表
    ui->tableWidgetShowAllMatch->setRowCount(0);//清空table
    int currentRow = 0;
    //遍历比赛列表
    for(Match match:matchList)//循环遍历match列表 获取每行数据
    {
        ui->tableWidgetShowAllMatch->insertRow(currentRow);//新增一行

        //填充比赛编号
        int i_NewMatchID = match.getMatchID();
        QString str_NewMatchID = QString::number(i_NewMatchID);
        QTableWidgetItem *it_IDItem = new QTableWidgetItem(str_NewMatchID);
        ui->tableWidgetShowAllMatch->setItem(currentRow,0,it_IDItem);

        //填充比赛时间
        QDate d_NewMatchDate = match.getMatchDate();
        QString str_NewMatchDate = d_NewMatchDate.toString();
        QTableWidgetItem *it_DateItem = new QTableWidgetItem(str_NewMatchDate);
        ui->tableWidgetShowAllMatch->setItem(currentRow,1,it_DateItem);

        //填充比赛地点
        ui->tableWidgetShowAllMatch->setItem(currentRow,2,new QTableWidgetItem(match.getMatchSite()));
        //填充参赛队伍1
        ui->tableWidgetShowAllMatch->setItem(currentRow,3,new QTableWidgetItem(match.getTeam1().getTeamName()));
        //填充参赛队伍2
        ui->tableWidgetShowAllMatch->setItem(currentRow,4,new QTableWidgetItem(match.getTeam2().getTeamName()));
    }

}
/**
 * @brief 导出比赛信息到文件
 *
 * 该函数通过文件对话框让用户选择保存文件的路径，然后将比赛列表中的所有比赛信息写入到指定的文件中。
 * 每一场比赛的信息包括：比赛编号、比赛日期、比赛场地、参赛队伍1名称和参赛队伍2名称。
 */
void ShowAllMatchDialog::exportMatches()
{
    // 打开文件对话框，让用户选择保存文件的位置和名称
    QString fileName = QFileDialog::getSaveFileName(this, "Export Matches", "", "Text Files (*.txt)");

    // 检查用户是否选择了有效的文件名
    if (!fileName.isEmpty())
    {
        QFile file(fileName); // 创建 QFile 对象以操作文件
        if (file.open(QIODevice::WriteOnly)) // 以只写模式打开文件
        {
            QTextStream out(&file); // 创建 QTextStream 对象以便于写入文本

            // 遍历全局比赛列表，将每场比赛的信息写入文件
            for (Match& match : Match::m_MatchList)
            {
                out << match.getMatchID() << " " // 写入比赛编号
                    << match.getMatchDate().toString("yyyy-MM-dd") << " "  // 写入比赛日期，格式为 yyyy-MM-dd
                    << match.getMatchSite() << " "  // 写入比赛地点
                    << match.getTeam1().getTeamName() << " "  // 写入参赛队伍1的名称
                    << match.getTeam2().getTeamName() << "\n"; // 写入参赛队伍2的名称，换行
            }

            file.close(); // 完成写入后关闭文件
        }
    }
}


void ShowAllMatchDialog::on_pushButtonExport_clicked()
{
    exportMatches(); // 调用导出函数
}


void ShowAllMatchDialog::importMatches()
{
    // 打开文件对话框，让用户选择要导入的文件
    QString fileName = QFileDialog::getOpenFileName(this, "Import Matches", "", "Text Files (*.txt)");

    // 检查用户是否选择了有效的文件名
    if (!fileName.isEmpty())
    {
        QFile file(fileName); // 创建 QFile 对象以操作文件
        if (file.open(QIODevice::ReadOnly)) // 以只读模式打开文件
        {
            QTextStream in(&file); // 创建 QTextStream 对象以便于读取文本

            // 逐行读取文件内容，处理每场比赛的信息
            while (!in.atEnd())
            {
                QString line = in.readLine(); // 读取文件中的一行
                QStringList data = line.split(" "); // 按空格分割每行数据

                // 每行必须包含5个字符串变量（比赛编号、比赛日期、比赛场地、队伍1名称、队伍2名称）
                if (data.size() == 5)
                {
                    int matchID = data[0].toInt(); // 获取比赛编号
                    QDate matchDate = QDate::fromString(data[1], "yyyy-MM-dd"); // 获取比赛日期并转换为 QDate 格式
                    QString matchSite = data[2]; // 获取比赛地点
                    QString team1Name = data[3]; // 获取队伍1名称
                    QString team2Name = data[4]; // 获取队伍2名称

                    // 创建 Match 对象，并设置比赛基本信息
                    Match newMatch;
                    newMatch.setMatchID(matchID);
                    newMatch.setMatchDate(matchDate);
                    newMatch.setMatchSite(matchSite);

                    Team team1, team2;
                    bool team1Found = false, team2Found = false;

                    // 查找或创建参赛队伍1
                    for (const Team& team : Team::m_TeamList)
                    {
                        if (team.getTeamName() == team1Name)
                        {
                            team1 = team; // 找到现有的队伍1
                            team1Found = true;
                            break;
                        }
                    }

                    // 如果队伍1未找到，则创建一个新的队伍
                    if (!team1Found)
                    {
                        team1.setTeamID(Team::m_TeamList.size() + 1); // 新的队伍ID
                        team1.setTeamName(team1Name); // 设置队伍名称
                        Team::m_TeamList.append(team1); // 将新队伍添加到球队列表
                    }

                    // 查找或创建参赛队伍2
                    for (const Team& team : Team::m_TeamList)
                    {
                        if (team.getTeamName() == team2Name)
                        {
                            team2 = team; // 找到现有的队伍2
                            team2Found = true;
                            break;
                        }
                    }

                    // 如果队伍2未找到，则创建一个新的队伍
                    if (!team2Found)
                    {
                        team2.setTeamID(Team::m_TeamList.size() + 1); // 新的队伍ID
                        team2.setTeamName(team2Name); // 设置队伍名称
                        Team::m_TeamList.append(team2); // 将新队伍添加到球队列表
                    }

                    // 设置比赛的参赛队伍
                    newMatch.setTeam1(team1);
                    newMatch.setTeam2(team2);

                    // 将比赛添加到比赛列表
                    Match::m_MatchList.append(newMatch);
                }
            }

            file.close(); // 完成读取后关闭文件
        }
    }
}


void ShowAllMatchDialog::on_pushButtonImport_clicked()
{
    importMatches(); // 调用导入函数
}
