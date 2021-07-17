#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CustomTrayIcon;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void refreshWindowList();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    bool isResidentMode() const;
private:
    Ui::MainWindow *ui;
    CustomTrayIcon *trayIcon;
};
#endif // MAINWINDOW_H
