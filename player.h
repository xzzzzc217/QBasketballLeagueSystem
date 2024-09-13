#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include "playerperformance.h"
#include"QList"
class Player
{
public:
    // 构造函数
    Player();


    // Setter 成员函数
    void setPlayerName(const QString &newPlayerName);
    void setPlayerAge(int newPlayerAge);
    void setPlayerID(int newPlayerID);

    // Getter 成员函数
    QString getPlayerName() const;
    int getPlayerAge() const;
    int getPlayerID() const;

    // 添加比赛表现到m_Performances
    void addPerformanceToList(const PlayerPerformance& performance);
    // 获取单个场次表现
    PlayerPerformance getPerformance();
    QList<PlayerPerformance> m_Performances;// 存储该球员的所有比赛表现
private:
    // 成员属性
    QString m_PlayerName;   // 球员姓名
    int m_PlayerAge;        // 球员年龄
    int m_PlayerID;         // 球员编号
};

#endif // PLAYER_H
