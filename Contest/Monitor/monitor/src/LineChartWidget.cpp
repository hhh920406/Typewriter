#include <QDateTime>
#include <QPainter>
#include "ClientManager.h"
#include "LineChartWidget.h"

LineChartWidget::LineChartWidget(QWidget *parent) :
    QWidget(parent)
{
    this->_clientManager = 0L;
    this->setGeometry(this->geometry().x(), this->geometry().y(), 200, 400);
    this->_useMagic = false;
    this->_magic = -1;
}

void LineChartWidget::setClientManager(ClientManager *ClientManager)
{
    this->_clientManager = ClientManager;
}

void LineChartWidget::setUseMagic(const bool value)
{
    this->_useMagic = value;
}

void LineChartWidget::setMagic(const qint32 value)
{
    this->_magic = value;
}

void LineChartWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    qint32 width = this->geometry().width();
    qint32 height = this->geometry().height();
    painter.drawRect(0, 0, width, height);
    qint32 margin = 20;
    qint32 chartWidth = width - (margin << 2);
    qint32 chartHeight = (height - (margin << 2)) >> 1;
    qint32 hourChartShiftX = margin * 3;
    qint32 hourChartShiftY = margin;
    qint32 dayChartShiftX = margin * 3;
    qint32 dayChartShiftY = margin * 3 + chartHeight;
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::darkGray);
    for (qint32 i = 1; i < 12; ++i)
    {
        painter.drawLine(hourChartShiftX + i / 12.0 * chartWidth,
                         hourChartShiftY,
                         hourChartShiftX + i / 12.0 * chartWidth,
                         hourChartShiftY + chartHeight);
        painter.drawLine(dayChartShiftX + i / 12.0 * chartWidth,
                         dayChartShiftY,
                         dayChartShiftX + i / 12.0 * chartWidth,
                         dayChartShiftY + chartHeight);
    }
    for (qint32 i = 1; i < 5; ++i)
    {
        painter.drawLine(hourChartShiftX,
                         hourChartShiftY + i / 5.0 * chartHeight,
                         hourChartShiftX + chartWidth,
                         hourChartShiftY + i / 5.0 * chartHeight);
        painter.drawLine(dayChartShiftX,
                         dayChartShiftY + i / 5.0 * chartHeight,
                         dayChartShiftX + chartWidth,
                         dayChartShiftY + i / 5.0 * chartHeight);
    }
    painter.setPen(Qt::black);
    for (qint32 i = 0; i <= 12; ++i)
    {
        painter.drawText(hourChartShiftX + i / 12.0 * chartWidth - 10,
                         hourChartShiftY + chartHeight + 2,
                         100,
                         100,
                         Qt::AlignLeft | Qt::AlignTop,
                         QString("%1").arg(i * 25));
        painter.drawText(dayChartShiftX + i / 12.0 * chartWidth - 10,
                         dayChartShiftY + chartHeight + 2,
                         100,
                         100,
                         Qt::AlignLeft | Qt::AlignTop,
                         QString("%1").arg(i * 5));
    }
    if (0L != this->_clientManager)
    {
        qint32 maxRtt = 100;
        QVector<ClientInfo> *clients = this->_clientManager->clients();
        for (qint32 i = 0; i < clients->size(); ++i)
        {
            if (this->_useMagic && this->_magic != clients->at(i).magic())
            {
                continue;
            }
            if (clients->at(i).show())
            {
                qint32 threshold = clients->at(i).alertThreshold();
                threshold = threshold / 8 * 10;
                if (threshold > maxRtt)
                {
                    maxRtt = threshold;
                }
            }
        }
        for (qint32 i = 1; i <= 5; ++i)
        {
            painter.drawText(hourChartShiftX - 100,
                             hourChartShiftY + (5 - i) / 5.0 * chartHeight - 100,
                             95,
                             200,
                             Qt::AlignRight | Qt::AlignVCenter,
                             QString("%1").arg(maxRtt * i / 5));
            painter.drawText(dayChartShiftX - 100,
                             dayChartShiftY + (5 - i) / 5.0 * chartHeight - 100,
                             95,
                             200,
                             Qt::AlignRight | Qt::AlignVCenter,
                             QString("%1").arg(maxRtt * i / 5));
        }
        for (qint32 i = 0; i < clients->size(); ++i)
        {
            ClientInfo *client = &(*clients)[i];
            if (this->_useMagic && this->_magic != client->magic())
            {
                continue;
            }
            if (client->show())
            {
                QPen pen(clients->at(i).color());
                pen.setWidth(2);
                painter.setPen(pen);
                qint32 threshold = client->alertThreshold();
                painter.drawLine(hourChartShiftX,
                                 hourChartShiftY + 1.0 * (maxRtt - threshold) / maxRtt * chartHeight,
                                 hourChartShiftX + chartWidth,
                                 hourChartShiftY + 1.0 * (maxRtt - threshold) / maxRtt * chartHeight);
                painter.drawLine(dayChartShiftX,
                                 dayChartShiftY + 1.0 * (maxRtt - threshold) / maxRtt * chartHeight,
                                 dayChartShiftX + chartWidth,
                                 dayChartShiftY + 1.0 * (maxRtt - threshold) / maxRtt * chartHeight);
                if (client->times()->size() > 0)
                {
                    qint64 lastTime = client->times()->last() % 3600000;
                    painter.drawLine(dayChartShiftX + lastTime / 3600000.0 * chartWidth,
                                     dayChartShiftY,
                                     dayChartShiftX + lastTime / 3600000.0 * chartWidth,
                                     dayChartShiftY + chartHeight);
                    lastTime %= 300000;
                    painter.drawLine(hourChartShiftX + lastTime / 300000.0 * chartWidth,
                                     hourChartShiftY,
                                     hourChartShiftX + lastTime / 300000.0 * chartWidth,
                                     hourChartShiftY + chartHeight);
                    lastTime = client->times()->last();
                    for (qint32 j = 1; j < client->times()->size(); ++j)
                    {
                        qint64 time1 = client->times()->at(j - 1);
                        qint64 time2 = client->times()->at(j);
                        qint32 rtt1 = client->rtts()->at(j - 1);
                        qint32 rtt2 = client->rtts()->at(j);
                        if (rtt1 > maxRtt)
                        {
                            rtt1 = maxRtt;
                        }
                        if (rtt2 > maxRtt)
                        {
                            rtt2 = maxRtt;
                        }
                        time1 %= 3600000;
                        time2 %= 3600000;
                        if (time2 > time1 && lastTime - client->times()->at(j - 1) < 3600000)
                        {
                            painter.drawLine(dayChartShiftX + time1 / 3600000.0 * chartWidth,
                                             dayChartShiftY + 1.0 * (maxRtt - rtt1) / maxRtt * chartHeight,
                                             dayChartShiftX + time2 / 3600000.0 * chartWidth,
                                             dayChartShiftY + 1.0 * (maxRtt - rtt2) / maxRtt * chartHeight);
                        }
                        time1 %= 300000;
                        time2 %= 300000;
                        if (time2 > time1 && lastTime - client->times()->at(j - 1) < 300000)
                        {
                            painter.drawLine(hourChartShiftX + time1 / 300000.0 * chartWidth,
                                             hourChartShiftY + 1.0 * (maxRtt - rtt1) / maxRtt * chartHeight,
                                             hourChartShiftX + time2 / 300000.0 * chartWidth,
                                             hourChartShiftY + 1.0 * (maxRtt - rtt2) / maxRtt * chartHeight);
                        }
                    }
                }
            }
        }
    }
    painter.setPen(Qt::black);
    painter.drawRect(hourChartShiftX, hourChartShiftY, chartWidth, chartHeight);
    painter.drawRect(dayChartShiftX, dayChartShiftY, chartWidth, chartHeight);
}
