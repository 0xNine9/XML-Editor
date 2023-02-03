#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <string>
#include "tree.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_As_triggered();

    void on_actionExit_triggered();

    void on_actionSave_triggered();

    void on_actionCompress_triggered();

    void on_actionDecompress_triggered();

    void on_actionConvert_to_JSON_triggered();

    void on_actionFormat_triggered();

    void on_actionCheck_triggered();

    void on_actionMinify_triggered();
    bool checkUiText(std::string msg);
    void on_pushButton_clicked();

    void on_moastActiveUserButton_clicked();

    void on_mostInfUserButton_clicked();

    void on_resetButton_clicked();

    void on_mutualFollwersButton_clicked();

    void on_sf_clicked();

private:
    Ui::MainWindow *ui;
    QString currentFile = "";
};
#endif // MAINWINDOW_H
