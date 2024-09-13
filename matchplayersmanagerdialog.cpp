/**
 * @file matchplayersmanagerdialog.cpp
 * @brief MatchPlayersManagerDialog 类的实现文件
 *
 * 该文件实现了 MatchPlayersManagerDialog 类，该类主要用于管理比赛中的球员，包括添加、删除和更新球员信息，以及管理球员的比赛表现数据。
 * 该类通过一个对话框界面，允许用户选择比赛，并对相应的队伍和球员进行操作。
 *
 * 文件中的主要功能：
 * - populateMatchID()：填充比赛编号到下拉框。
 * - refreshPlayerList()：刷新指定比赛中的两支队伍的球员列表。
 * - getSelectedMatch()：获取用户选中的比赛对象。
 * - on_buttonBoxSelectMatchID_accepted()：根据选定的比赛，刷新球员列表。
 * - on_buttonBoxRemove_accepted()：根据选定的球员名称，从队伍中删除球员。
 * - on_pushButtonNotRemove_clicked()：取消删除球员操作。
 * - on_buttonBoxAdd_accepted()：根据用户输入，向队伍中添加新的球员。
 * - on_buttonBoxPerformance_accepted()：录入选定球员的比赛表现数据。
 * - on_pushButtonInputComplete_clicked()：处理所有录入操作，更新表格，并恢复或清除临时删除和新增的球员。
 *
 * 依赖项：
 * - matchplayersmanagerdialog.h：包含 MatchPlayersManagerDialog 类声明的头文件。
 * - match.h：用于获取和操作 Match 对象。
 * - team.h：用于操作 Team 类，管理队伍和球员列表。
 * - player.h：用于操作 Player 类，管理球员的信息及其表现数据。
 *
 * 作者: 赵子辰
 * @date 2024-09-10
 */

#include "matchplayersmanagerdialog.h"
#include "ui_matchplayersmanagerdialog.h"

MatchPlayersManagerDialog::MatchPlayersManagerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MatchPlayersManagerDialog)
{
    ui->setupUi(this);
}

MatchPlayersManagerDialog::~MatchPlayersManagerDialog()
{
    delete ui;
}

void MatchPlayersManagerDialog::populateMatchID()//先填充
{
    QList<Match>matchList = Match::getMatchList();//获取m_MatchList
    for(int i=0;i<matchList.size();i++)
    {
        ui->comboBoxMatchID->addItem(QString::number(matchList[i].getMatchID()));//将场次ID填充进combobox
    }

}

void MatchPlayersManagerDialog::refreshPlayerList()
{
    // 重新获取选定比赛的队伍和球员列表
    Match selectedMatch = getSelectedMatch();
    if (selectedMatch.getMatchID() == 0) return;  // 确保比赛存在

    Team team1 = selectedMatch.getTeam1();
    Team team2 = selectedMatch.getTeam2();

    QList<Player> l_Team1Players = team1.getTeamPlayers();
    QList<Player> l_Team2Players = team2.getTeamPlayers();

    // 清空 combobox，然后重新填充
    ui->comboBoxTeam1Players->clear();
    ui->comboBoxTeam2Players->clear();

    for (const Player &player : l_Team1Players)
    {
        ui->comboBoxTeam1Players->addItem(player.getPlayerName());
    }

    for (const Player &player : l_Team2Players)
    {
        ui->comboBoxTeam2Players->addItem(player.getPlayerName());
    }

}

Match& MatchPlayersManagerDialog::getSelectedMatch()
{
    int selectedMatchID = ui->comboBoxMatchID->currentText().toInt();
    QList<Match> &matchList = Match::getMatchList();  // 使用非 const 的引用获取比赛列表

    for (Match &match : matchList)  // 返回 match 的引用
    {
        if (match.getMatchID() == selectedMatchID)
        {
            return match;
        }
    }

    qDebug() << "Match not found for ID:" << selectedMatchID;
    static Match emptyMatch; // 返回空的引用对象
    return emptyMatch;
}

