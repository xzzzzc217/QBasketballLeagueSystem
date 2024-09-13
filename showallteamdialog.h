#ifndef SHOWALLTEAMDIALOG_H
#define SHOWALLTEAMDIALOG_H
#include"team.h"
#include <QDialog>
#include"QList"
#include<QFileDialog>

namespace Ui {
class ShowAllTeamDialog;
}

class ShowAllTeamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowAllTeamDialog(QWidget *parent = nullptr);
    ~ShowAllTeamDialog();
    //在类内部声明函数
    void populateShowAllTeamTable();//填充tableWidgetShowAllTeam的函数
    void exportTeams();//导出球员数据
    void importTeams();//导入球队数据函数
private slots:
    void on_pushButtonExport_clicked();//点击“导出”

    void on_pushButtonImport_clicked();//点击“导入”将数据导入到table中

private:
    Ui::ShowAllTeamDialog *ui;
};

#endif // SHOWALLTEAMDIALOG_H
