#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QCloseEvent>

#include "customtrayicon.h"
#include "windowinfohelper.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , trayIcon(new CustomTrayIcon(this, this))
{
    ui->setupUi(this);
    connect(ui->btnLoad, &QAbstractButton::clicked, this, &MainWindow::refreshWindowList);
    connect(trayIcon, &CustomTrayIcon::reload, this, &MainWindow::refreshWindowList);
    trayIcon->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(isResidentMode() == false) {
        qApp->quit();
        return;
    }

    if (trayIcon->isVisible() == false) {
        QMainWindow::closeEvent(event);
        return;
    }

    QMessageBox::information(this, tr("Systray"),
                             tr("The program will keep running in the "
                                "system tray. To terminate the program, "
                                "choose <b>Quit</b> in the context menu "
                                "of the system tray entry."));
    hide();
    event->ignore();
}

bool MainWindow::isResidentMode() const
{
    return ui->chkboxResident->isChecked();
}

void MainWindow::refreshWindowList()
{
    ui->listWidget->clear();
    const WindowInfoList windowInfoList = WindowInfoHelper::getWindowList();
    for(const auto& windowInfo : windowInfoList) {
        QListWidgetItem* item = new QListWidgetItem();
        item->setText(windowInfo.first);
        item->setToolTip(windowInfo.second);
        ui->listWidget->addItem(item);
    }
    ui->listWidget->sortItems();
}
