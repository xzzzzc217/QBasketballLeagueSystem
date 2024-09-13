#include "addplayerdialog.h"
#include "ui_addplayerdialog.h"

AddPlayerDialog::AddPlayerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddPlayerDialog)
{
    ui->setupUi(this);

}
//获取用户输入的信息 返回Player对象
Player AddPlayerDialog:: getPlayer()
{
    //Player newPlayer = AddPlayerDialog.getPlayer();  // 获取新添加的球员信息 具体应在addplayerdialog类中实现
    Player newPlayer;//将要被添加的球员
    newPlayer.setPlayerAge(ui->lineEditPlayerAge->text().toInt());//从addplayerdialog.ui获取playerage,并返回给newPlayer的属性m_PlayerAge
    newPlayer.setPlayerID(ui->lineEditPlayerID->text().toInt());
    newPlayer.setPlayerName(ui->lineEditPlayerName->text());


    return newPlayer;  // 在函数末尾返回 newPlayer 对象

}
AddPlayerDialog::~AddPlayerDialog()
{
    delete ui;
}
