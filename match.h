#ifndef MATCH_H
#define MATCH_H
#include"QDate"
#include"QString"
#include"team.h"
#include"QList"
class Match
{
public:
    Match();

    static QList<Match> m_MatchList;//管理match对象的列表

    //setter
    void setMatchID(int newMatchID);//设置比赛编号
    void setMatchDate(QDate newMatchDate);//设置比赛时间
    void setMatchSite(QString newMatchSite);//设置比赛地点
    void setTeam1(Team m_Team1);//设置参赛队伍1
    void setTeam2(Team m_Team2);//设置参赛队伍2

    //getter
    int getMatchID()const;//获取比赛编号
    QDate getMatchDate()const;//获取比赛时间
    QString getMatchSite()const;//获取比赛地点
    Team& getTeam1();//获取参赛队伍1
    Team& getTeam2();//获取参赛队伍2
    //管理matchlist的函数
    static  QList<Match>& getMatchList();//获取matchList
    static void addMatch(Match newMatch);//添加match到列表
    static void removeMatch(int matchID);//从列表中删除match对象

private:
    //成员属性
    int m_MatchID;//比赛编号
    QDate m_MatchDate;//比赛时间
    QString m_MatchSite;//比赛地点

    Team m_Team1;//球队一
    Team m_Team2;//球队二

};

#endif // MATCH_H
