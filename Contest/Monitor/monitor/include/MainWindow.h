#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMap>
#include <QMainWindow>
#include <QMdiSubWindow>
#include "ClientManager.h"
#include "TcpServer.h"
#include "UdpServer.h"
#include "LineChartWidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *);
    
private:
    Ui::MainWindow *ui;
    ClientManager _clientManager;
    TcpServer *_tcpServer;
    UdpServer *_udpServer;
    LineChartWidget *_summarySubWindow;
    QMap<qint32, QMdiSubWindow*> _subWindows;

    void initToolBar();
    void updateTableRow(const qint32 row, ClientInfo *client);
    void updateTableMagic(const qint32 magic);
    void updateTableWidget();
    void updateSubWindowMagic(const qint32 magic);
    void removeSubWindowMagic(const qint32 magic);

private slots:
    void newClient(qint32 magic);
    void updateClient(qint32 magic);
    void closeClient(qint32 magic);
    void deleteClient();
    void showChanged(bool value);
    void alertChanged(bool value);
    void colorChanged(QColor value);
    void editAlert(int value);
    void on_actionExport_triggered();
    void on_actionExit_E_triggered();
    void on_actionStart_S_triggered();
    void on_actionPause_P_triggered();
    void on_actionStop_E_triggered();
    void on_actionOption_O_triggered();
    void on_actionCascade_triggered();
    void on_actionTile_triggered();
    void on_actionAbout_triggered();
    void on_actionHelp_triggered();
};

#endif // MAINWINDOW_H
