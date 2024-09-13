#ifndef MATCHPLAYERSMANAGERDIALOG_H
#define MATCHPLAYERSMANAGERDIALOG_H
#include<QFileDialog>
#include <QDialog>
#include"match.h"
namespace Ui {
class MatchPlayersManagerDialog;
}

class MatchPlayersManagerDialog : public QDialog
{
    Q_OBJECT

public:
    QList<Player> m_TempRemoveTeam1PLayers; //球员列表，存储临时删除的team1球员
    QList<Player> m_TempRemoveTeam2PLayers; //球员列表，存储临时删除的team2球员
    QList<Player> m_TempAddTeam1Players;    //球员列表，存储临时新增的team1球员
    QList<Player> m_TempAddTeam2Players;    //球员列表，存储临时新增的team2球员
    explicit MatchPlayersManagerDialog(QWidget *parent = nullptr);
    ~MatchPlayersManagerDialog();
    void populateMatchID();//将比赛编号填充进combobox

    Match& getSelectedMatch();//提取代码复用部分，该函数用于获取选中的比赛场次
    void refreshPlayerList();//更新列表函数

private slots:
    void on_buttonBoxSelectMatchID_accepted();//确定选中的比赛场次编号

    void on_buttonBoxAdd_accepted();//确定临时新增球队球员

    void on_buttonBoxPerformance_accepted();//对球员场次表现赋值

    void on_buttonBoxRemove_accepted();//确定删除球员

    void on_pushButtonInputComplete_clicked();//确定录入完成

    void on_pushButtonNotRemove_clicked();//选择不移除球员



private:
    Ui::MatchPlayersManagerDialog *ui;

};

#endif // MATCHPLAYERSMANAGERDIALOG_H
