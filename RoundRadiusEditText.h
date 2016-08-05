#pragma once
#ifndef ROUNDRADIUSEDITTEXT_H
#define ROUNDRADIUSEDITTEXT_H

#include <QtWidgets>

class RoundRadiusEditText: public QLineEdit
{
	Q_OBJECT
public:
	RoundRadiusEditText(QWidget *parent = 0, QString hint = tr("input something here."));
	~RoundRadiusEditText();
	void setLocation(int h);

	bool isEmpty() { return empty; }

signals:

private slots:

////// events and methods//////
private:
	void paintEvent(QPaintEvent *);
	void focusInEvent(QFocusEvent *);
	void focusOutEvent(QFocusEvent *);

	void p_focusOutEvent();

	//void resizeEvent(QResizeEvent *);

private:
	QWidget *parent;
	QString hint;
	QColor textColor;
	QColor hintColor;

	bool empty;
};

#endif