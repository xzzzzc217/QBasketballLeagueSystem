#include "newteamdialog.h"
#include "ui_newteamdialog.h"
#include "addplayerdialog.h"
#include "player.h"// 引入 Player 类
#include<QDebug>
NewTeamDialog::NewTeamDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewTeamDialog)
{
    ui->setupUi(this);
}

NewTeamDialog::~NewTeamDialog()
{
    delete ui;
}

void NewTeamDialog::on_pushButtonAddPlayer_clicked()//新增球队-新增队员
{
    //显示对话框
    AddPlayerDialog AddPlayerDialog(this);

    if (AddPlayerDialog.exec() == QDialog::Accepted)
    {  // 如果用户点击了“确定”
        Player newPlayer = AddPlayerDialog.getPlayer();  // 获取新添加的球员信息 具体应在addplayerdialog类中实现

        //将新球员添加到当前球队的球员列表
        m_CurrentTeam.addTeamPlayer(newPlayer);//每次点击“新增队员”，新队员就会添加到m_CurrentTeam的m_TeamList
        // 在表格中新增一行
        int currentRow = ui->ShowPlayerstableWidget->rowCount();
        ui->ShowPlayerstableWidget->insertRow(currentRow);

        // 将球员信息添加到表格中的对应列
        ui->ShowPlayerstableWidget->setItem(currentRow, 0, new QTableWidgetItem(QString::number(newPlayer.getPlayerID())));
        ui->ShowPlayerstableWidget->setItem(currentRow, 1, new QTableWidgetItem(newPlayer.getPlayerName()));
        ui->ShowPlayerstableWidget->setItem(currentRow, 2, new QTableWidgetItem(QString::number(newPlayer.getPlayerAge())));

    }
}


void NewTeamDialog::on_buttonBox_accepted()//用户点击确定
{
    // 获取用户输入的球队编号和名称
    QString teamName = ui->lineEditTeamName->text();
    int teamID = ui->lineEditTeamID->text().toInt();

    m_CurrentTeam.setTeamName(teamName);
    m_CurrentTeam.setTeamID(teamID);
    //到此m_CurrentTeam的所有属性都正确赋值了，包括TeamName,TeamID,m_TeamPlayers
    // 添加球队到列表
    Team::m_TeamList.append(m_CurrentTeam);//将这个完整的球队添加到队伍列表中

    // 输出调试信息，确保球队已被添加
    qDebug() << "Added team:" << teamName << "with ID:" << teamID;

    // 关闭对话框
    this->accept();  // 或者使用 this->close();
}

