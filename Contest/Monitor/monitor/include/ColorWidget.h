#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>

class ColorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorWidget(QWidget *parent = 0);
    void setColor(QColor color);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

private:
    QColor _color;
    
signals:
    void colorChanged(QColor color);
};

#endif // COLORWIDGET_H
