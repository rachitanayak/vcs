#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QComboBox>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openfile_clicked();

    void on_actionRedo_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionSave_triggered();

    void on_actionCommit_triggered();

    void on_view_clicked();

    void on_revert_clicked();

    void on_actionPush_triggered();

    void on_pull_clicked();



private:
    Ui::MainWindow *ui;
    QString mFilename;
};

#endif // MAINWINDOW_H
