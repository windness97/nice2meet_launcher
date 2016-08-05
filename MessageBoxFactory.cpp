#include "MessageBoxFactory.h"

MessageBoxFactory::MessageBoxFactory() {
	normal_color = new QColor(30, 30, 120);
	warning_color = new QColor(150, 100, 30);
}

MessageBoxFactory::~MessageBoxFactory() {
	if (normal_color != NULL) delete normal_color;
	if (warning_color != NULL) delete warning_color;
}

MessageBoxFactory* factory;
MessageBoxFactory* MessageBoxFactory::get() {
	if (factory == NULL) {
		factory = new MessageBoxFactory();
	}
	return factory;
}

CMessageBox *MessageBoxFactory::create(QWidget *parent, QString content, QRect showRectInParent, BOXMODE mode, int showTime, int radius) {
	QColor backgroundColor(mode == normal ? QColor(*normal_color) : QColor(*warning_color));
	CMessageBox *box = new CMessageBox(parent, content, showRectInParent, backgroundColor, showTime, radius);
	return box;
}



CMessageBox::CMessageBox(QWidget *parent, QString content, QRect showRectInParent, QColor backgroundColor, int showTime, int radius)
	: QLabel(parent), parent(parent), backgroundColor(backgroundColor), showTime(showTime), radius(radius)
{
	setText(content);
	this->setWordWrap(true);
	this->setAttribute(Qt::WA_X11DoNotAcceptFocus, true);
	this->setAttribute(Qt::WA_TransparentForMouseEvents, true);

	QFont font = this->font();
	font.setPointSize(10);
	this->setFont(font);

	QPalette palette = this->palette();
	palette.setColor(QPalette::WindowText, QColor(255, 255, 255));
	this->setPalette(palette);

	this->setContentsMargins(QMargins(10, 0, 10, 0));
	this->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	timer = new QTimer(this);
	timer->setSingleShot(true);
	connect(timer, SIGNAL(timeout()), this, SLOT(handleTimeOut()));

	setGeometry(showRectInParent);
}

CMessageBox::~CMessageBox() {
	if (timer != NULL) delete timer;
}

void CMessageBox::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(backgroundColor));

	int r = this->radius;
	int x1 = this->rect().left();
	int y1 = this->rect().top();
	int x2 = this->rect().right();
	int y2 = this->rect().bottom();

	QPainterPath path;

	path.moveTo(x1 + r, y1);
	path.arcTo(x1, y1, r * 2, r * 2, 90.0f, 90.0f);
	path.arcTo(x1, y2 - r * 2 + 1, r * 2, r * 2, 180.0f, 90.0f);
	path.arcTo(x2 - r * 2 + 1, y2 - r * 2 + 1, r * 2, r * 2, 270.0f, 90.0f);
	path.arcTo(x2 - r * 2 + 1, y1, r * 2, r * 2, 0.0f, 90.0f);

	painter.fillPath(path, painter.brush());

	QLabel::paintEvent(event);
}

void CMessageBox::start() {
	timer->start(showTime);
	show();
}

void CMessageBox::handleTimeOut() {
	timer->stop();
	close();
	this->destroy(true);
	delete this;
}