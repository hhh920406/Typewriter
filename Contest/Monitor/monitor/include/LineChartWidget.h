#ifndef LINECHARTWIDGET_H
#define LINECHARTWIDGET_H
/**
 * The line chart of RTT.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QWidget>

class ClientManager;

class LineChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LineChartWidget(QWidget *parent = 0);
    void setClientManager(ClientManager *ClientManager);
    void paintEvent(QPaintEvent *);
    void setUseMagic(const bool value);
    void setMagic(const qint32 value);

private:
    ClientManager *_clientManager;
    bool _useMagic;
    qint32 _magic;
};

#endif // LINECHARTWIDGET_H
