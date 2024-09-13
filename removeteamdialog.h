#ifndef REMOVETEAMDIALOG_H
#define REMOVETEAMDIALOG_H
#include"team.h"
#include <QDialog>

namespace Ui {
class RemoveTeamDialog;
}

class RemoveTeamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveTeamDialog(QWidget *parent = nullptr);
    ~RemoveTeamDialog();
    void populateTeamList();//填充球队列表，用于在移除球队的combobox中展示

private slots:
    void on_buttonBox_accepted();//删除按钮槽函数：球队管理-RemoveTeam-确定

private:
    Ui::RemoveTeamDialog *ui;
};

#endif // REMOVETEAMDIALOG_H
