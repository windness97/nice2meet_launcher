#include "BaseButton.h"


BaseButton::BaseButton(QWidget *parent, int x, int y, int w, int h)
	: QPushButton(parent), parent(parent), _x(x), _y(y), _w(w), _h(h)
{
	setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint);
	setMouseTracking(true);

	//setFixedWidth(w);
	//setFixedHeight(h);
	setFixedSize(w, h);
	//setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

BaseButton::~BaseButton()
{
}

void BaseButton::paintEvent(QPaintEvent *event) {
	int w = this->width();
	int h = this->height();

	int x = this->x();
	int y = this->y();

	QPainter painter(this);
	painter.setPen(QPen(QColor(255, 255, 255), 5, Qt::SolidLine, Qt::RoundCap));
	painter.setBrush(QColor(200, 200, 200));
	
	painter.drawRect(x, y, w, h);

	QPainterPath path;
	path.moveTo(x + w * 0.2f, y + h * 0.2f);
	path.lineTo(x + w * 0.8f, y + h * 0.8f);
	path.moveTo(x + w * 0.8f, y + h * 0.2f);
	path.lineTo(x + w * 0.2f, y + h * 0.8f);

	painter.drawPath(path);
	painter.fillPath(path, painter.brush());

	QPushButton::paintEvent(event);
}

void BaseButton::setLocation() {
	//this->setGeometry(x(), y(), width(), height());
	this->setGeometry(parent->width() - 60, 20, width(), height());
}