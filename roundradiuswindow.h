#ifndef ROUNDRADIUSTEST_H
#define ROUNDRADIUSTEST_H

#include <QtWidgets>
#include "RoundRadiusEditText.h"
#include "MessageBoxFactory.h"
#include "BaseButton.h"

class RoundRadiusWindow : public QMainWindow
{
	Q_OBJECT
public:
	RoundRadiusWindow(QWidget *parent = 0, Qt::WindowFlags flags = Qt::FramelessWindowHint);
	~RoundRadiusWindow();

private slots:
	void checkStart();

protected:
	void paintEvent(QPaintEvent *);
	void resizeEvent(QResizeEvent *);

	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
private:
	RoundRadiusEditText *_name_edit;
	RoundRadiusEditText *_room_edit;
	RoundRadiusEditText *_password_edit;

	QButtonGroup *_group_mode;
	QRadioButton *_mode_mcu;
	QRadioButton *_mode_p2p;

	QPushButton *_button_start;
	//BaseButton *closeButton;

	int radius;
	
	enum MOUSETYPE {
		MouseIn,
		MouseOut,
		MouseLeft,
		MouseTop,
		MouseRight,
		MouseBottom,
		MouseTopLeft,
		MouseTopRight,
		MouseBottomLeft,
		MouseBottomRight,
	};
	bool _mouse_clicked;
	MOUSETYPE _mouse_clicked_type;
	QRect _rect_clicked;
	QPoint _point_clicked;

	enum MODE {
		mcu,
		p2p
	};

	MOUSETYPE checkMouse(int, int);
	void start();
	MODE mode();

	void createMessageBox(QString str, bool warning = false);
};

#endif // ROUNDRADIUSTEST_H