void MatchPlayersManagerDialog::on_buttonBoxSelectMatchID_accepted()//确定-选中比赛场次编号
{
    Match selectedMatch = getSelectedMatch();
    if (selectedMatch.getMatchID() == 0) return; // 确保比赛存在

    // 获取 Team1 和 Team2
    Team &team1 = selectedMatch.getTeam1();
    Team &team2 = selectedMatch.getTeam2();


    // 获取 Team1 和 Team2 的球员列表
    QList<Player> &l_Team1Players = team1.getTeamPlayers();
    QList<Player> &l_Team2Players = team2.getTeamPlayers();

    // 清空 combobox
    ui->comboBoxTeam1Players->clear();
    ui->comboBoxTeam2Players->clear();

    // 将 Team1 的球员添加到 combobox
    for (const Player &player : l_Team1Players)
    {
        ui->comboBoxTeam1Players->addItem(player.getPlayerName());
    }

    // 将 Team2 的球员添加到 combobox
    for (const Player &player : l_Team2Players)
    {
        ui->comboBoxTeam2Players->addItem(player.getPlayerName());
    }
}

void MatchPlayersManagerDialog::on_buttonBoxRemove_accepted()
{
    QString str_SelectTeam1PlayerName = ui->comboBoxTeam1Players->currentText();
    QString str_SelectTeam2PlayerName = ui->comboBoxTeam2Players->currentText();

    Match &selectedMatch = getSelectedMatch();
    if (selectedMatch.getMatchID() == 0) return;

    // 获取 Team1 和 Team2
    Team &team1 = selectedMatch.getTeam1();
    Team &team2 = selectedMatch.getTeam2();

    // 获取 Team1 和 Team2 的球员列表
    QList<Player> &l_Team1Players = team1.getTeamPlayers();
    QList<Player> &l_Team2Players = team2.getTeamPlayers();

    // 删除 Team1 球员

    for(int i = 0; i < l_Team1Players.size(); i++)
    {
        if(l_Team1Players[i].getPlayerName() == str_SelectTeam1PlayerName)
        {
            Player selectTeam1Player = l_Team1Players[i];
            l_Team1Players.removeAt(i);
            m_TempRemoveTeam1PLayers.append(selectTeam1Player);
            qDebug() << "删除了Team 1的: " << selectTeam1Player.getPlayerName();
            break;
        }
    }

    // 删除 Team2 球员

    for(int i = 0; i < l_Team2Players.size(); i++)
    {
        if(l_Team2Players[i].getPlayerName() == str_SelectTeam2PlayerName)
        {
            Player selectTeam2Player = l_Team2Players[i];
            l_Team2Players.removeAt(i);
            m_TempRemoveTeam2PLayers.append(selectTeam2Player);
            qDebug() << "删除了Team 2的: " << selectTeam2Player.getPlayerName();
            break;
        }
    }

    // 在数据修改完成后刷新列表
    team1.setTeamPlayers(l_Team1Players);
    team2.setTeamPlayers(l_Team2Players);
    refreshPlayerList();
}

void MatchPlayersManagerDialog::on_pushButtonNotRemove_clicked()//选择不删除任何球员
{
    //选择不删除team1team2的球员
    //m_TempRemoveTeam1PLayers,m_TempRemoveTeam2PLayers都为空列表
}

