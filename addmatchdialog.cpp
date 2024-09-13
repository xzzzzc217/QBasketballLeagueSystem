/**
 * @file addmatchdialog.cpp
 * @brief AddMatchDialog 类的实现文件
 *
 * 该文件包含 AddMatchDialog 类的实现，该类提供一个用于添加新比赛的对话框界面。
 * 用户可以选择两个参赛队伍，并指定比赛地点、日期以及比赛 ID。
 *
 * 两个队伍通过两个 QComboBox 小部件进行选择。当一个队伍在第一个下拉框中被选中时，
 * 该队伍将从第二个下拉框的选项中移除，以防止用户为两支队伍选择相同的队伍。用户还可以输入比赛 ID、比赛地点和比赛日期，
 * 这些信息会被存储到比赛对象中。
 *
 * 文件中的主要函数：
 * - AddMatchTeam1Options()：根据第一个队伍的选择更新第二个队伍的选项。
 * - AddMatchTeam2Options()：根据第二个队伍的选择更新第一个队伍的选项。
 * - on_buttonBox_accepted()：获取用户输入的所有信息，包括队伍选择、比赛地点、日期和比赛 ID，
 *   然后将比赛信息存储到全局比赛列表中。
 *
 * 依赖项：
 * - addmatchdialog.h：包含 AddMatchDialog 类声明的头文件。
 * - team.h：定义 Team 类及相关函数的头文件（例如 `populateTeamComboBox` 和 `getTeamList`）。
 * - match.h：定义 Match 类及其属性和比赛列表管理的头文件。
 *
 * 作者：赵子辰
 * @date 2024-09-10
 */

#include "addmatchdialog.h"
#include "ui_addmatchdialog.h"

AddMatchDialog::AddMatchDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddMatchDialog)
{
    ui->setupUi(this);

    // 将队伍列表填充到两个 QComboBox
    Team::populateTeamComboBox(ui->comboBoxTeam1);
    Team::populateTeamComboBox(ui->comboBoxTeam2);
}

AddMatchDialog::~AddMatchDialog()
{
    delete ui;
}

void AddMatchDialog::AddMatchTeam1Options()//将队伍填充到team1combobox里
{
    // 获取 team1 选中的队伍
    QString selectedTeam1 = ui->comboBoxTeam1->currentText();

    //每次填充前先清除 team2 的所有选项
    ui->comboBoxTeam2->clear();

    // 再将未选中的队伍添加回 team2 的下拉框中
    QList<Team> teamList = Team::getTeamList();
    for (const Team &team : teamList)
    {
        if (team.getTeamName() != selectedTeam1)
        {
            ui->comboBoxTeam2->addItem(team.getTeamName());
        }
    }
}
//eg:假设有3支队伍：Team A、Team B 和 Team C。
//当用户在 comboBoxTeam1 中选择了 Team A 时，希望 comboBoxTeam2 只显示 Team B 和 Team C，因此必须首先调用 clear() 清空 comboBoxTeam2 的内容，再添加不包括 Team A 的队伍选项。
//当用户在 comboBoxTeam2 中选择了 Team C 时，comboBoxTeam1 中应只显示 Team A 和 Team B，这也需要通过 clear() 清空当前选项，再重新填充剩下的队伍。
void AddMatchDialog::AddMatchTeam2Options()//
{
    //获取team2选中的队伍
    QString selectedTeam2 = ui->comboBoxTeam2->currentText();

    //清除team1的所有选项
    ui->comboBoxTeam1->clear();

    //再将未选中的队伍添加回team1的下拉框中
    QList<Team> teamList = Team::getTeamList();
    for(const Team &team : teamList)
    {
        if(team.getTeamName()!=selectedTeam2)
        {
            ui->comboBoxTeam1->addItem(team.getTeamName());
        }
    }
}

void AddMatchDialog::on_buttonBox_accepted()//addMatch-确定
{
    //获取QString文本
    QString str_Team1Name = ui->comboBoxTeam1->currentText();
    QString str_Team2Name = ui->comboBoxTeam2->currentText();

    QString str_MatchSite = ui->lineEditMatchSite->text();
    //获取int类matchID
    int i_MatchID = ui->lineEditMatchID->text().toInt();

    // 获取 QDate 对象
    QDate d_MatchDate = ui->dateEditMatchDate->date(); // 直接获取 QDate

    m_CurrentMatch.setMatchDate(d_MatchDate);
    m_CurrentMatch.setMatchID(i_MatchID);//m_MatchID
    m_CurrentMatch.setMatchSite(str_MatchSite);//m_MatchSite
    for(int i=0;i<Team::m_TeamList.size();++i)//根据队名找到team1
    {
        if(Team::m_TeamList[i].getTeamName()==str_Team1Name)
        {
            Team team1 = Team::m_TeamList[i];
            //将team1塞进m_CurrentMatch的m_Team1
            m_CurrentMatch.setTeam1(team1);
        }
    }

    for(int i=0;i<Team::m_TeamList.size();++i)//同理，找到team2
    {
        if(Team::m_TeamList[i].getTeamName()==str_Team2Name)
        {
            Team team2 = Team::m_TeamList[i];
            //将team2塞进去
            m_CurrentMatch.setTeam2(team2);
        }
    }
    //到此m_CurrentMatch的所有属性设置完毕
    //将m_CurrentMatch添加到m_MatcList
    Match::m_MatchList.append(m_CurrentMatch);

}

