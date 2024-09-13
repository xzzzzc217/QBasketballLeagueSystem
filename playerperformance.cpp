/**
 * @file playerperformance.cpp
 * @brief PlayerPerformance 类的实现文件
 *
 * 该文件实现了 PlayerPerformance 类，主要用于记录球员在单场比赛中的表现数据。每个 PlayerPerformance
 * 对象包含球员在比赛中的三分球、篮板、扣篮和抢断等统计数据。该类提供了相应的 setter 和 getter 函数来
 * 设置和获取这些数据，并且提供了一个函数用于将其他 PlayerPerformance 对象的表现数据传递给当前对象。
 *
 * PlayerPerformance 类的功能包括设置和获取比赛中的各项表现数据，如三分球、篮板、扣篮和抢断。
 *
 * 文件中的主要函数：
 * - setThreePoints()：设置球员的三分球得分。
 * - setRebounds()：设置球员的篮板数。
 * - setDunks()：设置球员的扣篮数。
 * - setSteals()：设置球员的抢断数。
 * - getThreePoints()：获取球员的三分球得分。
 * - getRebounds()：获取球员的篮板数。
 * - getDunks()：获取球员的扣篮数。
 * - getSteals()：获取球员的抢断数。
 * - deliverPerformance()：将另一个 PlayerPerformance 对象的表现数据赋值给当前对象。原名为addPerformance()
 * - addPerformance():deliverPerformance()的前身
 * 原代码：
 *      {
 *          m_ThreePoints += pp_other.getThreePoints();
            m_Rebounds += pp_other.getRebounds();
            m_Dunks += pp_other.getDunks();
            m_Steals += pp_other.getSteals();
        }
 *
 * 依赖项：
 * - playerperformance.h：包含 PlayerPerformance 类声明的头文件。
 *
 * 作者: 赵子辰
 * @date 2024-09-10
 */

#include "playerperformance.h"

PlayerPerformance::PlayerPerformance()
    :m_ThreePoints(0),m_Rebounds(0),m_Dunks(0),m_Steals(0)
{}
void PlayerPerformance::setThreePoints(int newThreePoints)
{
    m_ThreePoints = newThreePoints;
}

void PlayerPerformance::setRebounds(int newRebounds)
{
    m_Rebounds = newRebounds;
}

void PlayerPerformance::setDunks(int newDunks)
{
    m_Dunks = newDunks;
}

void PlayerPerformance::setSteals(int newSteals)
{
    m_Steals = newSteals;
}
int PlayerPerformance::getThreePoints() const
{
    return m_ThreePoints;
}

int PlayerPerformance::getRebounds() const
{
    return m_Rebounds;
}

int PlayerPerformance::getDunks() const
{
    return m_Dunks;
}

int PlayerPerformance::getSteals() const
{
    return m_Steals;
}

void PlayerPerformance::deliverPerformance(const PlayerPerformance& pp_other)//other是一个常量引用类型的PlayerPerformance对象，表示传入的对象不会被修改
{                      //原名为addPerformance
    m_ThreePoints = pp_other.getThreePoints();
    m_Rebounds = pp_other.getRebounds();
    m_Dunks = pp_other.getDunks();
    m_Steals = pp_other.getSteals();
}