void MatchPlayersManagerDialog::on_buttonBoxAdd_accepted()
{
    //先将ui中新球员的属性全部获取
    QString str_Team1AidPlayerName = ui->lineEditTeam1PlayerName->text();
    QString str_Team2AidPlayerName = ui->lineEditTeam2PlayerName->text();
    int i_Team1AidPlayerAge = ui->lineEditTeam1PlayerAge->text().toInt();
    int i_Team2AidPlayerAge = ui->lineEditTeam2PlayerAge->text().toInt();
    int i_Team1AidPlayerID = ui->lineEditTeam1PlayerID->text().toInt();
    int i_Team2AidPlayerID = ui->lineEditTeam2PlayerID->text().toInt();

    if(!str_Team1AidPlayerName.isEmpty()&&str_Team2AidPlayerName.isEmpty())
    {
        //情况1：球队1新增球员，球队2不新增球员
        //即str_Team1AidPlayerName.isEmpty() = False，str_Team2AidPlayerName.isEmpty() = True
        //m_TempAddTeam2Players为空列表
        Match& selectedMatch = getSelectedMatch();
        if (selectedMatch.getMatchID() == 0) return; // 确保比赛存在

        // 获取 Team1 和 Team2
        Team &team1 = selectedMatch.getTeam1();

        // 获取 Team1 和 Team2 的球员列表
        QList<Player> &l_Team1Players = team1.getTeamPlayers();

        // 避免重复添加球员
        for (const Player &player : l_Team1Players)
        {
            if (player.getPlayerID() == i_Team1AidPlayerID)
            {
                qDebug() << "该球员已在 Team 1 中，无法重复添加";
                return;
            }
        }
        // 创建新的球员对象，由于没有对team2新建球员，因此不需创建team2AidPlayer
        Player team1AidPlayer;
        team1AidPlayer.setPlayerAge(i_Team1AidPlayerAge);
        team1AidPlayer.setPlayerID(i_Team1AidPlayerID);
        team1AidPlayer.setPlayerName(str_Team1AidPlayerName);
        //将team1外援添加到列表
        l_Team1Players.append(team1AidPlayer);
        //将team1外援添加到储存临时外援的列表中
        m_TempAddTeam1Players.append(team1AidPlayer);
        //更新team1球员列表
        team1.setTeamPlayers(l_Team1Players);

    }
    if(str_Team1AidPlayerName.isEmpty()&&!str_Team2AidPlayerName.isEmpty())
    {
        //情况2：球队1不新增球员，球队2新增球员
        //即str_Team1AidPlayerName.isEmpty() = True，str_Team2AidPlayerName.isEmpty() = False
        //m_TempAddTeam1Players为空列表
        Match& selectedMatch = getSelectedMatch();
        if (selectedMatch.getMatchID() == 0)
            return; // 确保比赛存在

        // 获取 Team2

        Team &team2 = selectedMatch.getTeam2();

        // 获取 Team2 的球员列表

        QList<Player> &l_Team2Players = team2.getTeamPlayers();

        // 避免重复添加球员

        for (const Player &player : l_Team2Players)
        {
            if (player.getPlayerID() == i_Team2AidPlayerID)
            {
                qDebug() << "该球员已在 Team 2 中，无法重复添加";
                return;
            }
        }
        // 创建新的球员对象，由于没有对team1新建球员，因此不需创建team1AidPlayer
        Player team2AidPlayer;
        team2AidPlayer.setPlayerAge(i_Team2AidPlayerAge);
        team2AidPlayer.setPlayerID(i_Team2AidPlayerID);
        team2AidPlayer.setPlayerName(str_Team2AidPlayerName);
        //将team2外援添加到列表
        l_Team2Players.append(team2AidPlayer);
        //将team2外援添加到储存临时外援的列表中
        m_TempAddTeam2Players.append(team2AidPlayer);
        //更新team2球员列表
        team2.setTeamPlayers(l_Team2Players);
    }
    if(!str_Team1AidPlayerName.isEmpty()&&!str_Team2AidPlayerName.isEmpty())
    {
        //情况3：两支球队都新增球员（正常情况）
        //即str_Team1AidPlayerName.isEmpty() = False，str_Team2AidPlayerName.isEmpty() = False
        Match& selectedMatch = getSelectedMatch();
        if (selectedMatch.getMatchID() == 0) return; // 确保比赛存在

        // 获取 Team1 和 Team2
        Team &team1 = selectedMatch.getTeam1();
        Team &team2 = selectedMatch.getTeam2();

        // 获取 Team1 和 Team2 的球员列表
        QList<Player> &l_Team1Players = team1.getTeamPlayers();
        QList<Player> &l_Team2Players = team2.getTeamPlayers();

        // 避免重复添加球员
        for (const Player &player : l_Team1Players)
        {
            if (player.getPlayerID() == i_Team1AidPlayerID)
            {
                qDebug() << "该球员已在 Team 1 中，无法重复添加";
                return;
            }
        }
        for (const Player &player : l_Team2Players)
        {
            if (player.getPlayerID() == i_Team2AidPlayerID)
            {
                qDebug() << "该球员已在 Team 2 中，无法重复添加";
                return;
            }
        }

        // 创建新的球员对象
        Player team1AidPlayer;
        team1AidPlayer.setPlayerAge(i_Team1AidPlayerAge);
        team1AidPlayer.setPlayerID(i_Team1AidPlayerID);
        team1AidPlayer.setPlayerName(str_Team1AidPlayerName);

        Player team2AidPlayer;
        team2AidPlayer.setPlayerAge(i_Team2AidPlayerAge);
        team2AidPlayer.setPlayerID(i_Team2AidPlayerID);
        team2AidPlayer.setPlayerName(str_Team2AidPlayerName);

        // 将外援添加到队伍中
        l_Team1Players.append(team1AidPlayer);
        l_Team2Players.append(team2AidPlayer);

        // 将外援添加到存储临时新增的球员列表当中
        m_TempAddTeam1Players.append(team1AidPlayer);
        m_TempAddTeam2Players.append(team2AidPlayer);

        // 更新 team1 和 team2 的球员列表
        team1.setTeamPlayers(l_Team1Players);
        team2.setTeamPlayers(l_Team2Players);
    }
    if(str_Team1AidPlayerName.isEmpty()&&str_Team2AidPlayerName.isEmpty())
    {
        //情况4：两支球队都不新增球员
        //即str_Team1AidPlayerName.isEmpty() = True，str_Team2AidPlayerName.isEmpty() = Ture
        //m_TempAddTeam1Players，m_TempAddTeam2Players都为空列表
    }

    // 清空 combobox，重新填充球员数据
    refreshPlayerList();
    Match& selectedMatch = getSelectedMatch();
    if (selectedMatch.getMatchID() == 0) return; // 确保比赛存在

    // 获取 Team1 和 Team2
    Team &team1 = selectedMatch.getTeam1();
    Team &team2 = selectedMatch.getTeam2();

    // 获取 Team1 和 Team2 的球员列表
    QList<Player> &l_Team1Players = team1.getTeamPlayers();
    QList<Player> &l_Team2Players = team2.getTeamPlayers();
    for(int i=0;i<l_Team1Players.size();i++)
    {
        ui->comboBoxTeam1Performance->addItem(l_Team1Players[i].getPlayerName());
    }
    for(int i=0;i<l_Team2Players.size();i++)
    {
        ui->comboBoxTeam2Performance->addItem(l_Team2Players[i].getPlayerName());
    }
    // 清空输入框，方便下一次添加
    ui->lineEditTeam1PlayerName->clear();
    ui->lineEditTeam2PlayerName->clear();
    ui->lineEditTeam1PlayerAge->clear();
    ui->lineEditTeam2PlayerAge->clear();
    ui->lineEditTeam1PlayerID->clear();
    ui->lineEditTeam2PlayerID->clear();
}

