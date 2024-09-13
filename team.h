#ifndef TEAM_H
#define TEAM_H
#include"QString"
#include"QList"
#include"player.h"
#include"QComboBox"
class Team
{
public:
    Team();

    static QList<Team> m_TeamList;//队伍列表，保存所有队伍
    QList<Player> m_TeamPlayers; // 球员列表，存储某个Team所有Players。且最重要的是若加上了static声明会出现共享错误问题

    //setter
    void setTeamName(const QString &newName);
    void setTeamID(int newID);

    //getter
    QString getTeamName()const;
    int getTeamID()const;

    //管理m_teamPlayers的函数
    void addTeamPlayer(const Player &player); //添加球员到球队
    bool removeTeamPlayer(const QString &playerName);//删除球队球员   //在这里修改了const &
    QList<Player> &getTeamPlayers() ; // 获取球队中的球员列表

    //管理m_TeamList的函数
    static void addTeam(const Team &team);           // 添加球队到列表
    static void removeTeam(const QString &teamName); // 删除球队
    static QList<Team> getTeamList();                // 获取球队列表

    // 声明一个静态函数，用于填充 QComboBox
    static void populateTeamComboBox(QComboBox *comboBox);//在addMatch新建场次时填充combobox,提供用户选择

    // 声明设置球员列表的函数
    void setTeamPlayers(const QList<Player>& players);
private:
    QString m_TeamName;//队伍名字
    int m_TeamID;//队伍编号

};

#endif // TEAM_H
