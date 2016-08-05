#include "RoundRadiusEditText.h"
#include <iostream>

using namespace std;

RoundRadiusEditText::RoundRadiusEditText(QWidget *parent, QString hint)
	: QLineEdit(parent), parent(parent), hint(hint), empty(true), textColor(QColor(255, 255, 255)), hintColor(QColor(150, 150, 150))
{
	this->setStyleSheet("border:0px;padding:4px 6px;background-color:rbg(0,0,0,0);");

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setMaxLength(20);

	QFont font = this->font();
	font.setPointSize(12);
	this->setFont(font);

	QPalette palette = this->palette();
	palette.setColor(QPalette::ColorRole::Text, textColor);
	this->setPalette(palette);

	this->clearFocus();
	p_focusOutEvent();
}

RoundRadiusEditText::~RoundRadiusEditText()
{
}

void RoundRadiusEditText::paintEvent(QPaintEvent *event) {
	//QPainter painter(this);
	//painter.setPen(QPen(QColor(255, 0, 0), 3));
	//painter.drawRoundRect(this->rect());

	QPainter painter(this);
	painter.setBrush(QBrush(QColor(50, 50, 50)));
	
	int r = 10;
	int x1 = this->rect().left();
	int y1 = this->rect().top();
	int x2 = this->rect().right();
	int y2 = this->rect().bottom();

	QPainterPath path;
	path.moveTo(x1 + r, y1);
	path.arcTo(x1, y1, r * 2, r * 2, 90.0f, 90.0f);
	path.arcTo(x1, y2 - r * 2 + 1, r * 2, r * 2, 180.0f, 90.0f);
	path.arcTo(x2 - r * 2 + 1, y2 - r * 2, r * 2 + 1, r * 2, 270.0f, 90.0f);
	path.arcTo(x2 - r * 2 + 1, y1, r * 2, r * 2, 0.0f, 90.0f);

	painter.fillPath(path, painter.brush());

	cout << "left: " << rect().left() << endl;
	cout << "top: " << rect().top() << endl;
	cout << "right: " << rect().right() << endl;
	cout << "bottom: " << rect().bottom() << endl;

	QLineEdit::paintEvent(event);
}

void RoundRadiusEditText::setLocation(int h) {
	this->setFixedWidth(parent->width() * 0.8);
	this->setGeometry(parent->width() * 0.1, h, this->width(), this->height());
}

////// slots //////


////// events //////

void RoundRadiusEditText::focusInEvent(QFocusEvent *event) {
	if (empty == true) {
		this->setText(tr(""));

		QPalette p = this->palette();
		p.setColor(QPalette::ColorRole::Text, textColor);
		this->setPalette(p);

		QFont f = this->font();
		f.setItalic(false);
		this->setFont(f);

		empty = false;
	}
	QLineEdit::focusInEvent(event);
}

void RoundRadiusEditText::focusOutEvent(QFocusEvent *event) {
	p_focusOutEvent();

	//if (event != NULL) 
	QLineEdit::focusOutEvent(event);
}

void RoundRadiusEditText::p_focusOutEvent() {
	if (this->text() == tr("") || this->text().length() == 0) {
		this->setText(hint);

		QPalette p = this->palette();
		p.setColor(QPalette::ColorRole::Text, hintColor);
		this->setPalette(p);

		QFont f = this->font();
		f.setItalic(true);
		this->setFont(f);

		empty = true;
	}
}