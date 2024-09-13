/**
 * @file showallmatchdialog.cpp
 * @brief ShowAllMatchDialog 类的实现文件
 *
 * 该文件实现了 ShowAllMatchDialog 类，用于显示、导入和导出所有比赛信息。比赛信息通过表格（QTableWidget）展示，
 * 用户可以导入或导出比赛数据，包括比赛的编号、日期、地点，以及参赛队伍信息。
 *
 * 文件中的主要功能：
 * - populateShowAllMatchTable()：初始化表格，填充所有比赛的信息。
 * - exportMatches()：导出比赛信息到文本文件，供用户保存。
 * - importMatches()：从文本文件中导入比赛信息，并更新全局比赛列表。
 *
 * 依赖项：
 * - showallmatchdialog.h：包含 ShowAllMatchDialog 类声明的头文件。
 * - match.h：用于操作 Match 类，管理比赛及其相关信息。
 * - team.h：用于操作 Team 类，管理球队信息。
 *
 * 作者: 赵子辰
 * @date 2024-09-10
 */

#ifndef SHOWALLMATCHDIALOG_H
#define SHOWALLMATCHDIALOG_H
#include"match.h"
#include <QDialog>
#include<QFileDialog>
namespace Ui {
class ShowAllMatchDialog;
}

class ShowAllMatchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowAllMatchDialog(QWidget *parent = nullptr);
    ~ShowAllMatchDialog();
    void populateShowAllMatchTable();//用于填充tableWidget的函数
    void importMatches();//用于将场次数据导入的函数
    void exportMatches();//将场次信息导出

private slots:
    void on_pushButtonExport_clicked();//点击导出的槽函数

    void on_pushButtonImport_clicked();//点击导入的槽函数

private:
    Ui::ShowAllMatchDialog *ui;
};

#endif // SHOWALLMATCHDIALOG_H
