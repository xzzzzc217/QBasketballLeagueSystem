#include "removeteamdialog.h"
#include "ui_removeteamdialog.h"

RemoveTeamDialog::RemoveTeamDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RemoveTeamDialog)
{
    ui->setupUi(this);
}

RemoveTeamDialog::~RemoveTeamDialog()
{
    delete ui;
}

void RemoveTeamDialog::populateTeamList()//往combobox填充teamlist列表
{
    QList<Team> teamList = Team::getTeamList();//从Team类获取teamlist球队列表
    for(const Team &team:teamList)
    {
        ui->comboBoxSelectTeam->addItem(team.getTeamName());//填充进combobox
    }

}
void RemoveTeamDialog::on_buttonBox_accepted()//删除按钮槽函数
{
    //获取用户选中的teamName
    QString selectedTeamName = ui->comboBoxSelectTeam->currentText();

    //遍历球队列表teamlist找到要删除的球队名字
    for(int i=0;i<Team::m_TeamList.size();++i)
    {
        if(Team::m_TeamList[i].getTeamName()==selectedTeamName)//找到要删除的对象
        {
            Team::m_TeamList.removeAt(i);
        }

    }

}

