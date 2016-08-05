#include "roundradiuswindow.h"

RoundRadiusWindow::RoundRadiusWindow(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags), _mouse_clicked(false), radius(20)
{
	//this->setWindowFlags(Qt::FramelessWindowHint);
	setWindowModality(Qt::WindowModality::NonModal);
	setAttribute(Qt::WA_TranslucentBackground);
	setMouseTracking(true);
	this->setFixedSize(346, 350);

	_name_edit = new RoundRadiusEditText(this, tr("user name"));
	_room_edit = new RoundRadiusEditText(this, tr("room number"));
	_password_edit = new RoundRadiusEditText(this, tr("room password"));
	//closeButton = new BaseButton(this, width() - 60, 20, 40, 40);

	_group_mode = new QButtonGroup(this);
	_mode_mcu = new QRadioButton(QString("MCU"), this);
	_mode_p2p = new QRadioButton(QString("P2P"), this);
	_group_mode->addButton(_mode_mcu, 0);
	_group_mode->addButton(_mode_p2p, 1);
	_mode_mcu->setStyleSheet("color: rgb(150, 150, 150);");
	_mode_p2p->setStyleSheet("color: rgb(150, 150, 150);");
	_mode_mcu->setChecked(true);

	QToolButton *_closeButton = new QToolButton(this);
	QPixmap pic = QPixmap("Resources/images/close_btn.png");
	_closeButton->setFixedSize(pic.width(), pic.height());
	_closeButton->setIconSize(QSize(pic.width(), pic.height()));
	_closeButton->setIcon(pic);
	//_closeButton->setToolTip(QString("quit"));
	_closeButton->setGeometry(width() - 50, 10, 40, 40);
	_closeButton->setStyleSheet("background-color:transparent;");
	connect(_closeButton, SIGNAL(clicked()), qApp, SLOT(quit()));

	_button_start = new QPushButton(this);
	_button_start->setStyleSheet(tr("border-radius: 8px; padding: 4px; background-color: rgb(75, 75, 75); color: rgb(255, 255, 255);"));
	_button_start->setText("start");
	QFont font = _button_start->font();
	font.setPointSize(15);
	font.setWeight(75);
	_button_start->setFont(font);
	_button_start->setGeometry(width() * 0.2, 230, width() * 0.6, 32);
	connect(_button_start, SIGNAL(clicked()), this, SLOT(checkStart()));

	_name_edit->setLocation(50);
	_room_edit->setLocation(100);
	_password_edit->setLocation(150);

	_mode_mcu->setGeometry(85, 190, 75, 42);
	_mode_p2p->setGeometry(220, 190, 75, 42);
}

RoundRadiusWindow::~RoundRadiusWindow()
{

}

////// slots //////

void RoundRadiusWindow::checkStart() {
	if (_name_edit->isEmpty()) {
		QString message = "the name edit is empty.";
		//CMessageBox *box = new CMessageBox(this, message, QRect(width() * 0.1, 290, width() * 0.8, 30));
		//box->start();
		createMessageBox(message, true);
	}
	else if (_room_edit->isEmpty()) {
		QString message = "the room edit is empty.";
		//CMessageBox *box = new CMessageBox(this, message, QRect(width() * 0.1, 290, width() * 0.8, 30));
		//box->start();
		createMessageBox(message, true);
	}
	else {
		start();
	}
}

//////

void RoundRadiusWindow::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(QPen(QColor(100, 100, 100, 0), 1, Qt::SolidLine, Qt::RoundCap));
	painter.setBrush(QBrush(QColor(25, 25, 25, 200)));

	painter.drawRoundedRect(this->rect(), radius, radius);
}

void RoundRadiusWindow::resizeEvent(QResizeEvent *event) {
	//editText->setGeometry(100, 100, editText->width(), editText->height());

	//closeButton->setLocation();
	//editText2->setText(QString::number(closeButton->x(), 10) + tr(", ") + QString::number(closeButton->y(), 10) + tr(", ") + QString::number(closeButton->width(), 10) + tr(", ") + QString::number(closeButton->height(), 10));

	QWidget::resizeEvent(event);
}

void RoundRadiusWindow::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		_mouse_clicked = true;
		_mouse_clicked_type = checkMouse(event->x(), event->y());
		_rect_clicked = frameGeometry();
		_point_clicked = event->globalPos();
	}
}

void RoundRadiusWindow::mouseReleaseEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		_mouse_clicked = false;
		_mouse_clicked_type = MouseOut;
	}
}

void RoundRadiusWindow::mouseMoveEvent(QMouseEvent *event) {
	if (_mouse_clicked == false) {
		MOUSETYPE type = checkMouse(event->x(), event->y());
		if (type == MouseTop || type == MouseBottom) setCursor(Qt::SizeVerCursor);
		else if (type == MouseLeft || type == MouseRight) setCursor(Qt::SizeHorCursor);
		else if (type == MouseTopLeft || type == MouseBottomRight) setCursor(Qt::SizeFDiagCursor);
		else if (type == MouseTopRight || type == MouseBottomLeft) setCursor(Qt::SizeBDiagCursor);
		else if (type == MouseIn || MouseOut) setCursor(Qt::ArrowCursor);
	}
	else if (_mouse_clicked == true) {
		if (_mouse_clicked_type == MouseIn) {
			move(_rect_clicked.topLeft() + event->globalPos() - _point_clicked);
		}
	}
}

RoundRadiusWindow::MOUSETYPE RoundRadiusWindow::checkMouse(int x, int y) {

	int width = rect().width();
	int height = rect().height();
	int radius = this->radius;

	//if (x < 12 && y < 12)
	if (y < -x + radius)
	{
		return MouseTopLeft;
	}
	//if (x < 12 && y > height - 12)
	if (y > x + height - radius)
	{
		return MouseBottomLeft;
	}
	//if (x > width - 12 && y < 12)
	if (y < x - (width - radius))
	{
		return MouseTopRight;
	}
	//if (x > width - 12 && y > height - 12)
	if (y > -x + width + height - radius)
	{
		return MouseBottomRight;
	}

	if (x < 6)
	{
		return MouseLeft;
	}
	if (x > width - 6)
	{
		return MouseRight;
	}
	if (y < 6)
	{
		return MouseTop;
	}
	if (y > height - 6)
	{
		return MouseBottom;
	}

	return MouseIn;
}

void RoundRadiusWindow::start() {
	QString str_user = _name_edit->text();
	QString str_room = _room_edit->text();
	QString str_mode = mode() == mcu ? "mcu" : "p2p";
	QString message = "user: " + str_user + ", room: " + str_room + ", start mode: " + str_mode;
	//CMessageBox *box = new CMessageBox(this, message, QRect(width() * 0.1, 290, width() * 0.8, 30));
	//box->start();
	createMessageBox(message, false);
}

RoundRadiusWindow::MODE RoundRadiusWindow::mode() {
	return _mode_mcu->isChecked() ? mcu : p2p;
}

void RoundRadiusWindow::createMessageBox(QString message, bool warning) {
	int h0 = 300;
	int times = 15;
	
	int x = width() / (times * 2);
	int y = h0;
	int w = width() * (times - 1) / times;
	int z = height() - y - x;
	QRect rect(x, y, w, z);
	MessageBoxFactory::BOXMODE mode = warning == true ? MessageBoxFactory::warning : MessageBoxFactory::normal;
	MessageBoxFactory::get()->create(this, message, rect, mode)->start();
}