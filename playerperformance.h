//此文件用来实现运动员的得分属性
#ifndef PLAYERPERFORMANCE_H
#define PLAYERPERFORMANCE_H

class PlayerPerformance
{
public:
    PlayerPerformance();
    int m_ThreePoints;      // 三分球个数
    int m_Rebounds;         // 篮板球个数
    int m_Dunks;            // 扣篮次数
    int m_Steals;           // 抢断次数

    //getter
    int getThreePoints() const;//获取三分球数量
    int getRebounds() const;//获取篮板球数量
    int getDunks() const;//获取扣篮数量
    int getSteals() const;//获取抢断球数量

    //setter
    void setThreePoints(int i_NewThreePoints);//设置三分球数量
    void setRebounds(int i_NewRebounds);//设置篮板球数量
    void setDunks(int i_NewDunks);//设置扣篮数量
    void setSteals(int i_NewSteals);//设置抢断球数量
    //
    void deliverPerformance(const PlayerPerformance& other);//用于将某球员在所有场次的场次表现中 三分球 抢断球等数据的相加


};
#endif  // PLAYERPERFORMANCE_H

