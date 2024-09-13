/**
 * @file match.cpp
 * @brief Match 类的实现文件
 *
 * 该文件实现了 Match 类，负责管理比赛的基本信息及相关操作。Match 类包括比赛的编号、日期、地点以及两支参赛队伍。
 * 此外，Match 类定义了一个全局静态比赛列表，用于存储所有的比赛数据。
 *
 * Match 类的功能包括设置和获取比赛的相关属性（如比赛ID、日期、地点、参赛队伍等），
 * 以及管理比赛列表的功能（如添加和删除比赛）。
 *
 * 文件中的主要函数：
 * - setMatchID()：设置比赛的编号。
 * - setMatchDate()：设置比赛的日期。
 * - setMatchSite()：设置比赛的地点。
 * - setTeam1()：设置比赛的第一支参赛队伍。
 * - setTeam2()：设置比赛的第二支参赛队伍。
 * - getMatchID()：获取比赛的编号。
 * - getMatchDate()：获取比赛的日期。
 * - getMatchSite()：获取比赛的地点。
 * - getTeam1()：获取比赛的第一支参赛队伍。
 * - getTeam2()：获取比赛的第二支参赛队伍。
 * - addMatch()：将一场比赛添加到比赛列表中。
 * - removeMatch()：根据比赛编号从列表中删除比赛。
 * - getMatchList()：获取所有比赛的列表。
 *
 * 依赖项：
 * - match.h：包含 Match 类声明的头文件。
 * - team.h：包含 Team 类声明的头文件，Team 类用于表示参赛队伍。
 *
 * 静态成员：
 * - m_MatchList：保存所有比赛的全局静态列表。
 *
 * 作者: 赵子辰
 * @date 2024-09-10
 */

#include "match.h"

Match::Match() {}

QList<Match> Match::m_MatchList;  // 定义静态成员变量

//setter函数实现
void Match::setMatchID(int newMatchID)//设置Match编号
{
    m_MatchID = newMatchID;
}

void Match::setMatchDate(QDate newMatchDate)//设置match时间
{
    m_MatchDate = newMatchDate;
}

void Match::setMatchSite(QString newMatchSite)//设置match地点
{
    m_MatchSite = newMatchSite;
}

void Match::setTeam1(Team newTeam1)//设置参赛队伍1
{
    m_Team1 = newTeam1;
}

void Match::setTeam2(Team newTeam2)//设置参赛队伍2
{
    m_Team2 = newTeam2;
}
//getter函数实现
int Match::getMatchID()const //获取match编号
{
    return m_MatchID;
}

QDate Match::getMatchDate()const//获取match时间
{
    return m_MatchDate;
}

QString Match::getMatchSite()const//获取match地点
{
    return m_MatchSite;
}

Team& Match::getTeam1()//获取参赛队伍1
{
    return m_Team1;
}

Team& Match::getTeam2()//获取参赛队伍2
{
    return m_Team2;
}

//管理MatchList列表的函数
void Match::addMatch(Match newMatch)//添加match到列表
{
    m_MatchList.append(newMatch);
}

void Match::removeMatch(int matchID)//删除列表中的球队
{
    for(int i=0;i<m_MatchList.size();++i)
    {
        if(m_MatchList[i].getMatchID() == matchID)
        {
            m_MatchList.removeAt(i);//按编号删除场次
        }
    }
}


QList<Match>& Match::getMatchList()
{
    // 返回比赛列表的非const引用，允许修改
    return m_MatchList;
}
