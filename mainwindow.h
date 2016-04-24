#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_lineEditEps_editingFinished();

    void on_lineEditStep_editingFinished();

    void on_lineEditColNum_editingFinished();

    void on_lineEdit_editingFinished();

    void on_pushButtonSave_clicked();

    void on_pushButton_3_clicked();

    void on_lineEditReadFile_textChanged(const QString &arg1);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_lineEdit_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;

public:
    void readFile(QString nameFileOpen);
};

#endif // MAINWINDOW_H
