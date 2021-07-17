#include "customtrayicon.h"

#include <QApplication>
#include <QStyle>

CustomTrayIcon::CustomTrayIcon(QWidget* window, QObject *parent)
    : QSystemTrayIcon(parent)
    , m_window(window)
    , trayIconMenu(new QMenu())
    , reloadAction(new QAction())
    , minimizeAction(new QAction())
    , restoreAction(new QAction())
    , quitAction(new QAction())
{
    createActions();
    addActions2Menu();
    setContextMenu(trayIconMenu);

    setIcon(qApp->style()->standardIcon(QStyle::SP_DesktopIcon));
    setToolTip(m_window->windowTitle());

    setTrayIconConnections();
}

void CustomTrayIcon::createActions()
{
    reloadAction->setText(tr("Re&load"));
    connect(reloadAction, &QAction::triggered, this, &CustomTrayIcon::reload);

    minimizeAction->setText(tr("Mi&nimize"));
    connect(minimizeAction, &QAction::triggered, m_window, &QWidget::hide);

    restoreAction->setText(tr("&Restore"));
    connect(restoreAction, &QAction::triggered, m_window, &QWidget::showNormal);

    quitAction->setText(tr("&Quit"));
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void CustomTrayIcon::addActions2Menu()
{
    trayIconMenu->addAction(reloadAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
}

void CustomTrayIcon::setTrayIconConnections()
{
    connect(this, &QSystemTrayIcon::messageClicked, this, [](){
        ;
    });

    connect(this, &QSystemTrayIcon::activated, this, [this](QSystemTrayIcon::ActivationReason reason){
        switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
        case QSystemTrayIcon::MiddleClick:
            restoreAction->trigger();
            break;
        default:
            ;
        }
    });
}
