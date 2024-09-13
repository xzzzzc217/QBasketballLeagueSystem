#ifndef ADDPLAYERDIALOG_H
#define ADDPLAYERDIALOG_H
#include"player.h"
#include <QDialog>
#include"team.h"
namespace Ui {
class AddPlayerDialog;
}

class AddPlayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPlayerDialog(QWidget *parent = nullptr);
    ~AddPlayerDialog();
    Player getPlayer();//获取用户输入的信息 返回Player对象


private:
    Ui::AddPlayerDialog *ui;
};

#endif // ADDPLAYERDIALOG_H
