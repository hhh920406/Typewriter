#include <QBrush>
#include <QPainter>
#include <QColorDialog>
#include "ColorWidget.h"

ColorWidget::ColorWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setColor(QColor(Qt::white));
}

void ColorWidget::setColor(QColor color)
{
    this->_color = color;
}

void ColorWidget::mouseReleaseEvent(QMouseEvent *)
{
    QColorDialog dialog(this);
    if (QDialog::Accepted == dialog.exec())
    {
        this->_color = dialog.selectedColor();
        this->update();
        emit colorChanged(this->_color);
    }
}

void ColorWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setBrush(QBrush(this->_color));
    int width = this->geometry().width();
    int height = this->geometry().height();
    int left = (width >> 1) - 10;
    int top = (height >> 1) - 10;
    painter.drawRect(left, top, 20, 20);
}
