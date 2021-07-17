#ifndef CUSTOMTRAYICON_H
#define CUSTOMTRAYICON_H

#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>

class CustomTrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    CustomTrayIcon(QWidget* window, QObject *parent = nullptr);

signals:
    void reload();

private:
    void createActions();
    void addActions2Menu();
    void setTrayIconConnections();

private:
    QWidget* m_window;
    QMenu* trayIconMenu;
    QAction* reloadAction;
    QAction* minimizeAction;
    QAction* restoreAction;
    QAction* quitAction;
};

#endif // CUSTOMTRAYICON_H
