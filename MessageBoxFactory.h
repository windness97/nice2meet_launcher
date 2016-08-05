#pragma once
#ifndef MESSAGEBOXFACTORY_H
#define MESSAGEBOXFACTORY_H

#include <QtWidgets>

class CMessageBox;

class MessageBoxFactory
{
public:
	enum BOXMODE {
		normal = 0,
		warning = 1
	};

public:
	static MessageBoxFactory* get();
	CMessageBox* create(QWidget *parent, QString content, QRect showRectInParent, BOXMODE mode = normal, int showTime = 5000, int radius = 10);

protected:
	MessageBoxFactory();
	~MessageBoxFactory();

private:
	QColor *normal_color;
	QColor *warning_color;
};



class CMessageBox : public QLabel
{
	Q_OBJECT
public:
	CMessageBox(QWidget *parent, QString content, QRect showRectInParent, QColor backgroundColor, int showTime, int radius);
	~CMessageBox();
	void start();

private slots:
	void handleTimeOut();

protected:
	void paintEvent(QPaintEvent *);

private:
	int radius;
	QColor backgroundColor;
	QWidget *parent;
	int showTime;
	QTimer *timer;
};

#endif