#include "removematchdialog.h"
#include "ui_removematchdialog.h"

RemoveMatchDialog::RemoveMatchDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RemoveMatchDialog)
{
    ui->setupUi(this);
}

RemoveMatchDialog::~RemoveMatchDialog()
{
    delete ui;
}
void RemoveMatchDialog::populateMatchList()//将matchlist填充进combobox
{
    QList<Match>matchList = Match::getMatchList();//获取场次列表
    for(Match match:matchList)
    {
        ui->comboBoxSelectMatch->addItem(QString::number(match.getMatchID()));
    }
}
void RemoveMatchDialog::on_buttonBox_accepted()//确定删除选中的比赛场次
{
    //获取用户选中删除的matchID
    QString str_SelectMatchID = ui->comboBoxSelectMatch->currentText();//获取str类变量
    int i_SelectMatchID = str_SelectMatchID.toInt();
    for(int i=0;i<Match::m_MatchList.size();i++)
        if(Match::m_MatchList[i].getMatchID() == i_SelectMatchID)
        {
            Match::m_MatchList.removeAt(i);//根据比赛编号删除比赛
        }
}

