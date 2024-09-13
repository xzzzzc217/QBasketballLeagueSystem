/**
 * @file team.cpp
 * @brief Team 类的实现文件
 *
 * 该文件实现了 Team 类的功能，主要用于管理球队的信息和球员列表。每个 Team 对象表示一支球队，
 * 包括球队的名称、ID，以及球队的球员列表。此外，Team 类还维护了一个静态的球队列表，
 * 用于管理所有的球队。
 *
 * Team 类的功能包括设置和获取球队的名称和 ID，添加或移除球员，获取球员列表，以及将球队添加或移除到全局的球队列表中。
 *
 * 文件中的主要函数：
 * - setTeamName()：设置球队的名称。
 * - setTeamID()：设置球队的编号。
 * - getTeamName()：获取球队的名称。
 * - getTeamID()：获取球队的编号。
 * - addTeamPlayer()：将球员添加到球队的球员列表中。
 * - removeTeamPlayer()：根据球员姓名从球队的球员列表中移除球员。
 * - getTeamPlayers()：获取球队的球员列表。
 * - addTeam()：将新球队添加到全局的球队列表中。
 * - removeTeam()：根据球队名称从全局球队列表中删除球队。
 * - getTeamList()：获取所有球队的列表。
 * - populateTeamComboBox()：将球队名称填充到 QComboBox 中，以便选择球队。
 * - setTeamPlayers()：设置球队的球员列表。
 *
 * 依赖项：
 * - team.h：包含 Team 类声明的头文件。
 * - player.h：包含 Player 类声明的头文件，Player 类用于表示球员。
 * - qcombobox.h：用于操作 QComboBox 小部件，以显示和选择球队。
 *
 * 静态成员：
 * - m_TeamList：保存所有球队的全局静态列表。
 *
 * 作者: 赵子辰
 * @date 2024-09-10
 */

#include "team.h"
#include"QString"

QList<Team> Team::m_TeamList;  // 静态成员球队列表初始化

Team::Team() {}
//setter
void Team::setTeamName(const QString &newTeamName)//设置Team属性队名
{
    m_TeamName=newTeamName;
}

void Team::setTeamID(int newTeamID)//设置Team属性编号
{
    m_TeamID=newTeamID;
}

//getter
QString Team::getTeamName() const//获取Team属性队名
{
    return  m_TeamName;
}

int Team::getTeamID()const//获取Team属性编号
{
    return m_TeamID;
}

// 添加球员
void Team::addTeamPlayer(const Player &newPlayer)
{
    m_TeamPlayers.append(newPlayer);//将新的球员newPlayer加入队伍球员列表
}

// 移除球员
bool Team::removeTeamPlayer(const QString &playerName)
{
    for (int i = 0; i < m_TeamPlayers.size(); ++i)
    {
        if (m_TeamPlayers[i].getPlayerName() == playerName)
        {
            m_TeamPlayers.removeAt(i);//按球员名字将球员从球员列表中删除
            return true;
        }
    }
    return false;
}

// 获取球员列表
QList<Player>& Team::getTeamPlayers()
{
    return m_TeamPlayers;
}


//添加球队
void Team::addTeam(const Team &newTeam)
{
    m_TeamList.append(newTeam);// 将新球队添加到 m_TeamLists
}

//删除球队
void Team::removeTeam(const QString &teamName)
{
    for(int i=0;i<m_TeamList.size();i++)
    {
        if (m_TeamList[i].getTeamName() == teamName)
        {
            m_TeamList.remove(i);//按球队名字将球队从球队列表中删除
            break;
        }

    }
}

QList<Team> Team::getTeamList()//获取球队列表m_TeamList
{
    return m_TeamList;
}

void Team::populateTeamComboBox(QComboBox *comboBox)
{
    comboBox->clear();  // 清空 QComboBox 中的项目

    QList<Team> teamList = getTeamList();  // 获取队伍列表
    for (const Team &team : teamList)
    {
        comboBox->addItem(team.getTeamName());  // 将队伍名称添加到 QComboBox 中
    }
}


void Team::setTeamPlayers(const QList<Player>& players)
{
    m_TeamPlayers = players;  // 更新球员列表
}
