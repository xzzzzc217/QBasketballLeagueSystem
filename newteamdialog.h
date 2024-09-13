#ifndef NEWTEAMDIALOG_H
#define NEWTEAMDIALOG_H

#include <QDialog>
#include"addplayerdialog.h"
#include "player.h"
#include"team.h"
namespace Ui {
class NewTeamDialog;
}

class NewTeamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTeamDialog(QWidget *parent = nullptr);
    ~NewTeamDialog();
    Team m_CurrentTeam;//表示新增球队对话框正在编辑的球队对象

private slots:

    void on_pushButtonAddPlayer_clicked();//新增球队-新增队员

    void on_buttonBox_accepted();//下方的确定按钮

private:
    Ui::NewTeamDialog *ui;
};

#endif // NEWTEAMDIALOG_H