void MatchPlayersManagerDialog::on_buttonBoxPerformance_accepted()
{
    Match& selectedMatch = getSelectedMatch();
    if (selectedMatch.getMatchID() == 0) return;

    // 获取 Team1 和 Team2
    Team &team1 = selectedMatch.getTeam1();
    Team &team2 = selectedMatch.getTeam2();

    // 获取 Team1 和 Team2 的球员列表
    QList<Player> &l_Team1Players = team1.getTeamPlayers();
    QList<Player> &l_Team2Players = team2.getTeamPlayers();
    //测试前面新增外援的操作是否成功
    for(int i=0;i<l_Team1Players.size();i++)
    {
        qDebug()<<"team1里目前有"<<l_Team1Players[i].getPlayerID();
    }

    //获取combobox选中的球员名字
    QString str_PerformanceSelectTeam1PlayerName = ui->comboBoxTeam1Performance->currentText();
    QString str_PerformanceSelectTeam2PlayerName = ui->comboBoxTeam2Performance->currentText();

    if (str_PerformanceSelectTeam1PlayerName.isEmpty() || str_PerformanceSelectTeam2PlayerName.isEmpty())
    {
        qDebug() << "未选择球员，无法录入表现";
        return;
    }
    // 更新 Team1 球员的表现
    for(int i=0;i<l_Team1Players.size();i++)
    {
        if(l_Team1Players[i].getPlayerName() == str_PerformanceSelectTeam1PlayerName)
        {
            int i_Team1ThreePoints = ui->lineEditTeam1ThreePoints->text().toInt();

            int i_Team1Steals = ui->lineEditTeam1Steals->text().toInt();

            int i_Team1Dunks = ui->lineEditTeam1Dunks->text().toInt();

            int i_Team1Rebounds = ui->lineEditTeam1Rebounds->text().toInt();

            PlayerPerformance performance;

            performance.setThreePoints(i_Team1ThreePoints);

            performance.setSteals(i_Team1Steals);

            performance.setDunks(i_Team1Dunks);

            performance.setRebounds(i_Team1Rebounds);
            l_Team1Players[i].addPerformanceToList(performance);
            break;
        }
    }

    // 更新 Team2 球员的表现
    for (int i = 0; i < l_Team2Players.size(); ++i)
    {
        if(l_Team2Players[i].getPlayerName() == str_PerformanceSelectTeam2PlayerName)
        {
            int i_Team2ThreePoints = ui->lineEditTeam2ThreePoints->text().toInt();
            int i_Team2Steals = ui->lineEditTeam2Steals->text().toInt();
            int i_Team2Dunks = ui->lineEditTeam2Dunks->text().toInt();
            int i_Team2Rebounds = ui->lineEditTeam2Rebounds->text().toInt();
            PlayerPerformance performance;
            performance.setThreePoints(i_Team2ThreePoints);
            qDebug()<<"i_Team2ThreePoints:"<<i_Team2ThreePoints;
            qDebug()<<"场次表现 三分球performance.getThreePoints()："<<performance.getThreePoints();
            performance.setSteals(i_Team2Steals);
            performance.setDunks(i_Team2Dunks);
            performance.setRebounds(i_Team2Rebounds);
            l_Team2Players[i].addPerformanceToList(performance);

            break;
        }
    }
    //将球员场次表现录入之后清空文本框，方便下一个球员录入
    ui->lineEditTeam1ThreePoints->clear();
    ui->lineEditTeam1Steals->clear();
    ui->lineEditTeam1Dunks->clear();
    ui->lineEditTeam1Rebounds->clear();

    ui->lineEditTeam2ThreePoints->clear();
    ui->lineEditTeam2Steals->clear();
    ui->lineEditTeam2Dunks->clear();
    ui->lineEditTeam2Rebounds->clear();
}


