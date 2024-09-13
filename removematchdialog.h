#ifndef REMOVEMATCHDIALOG_H
#define REMOVEMATCHDIALOG_H

#include <QDialog>
#include"match.h"
namespace Ui {
class RemoveMatchDialog;
}

class RemoveMatchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveMatchDialog(QWidget *parent = nullptr);
    ~RemoveMatchDialog();
    void populateMatchList();//将matchlist填充进combobox

private slots:
    void on_buttonBox_accepted();//删除按钮槽函数

private:
    Ui::RemoveMatchDialog *ui;
};

#endif // REMOVEMATCHDIALOG_H
