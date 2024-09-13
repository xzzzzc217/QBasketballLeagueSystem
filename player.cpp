/**
 * @file player.cpp
 * @brief Player 类的实现文件
 *
 * 该文件实现了 Player 类的构造函数、成员变量的 Getter 和 Setter 方法，
 * 以及处理球员比赛表现的相关功能。每个球员的比赛表现被记录在一个 PlayerPerformance 对象中，并存储在列表中。
 *
 * Player 类的功能包括设置和获取球员的基本信息（如姓名、年龄、ID），并将球员的单场比赛表现添加到表现列表中。
 * 通过 getPerformance() 函数，可以获取并计算球员的总表现。
 *
 * 文件中的主要函数：
 * - setPlayerName()：设置球员的姓名。
 * - setPlayerAge()：设置球员的年龄。
 * - setPlayerID()：设置球员的 ID。
 * - getPlayerName()：获取球员的姓名。
 * - getPlayerAge()：获取球员的年龄。
 * - getPlayerID()：获取球员的 ID。
 * - addPerformanceToList()：将一场比赛的表现添加到球员的表现列表中。
 * - getPerformance()：返回球员的表现。原名为calculateTotalPerformance()
 * - calculateTotalPerformance():getPerformance()的前身，设计用来遍历某球员在所有场次的performance聚合而成的m_Performance列表并对应相加
 *
 * 依赖项：
 * - player.h：包含 Player 类声明的头文件。
 * - playerperformance.h：定义 PlayerPerformance 类的头文件，用于记录球员的单场比赛表现。
 *
 * 作者: 赵子辰
 * @date 2024-09-10
 */

#include "player.h"
#include <QDebug>

// 构造函数实现
Player::Player() {}

// Setter 成员函数实现
void Player::setPlayerName(const QString &newPlayerName)
{
    m_PlayerName = newPlayerName;
}

void Player::setPlayerAge(int newPlayerAge)
{
    m_PlayerAge = newPlayerAge;
}

void Player::setPlayerID(int newPlayerID)
{
    m_PlayerID = newPlayerID;
}

// Getter 成员函数实现
QString Player::getPlayerName() const
{
    return m_PlayerName;
}

int Player::getPlayerAge() const
{
    return m_PlayerAge;
}

int Player::getPlayerID() const
{
    return m_PlayerID;
}

void Player::addPerformanceToList(const PlayerPerformance& performance)//将单场比赛的表现添加到球员的表现列表中
{
    m_Performances.append(performance);//将球员在单场比赛中的表现数据作为一个PlayerPerformance对象储存在m_Performances列表中
    //其实每个球员的m_Performance就有一个performance
}

PlayerPerformance Player::getPerformance()//原名为calculateTotalPerformance()
{
    PlayerPerformance pp_SinglePerformance;

    //只是将pp对象的performance赋值给pp_SinglePerformance
    for (const PlayerPerformance& performance : m_Performances)
    {
        pp_SinglePerformance.deliverPerformance(performance); // 将performance的属性传递给pp_SinglePerformance
    }

    return pp_SinglePerformance;//pp对象
}


