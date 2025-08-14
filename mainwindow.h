#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setCentralWindow(int width, int height);
    void saveData(const QString &path);
    void loadData(const QString &path);
private:
    QWidget *widget;
    QGridLayout *grid;
};
#endif // MAINWINDOW_H
