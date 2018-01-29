#include "pf_graphicview.h"

#include <QPainter>
#include <QtMath>

PF_GraphicView::PF_GraphicView(QWidget *parent) : QWidget(parent)
{

}

void PF_GraphicView::paintEvent(QPaintEvent *){
    //在使用QPainter绘图之前，必须先制定绘图设备，用this指定在本窗口绘制
    QPainter painter(this);

    drawLayer1(&painter);

    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);
    // 设置画笔颜色、宽度
    painter.setPen(QPen(QColor(0, 160, 230), 2));
    // 设置画刷颜色
    painter.setBrush(QColor(255, 160, 90));
    painter.drawRect(50, 50, 160, 100);

    //绘制多边形
    int count = 6;
    int radius = 200;
    //绘图设备的坐标原点在左上角，水平向右增长，垂直向下增长，
    //平移坐标原点，让原点在绘图设备的中心
    painter.translate(width()/2.,height()/2.);

    //开始绘制多边形，并为每个区块上色
    for(int i = 0; i < count; ++i){
        float degree = 180. / count;
        //先将坐标 旋转
        painter.rotate(2 * degree);

        float radian = qDegreesToRadians(degree);
        float wid = radius * qSin(radian);
        float hei = radius * qCos(radian);

        //绘制三角形区块
        QPainterPath path;
        path.lineTo(-wid,-hei);
        path.lineTo(wid,-hei);
        path.lineTo(0,0);
        painter.drawPath(path);

        QColor color(qrand()%255,qrand()%255,qrand()%255,150);
        painter.fillPath(path,color);
    }
    // 设置画笔颜色
    QPen pen;
    pen.setColor(QColor(0, 0, 0));
    pen.setWidth(3);
    painter.setPen(pen);

    // 设置字体：微软雅黑、点大小50、斜体
    QFont font;
    font.setFamily("Times New Roman");
    font.setPointSize(15);
    font.setItalic(true);
    painter.setFont(font);

    //translate 是按照当前的原点进行的
    painter.translate(-0.4*width(),0.4*height());
    // 绘制x,y轴
    painter.drawLine(QPointF(0, 0), QPointF(0, -40));//y
    // y
    painter.drawText(QPointF(0-20, -80), QString("y"));
    painter.drawLine(QPointF(0, 0), QPointF(40, 0));//x
    //x
    painter.drawText(QPointF(80, 0+20), QString("x"));

    QPainterPath path;
    painter.setPen(Qt::NoPen);
    int ww = 6;
    int hh = 80;
    path.moveTo(-ww,-40);
    path.lineTo(ww,-40);
    path.lineTo(0,-hh);
    path.lineTo(-ww,-40);
    painter.drawPath(path);

    QColor color(0,0,0);
    painter.fillPath(path,color);

    path.moveTo(40, ww);
    path.lineTo(40, -ww);
    path.lineTo(hh, 0);
    path.lineTo(40, ww);
    painter.drawPath(path);

    painter.fillPath(path,color);
}

void PF_GraphicView::drawLayer1(QPainter * painter){

    for(int i = 0; i < this->width();i+=10){
        for(int j = 0; j < this->height();j+=10){
            painter->drawPoint(i,j);
        }
    }
}