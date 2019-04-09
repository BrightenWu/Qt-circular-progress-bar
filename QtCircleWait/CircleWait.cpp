#include "circlewait.h"
#include <QPainter>
#include <QTimer>

const int FILLET_RADIUS = 5;

QCircleWaitWidget::QCircleWaitWidget(QWidget *parent) : QWidget(parent),
    m_color(Qt::black),
    m_clockwiseRotate(true),
    m_rotateDelta(36),
    m_rotateAngle(0)
{
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);

    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(update()));
    m_timer->start(100);
}

void QCircleWaitWidget::setColor(QColor color)
{
    if(color != m_color)
    {
        m_color = color;
        update();
    }
}

void QCircleWaitWidget::setClockwiseRotate(bool clockwise)
{
    if(clockwise != m_clockwiseRotate)
    {
        m_clockwiseRotate = clockwise;
        update();
    }
}

void QCircleWaitWidget::setRotateDelta(int delta)
{
    if(delta != m_rotateDelta)
    {
        m_rotateDelta = delta;
        update();
    }
}

void QCircleWaitWidget::setText(const QString & str)
{
	m_strText = str;
}

void QCircleWaitWidget::setFontSize(int nSize)
{
	m_nFontSize = nSize;
}

void QCircleWaitWidget::setFont(const QString & str)
{
	m_strFont = str;
}

void QCircleWaitWidget::paintEvent(QPaintEvent *)
{
	if (width() < 10 || height() < 10)
	{
		return;
	}

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

	//! 绘制圆角矩形背景
	p.setPen(Qt::NoPen);
	p.setBrush(QBrush(QColor(0, 0, 0, 200)));
	QPainterPath roundRectPath;
	roundRectPath.moveTo(width(), FILLET_RADIUS);
	roundRectPath.arcTo(width() - FILLET_RADIUS * 2, 0.0, 10.0, 10.0, 0.0, 90.0);
	roundRectPath.lineTo(FILLET_RADIUS, 0.0);
	roundRectPath.arcTo(0.0, 0.0, 10.0, 10.0, 90.0, 90.0);
	roundRectPath.lineTo(0.0, height() - FILLET_RADIUS);
	roundRectPath.arcTo(0.0, height() - FILLET_RADIUS * 2, 10.0, 10.0, 180.0, 90.0);
	roundRectPath.lineTo(width() - FILLET_RADIUS, height());
	roundRectPath.arcTo(width() - FILLET_RADIUS * 2, height() - FILLET_RADIUS * 2, 10.0, 10.0, 270.0, 90.0);
	roundRectPath.closeSubpath();
	roundRectPath.setFillRule(Qt::WindingFill);
	p.drawPath(roundRectPath);

    int side = qMin(width(), height());

	//! 绘制提示文本
	p.setPen(Qt::white);
	p.setFont(QFont(m_strFont, m_nFontSize));
	if (width() > height())
	{
		p.drawText(QRect(side, 0, width() - side, height()), Qt::AlignCenter, m_strText);
	}
	else
	{
		p.drawText(QRect(0, side, width(), height() - side), Qt::AlignCenter, m_strText);
	}

	p.translate(side/2, side / 2);
    p.scale((side-9)/100.0, (side-9)/100.0);

    p.rotate(m_rotateAngle);
    drawCircleWait(p);
    m_rotateAngle += m_clockwiseRotate?m_rotateDelta:-m_rotateDelta;
    m_rotateAngle %= 360;
}

void QCircleWaitWidget::drawCircleWait(QPainter &p)
{
    //根据100*100的大小进行画,在paintEvent中进行过缩放
    p.save();
    p.setPen(Qt::NoPen);
    QColor color = m_color;
    for(int i = 0; i<=10; ++i)
    {
      color.setAlphaF(1.0*i/10);
      p.setBrush(QBrush(color));
      p.drawEllipse(30,-10, 20, 20);
      p.rotate(36);
    }
    p.restore();
}
