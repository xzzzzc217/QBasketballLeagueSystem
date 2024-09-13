#ifndef ADDMATCHDIALOG_H
#define ADDMATCHDIALOG_H
#include"QList"
#include <QDialog>
#include"team.h"
#include"match.h"

namespace Ui {
class AddMatchDialog;
}

class AddMatchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddMatchDialog(QWidget *parent = nullptr);
    ~AddMatchDialog();
    void AddMatchTeam1Options();//为combobox1填充
    void AddMatchTeam2Options();//为combobox2填充
private slots:
    void on_buttonBox_accepted();//点击菜单上的addMatch

private:
    Ui::AddMatchDialog *ui;
    Match m_CurrentMatch;//设置addMatchDialog对话框当前编辑的比赛场次

};

#endif // ADDMATCHDIALOG_H