void MatchPlayersManagerDialog::on_pushButtonInputComplete_clicked()
{

    // 强制刷新表格以确保显示更新
    ui->tableWidgetPerformance->viewport()->update();

    // 恢复临时删除的球员（如果有）
    Match& selectedMatch = getSelectedMatch();
    if (selectedMatch.getMatchID() == 0) return;

    // 获取 Team1 和 Team2
    Team& team1 = selectedMatch.getTeam1();
    Team& team2 = selectedMatch.getTeam2();

    qDebug()<<"**********team1.getTeamID()"<<team1.getTeamID();
    qDebug()<<"*********team1.getTeamPlayers()[0].getPlayerID()"<<team1.getTeamPlayers()[0].getPlayerID();
    qDebug()<<"team1.getTeamPlayers().size()"<<team1.getTeamPlayers().size();
    for(int i=0;i<team1.getTeamPlayers().size();i++)
    {
        int currentRow = ui->tableWidgetPerformance->rowCount();
        ui->tableWidgetPerformance->insertRow(currentRow);

        Player currentPlayer = team1.getTeamPlayers()[i];

        PlayerPerformance pp_SinglePerformance = currentPlayer.getPerformance();

        QTableWidgetItem *playerNameItem = new QTableWidgetItem(currentPlayer.getPlayerName());

        QTableWidgetItem *playerIDItem = new QTableWidgetItem(QString::number(currentPlayer.getPlayerID()));
        QTableWidgetItem *teamNameItem = new QTableWidgetItem(team1.getTeamName());
        QTableWidgetItem *threePointsItem = new QTableWidgetItem(QString::number( pp_SinglePerformance.getThreePoints()));
        QTableWidgetItem *reboundsItem = new QTableWidgetItem(QString::number( pp_SinglePerformance.getRebounds()));
        QTableWidgetItem *stealsItem = new QTableWidgetItem(QString::number( pp_SinglePerformance.getSteals()));
        QTableWidgetItem *dunksItem = new QTableWidgetItem(QString::number( pp_SinglePerformance.getDunks()));
        // 将项目插入到表格中的相应位置
        ui->tableWidgetPerformance->setItem(currentRow, 0, playerNameItem);
        ui->tableWidgetPerformance->setItem(currentRow, 1, playerIDItem);
        ui->tableWidgetPerformance->setItem(currentRow, 2, teamNameItem);
        ui->tableWidgetPerformance->setItem(currentRow, 3, threePointsItem);
        ui->tableWidgetPerformance->setItem(currentRow, 4, reboundsItem);
        ui->tableWidgetPerformance->setItem(currentRow, 5, stealsItem);
        ui->tableWidgetPerformance->setItem(currentRow, 6, dunksItem);
    }

    for(int i=0;i<team2.getTeamPlayers().size();i++)
    {
        int currentRow = ui->tableWidgetPerformance->rowCount();
        ui->tableWidgetPerformance->insertRow(currentRow);

        Player currentPlayer = team2.getTeamPlayers()[i];
        QTableWidgetItem *playerNameItem = new QTableWidgetItem(currentPlayer.getPlayerName());
        QTableWidgetItem *playerIDItem = new QTableWidgetItem(QString::number(currentPlayer.getPlayerID()));
        QTableWidgetItem *teamNameItem = new QTableWidgetItem(team2.getTeamName());
        QTableWidgetItem *threePointsItem = new QTableWidgetItem(QString::number(currentPlayer.getPerformance().getThreePoints()));
        QTableWidgetItem *reboundsItem = new QTableWidgetItem(QString::number(currentPlayer.getPerformance().getRebounds()));
        QTableWidgetItem *stealsItem = new QTableWidgetItem(QString::number(currentPlayer.getPerformance().getSteals()));
        QTableWidgetItem *dunksItem = new QTableWidgetItem(QString::number(currentPlayer.getPerformance().getDunks()));
        // 将项目插入到表格中的相应位置
        ui->tableWidgetPerformance->setItem(currentRow, 0, playerNameItem);
        ui->tableWidgetPerformance->setItem(currentRow, 1, playerIDItem);
        ui->tableWidgetPerformance->setItem(currentRow, 2, teamNameItem);
        ui->tableWidgetPerformance->setItem(currentRow, 3, threePointsItem);
        ui->tableWidgetPerformance->setItem(currentRow, 4, reboundsItem);
        ui->tableWidgetPerformance->setItem(currentRow, 5, stealsItem);
        ui->tableWidgetPerformance->setItem(currentRow, 6, dunksItem);
    }

    // 获取 Team1 和 Team2 的球员列表
    QList<Player>& team1Players = team1.getTeamPlayers();
    QList<Player>& team2Players = team2.getTeamPlayers();

    // 恢复 Team1 删除的球员
    if (!m_TempRemoveTeam1PLayers.isEmpty()) {
        for (const Player& player : m_TempRemoveTeam1PLayers) {
            team1Players.append(player);
        }
        m_TempRemoveTeam1PLayers.clear();  // 清空临时删除的列表
    }

    // 恢复 Team2 删除的球员
    if (!m_TempRemoveTeam2PLayers.isEmpty()) {
        for (const Player& player : m_TempRemoveTeam2PLayers) {
            team2Players.append(player);
        }
        m_TempRemoveTeam2PLayers.clear();  // 清空临时删除的列表
    }

    // 删除临时新增的球员（Team1）
    if (!m_TempAddTeam1Players.isEmpty()) {
        for (const Player& playerToRemove : m_TempAddTeam1Players) {
            for (int j = 0; j < team1Players.size(); ++j) {
                if (team1Players[j].getPlayerID() == playerToRemove.getPlayerID()) {
                    team1Players.removeAt(j);  // 从 Team1 中移除这个球员
                    --j;  // 调整索引防止跳过元素
                }
            }
        }
        m_TempAddTeam1Players.clear();
    }

    // 删除临时新增的球员（Team2）
    if (!m_TempAddTeam2Players.isEmpty()) {
        for (const Player& playerToRemove : m_TempAddTeam2Players) {
            for (int j = 0; j < team2Players.size(); ++j) {
                if (team2Players[j].getPlayerID() == playerToRemove.getPlayerID()) {
                    team2Players.removeAt(j);  // 从 Team2 中移除这个球员
                    --j;  // 调整索引防止跳过元素
                }
            }
        }
        m_TempAddTeam2Players.clear();
    }

    // 再次刷新表格，确保所有操作后数据是最新的
    ui->tableWidgetPerformance->viewport()->update();
}

