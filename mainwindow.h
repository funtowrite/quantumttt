#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}
class QGraph;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mark(int i);
    void trial();
    void markClassical(std::string n, int k);
    void translate(std::vector<int>);


private slots:
    void on_quantum1_clicked();
    void on_quantum2_clicked();
    void on_quantum3_clicked();
    void on_quantum4_clicked();
    void on_quantum5_clicked();
    void on_quantum6_clicked();
    void on_quantum7_clicked();
    void on_quantum8_clicked();
    void on_quantum9_clicked();
    void enable(int j, bool enabled);
    void on_submitBtn_clicked();

private:
    Ui::MainWindow *ui;
//    QGraph *graph;
//    ClassicalBoard *board;
};

#endif // MAINWINDOW_H
