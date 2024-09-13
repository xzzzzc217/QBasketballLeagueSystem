/**
 * @file showallteamdialog.cpp
 * @brief ShowAllTeamDialog 类的实现文件
 *
 * 该文件实现了 ShowAllTeamDialog 类，主要用于显示、导入和导出所有球队及其球员的信息。
 * ShowAllTeamDialog 提供了一个表格（QTableWidget）用于展示所有球队，并包含导入和导出功能，允许用户将球队信息
 * 保存为文本文件或从文本文件中加载球队数据。
 *
 * 文件中的主要功能：
 * - populateShowAllTeamTable()：初始化表格，填充所有球队和球员的信息。
 * - exportTeams()：导出球队及球员信息到文本文件，供用户保存。
 * - importTeams()：从文本文件中导入球队及球员信息，更新全局的球队列表。
 *
 * 依赖项：
 * - showallteamdialog.h：包含 ShowAllTeamDialog 类声明的头文件。
 * - team.h：包含 Team 类声明，管理球队和球员的相关信息。
 * - player.h：包含 Player 类声明，管理球员的属性。
 *
 * 作者: 赵子辰
 * @date 2024-09-10
 */

#include "showallteamdialog.h"
#include "ui_showallteamdialog.h"

ShowAllTeamDialog::ShowAllTeamDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShowAllTeamDialog)
{
    ui->setupUi(this);
}

ShowAllTeamDialog::~ShowAllTeamDialog()
{
    delete ui;
}

//在类外部实现函数
void ShowAllTeamDialog::populateShowAllTeamTable()//初始化tableWidget
{
    QList<Team> teamList = Team::getTeamList();  // 获取球队列表
    ui->tableWidgetShowAllTeam->setRowCount(0);  // 清空表格

    int currentRow = 0;

    // 遍历球队列表，填充表格

    for(int i=0;i<Team::m_TeamList.size();++i)
    {
        ui->tableWidgetShowAllTeam->insertRow(currentRow);  // 新增一行

        //填充球队编号
        ui->tableWidgetShowAllTeam->setItem(currentRow,0,new QTableWidgetItem(QString::number(Team::m_TeamList[i].getTeamID())));
        //填充球队名称
        ui->tableWidgetShowAllTeam->setItem(currentRow,1,new QTableWidgetItem(Team::m_TeamList[i].getTeamName()));
        currentRow++;
    }


}
void ShowAllTeamDialog::exportTeams()
{
    // 打开保存文件对话框，获取用户选择的保存文件路径
    QString fileName = QFileDialog::getSaveFileName(this, "Export Teams", "", "Text Files (*.txt)");

    // 如果用户选择了文件
    if (!fileName.isEmpty())
    {
        // 创建一个 QFile 对象来操作文件
        QFile file(fileName);

        // 打开文件，使用写入模式（QIODevice::WriteOnly）
        if (file.open(QIODevice::WriteOnly))
        {
            // 使用 QTextStream 来方便地写入文本数据
            QTextStream out(&file);

            // 遍历 Team 列表，导出每个球队的信息
            for (Team& team : Team::m_TeamList)
            {

                // 写入球队的编号和名称，格式为：<teamID> <teamName>
                out << team.getTeamID() << " " << team.getTeamName() << "\n";

                // 遍历当前球队的球员列表，导出每个球员的信息
                for (const Player& player : team.getTeamPlayers())
                {
                    // 每个球员的信息包括编号、年龄和姓名，格式为：<playerID> <playerAge> <playerName>
                    out << player.getPlayerID() << " "
                        << player.getPlayerAge() << " "
                        << player.getPlayerName() << "\n";
                }

                // 每个球队的信息结束后，写入 "END" 分隔符，用于区分不同球队
                out << "END\n";
            }

            // 完成文件写入，关闭文件
            file.close();
        }
    }
}

void ShowAllTeamDialog::on_pushButtonExport_clicked()//导出
{
    exportTeams();  // 调用导出函数
}

void ShowAllTeamDialog::importTeams()
{
    // 打开文件对话框，允许用户选择要导入的文件
    QString fileName = QFileDialog::getOpenFileName(this, "Import Teams", "", "Text Files (*.txt)");

    // 用户选择文件
    if (!fileName.isEmpty())
    {
        // 创建一个 QFile 对象来操作文件
        QFile file(fileName);

        // 打开文件，使用只读模式（QIODevice::ReadOnly）
        if (file.open(QIODevice::ReadOnly))
        {
            // 使用 QTextStream 来方便地读取文本数据
            QTextStream in(&file);
            Team currentTeam;  // 用来临时存储当前正在导入的球队

            // 逐行读取文件内容
            while (!in.atEnd())//是否已经读到末尾
            {
                // 读取一行，并移除首尾的空白字符
                QString line = in.readLine().trimmed();

                // 如果读取到 "END"，表示当前球队的所有信息结束，将当前球队添加到球队列表
                if (line == "END") {
                    Team::m_TeamList.append(currentTeam);  // 将当前球队添加到全局球队列表
                    currentTeam = Team();  // 重置 currentTeam，准备导入下一个球队
                }
                // 处理球队和球员信息
                else if (line.contains(" "))// 如果该行包含空格，说明是有效的数据
                {
                    QStringList data = line.split(" ");  // 按空格分割数据

                    // 如果某行包含两个数据项，表示这是球队的编号和名称
                    if (data.size() == 2 && data[0].toInt() > 0)
                    {
                        int teamID = data[0].toInt();  // 获取球队编号
                        QString teamName = data[1];    // 获取球队名称

                        // 设置当前球队的编号和名称
                        currentTeam.setTeamID(teamID);
                        currentTeam.setTeamName(teamName);
                    }
                    // 如果某行包含三个数据项，表示这是球员的信息
                    else if (data.size() == 3)
                    {
                        int playerID = data[0].toInt();  // 获取球员编号
                        int playerAge = data[1].toInt();  // 获取球员年龄
                        QString playerName = data[2];     // 获取球员姓名

                        // 创建一个新的球员对象，并设置属性
                        Player newPlayer;
                        newPlayer.setPlayerID(playerID);
                        newPlayer.setPlayerAge(playerAge);
                        newPlayer.setPlayerName(playerName);

                        // 将球员添加到当前球队的球员列表
                        currentTeam.addTeamPlayer(newPlayer);
                    }
                }
            }
            // 完成文件读取后，关闭文件
            file.close();
        }
    }
}

void ShowAllTeamDialog::on_pushButtonImport_clicked()//导入
{
    importTeams();
}

