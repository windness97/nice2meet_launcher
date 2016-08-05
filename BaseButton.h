#pragma once
#ifndef BASEBUTTON_H
#define BASEBUTTON_H

#include <QtWidgets>

class BaseButton : public QPushButton
{
	Q_OBJECT
public:
	BaseButton(QWidget *parent = 0, int x = 0, int y = 0, int w = 50, int h = 50);
	~BaseButton();
	void setLocation();

	int getX() {
		return x();
	}

	int getY() {
		return y();
	}

	int getW() {
		return width();
	}

	int getH() {
		return height();
	}

protected:
	void paintEvent(QPaintEvent *);

signals:

private slots:

private:
	QWidget *parent;
	int _x;
	int _y;
	int _w;
	int _h;

private:


};

#endif