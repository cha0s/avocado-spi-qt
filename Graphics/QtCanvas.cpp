#include "core/avocado-global.h"

#include "QtCanvas.h"

namespace avo {

AbstractFactory<QtCanvas> *QtCanvas::factory = new AbstractFactory<QtCanvas>;

static QPainter::CompositionMode mapCompositionMode(GraphicsService::BlendMode blendMode) {

	switch (blendMode) {
	default:
	case GraphicsService::BlendMode_Blend:
		return QPainter::CompositionMode_SourceOver;

	case GraphicsService::BlendMode_Replace:
		return QPainter::CompositionMode_Source;
	}
}

QtCanvas::QtCanvas()
	: Canvas()
	, _qImage(NULL)
{
}

QtCanvas::QtCanvas(int width, int height)
	: Canvas()
	, _qImage(new QImage(width, height, QImage::Format_ARGB32))
{
}

QtCanvas::QtCanvas(const boost::filesystem::path &uri)
	: Canvas()
{
	_qImage = new QImage(QString::fromStdString(uri.string()));

	if (!_qImage || _qImage->isNull()) throw std::runtime_error(
		"Qt couldn't load the image."
	);

	setUri(uri);
}

QtCanvas::~QtCanvas() {
	if (_qImage) delete _qImage;
}

void QtCanvas::drawCircle(int x, int y, int radius, int r, int g, int b, double a, GraphicsService::BlendMode blendMode) {
	if (NULL == _qImage) return;

	QPainter painter(_qImage);

	// Translate the rendering mode to Qt's composition mode.
	painter.setCompositionMode(mapCompositionMode(blendMode));

	painter.setPen(QPen(QColor(r, g, b, a * 255.0)));
	painter.drawEllipse(QRect(x, y, radius * 2, radius * 2));
}

void QtCanvas::drawFilledBox(int x, int y, int w, int h, int r, int g, int b, double a, GraphicsService::BlendMode blendMode) {
	if (NULL == _qImage) return;

	QPainter painter(_qImage);

	// Translate the rendering mode to Qt's composition mode.
	painter.setCompositionMode(mapCompositionMode(blendMode));

	painter.fillRect(QRect(x, y, w, h), QColor(r, g, b, a * 255.0));
}

void QtCanvas::drawLine(int x1, int y1, int x2, int y2, int r, int g, int b, double a, GraphicsService::BlendMode blendMode) {
	if (NULL == _qImage) return;

	QPainter painter(_qImage);

	// Translate the rendering mode to Qt's composition mode.
	painter.setCompositionMode(mapCompositionMode(blendMode));

	painter.setPen(QPen(QColor(r, g, b, a * 255.0)));
	painter.drawLine(QLine(x1, y1, x2, y2));
}

void QtCanvas::drawLineBox(int x, int y, int w, int h, int r, int g, int b, double a, GraphicsService::BlendMode blendMode) {
	if (NULL == _qImage) return;

	QPainter painter(_qImage);

	// Translate the rendering mode to Qt's composition mode.
	painter.setCompositionMode(mapCompositionMode(blendMode));

	painter.setPen(QPen(QColor(r, g, b, a * 255.0)));
	painter.drawRect(QRect(x, y, w, h));
}

void QtCanvas::fill(int r, int g, int b, double a) {
	if (NULL == _qImage) return;

	drawFilledBox(
		0, 0, width(), height(),
		r, g, b, a * 255.0,
		GraphicsService::BlendMode_Blend
	);
}

int QtCanvas::height() const {
	if (NULL == _qImage) return 0;

	return _qImage->height();
}

unsigned int QtCanvas::pixelAt(int x, int y) const {
	if (NULL == _qImage) return 0;

	return reinterpret_cast<unsigned int *>(_qImage->scanLine(y))[x];
}

void QtCanvas::saveToFile(const boost::filesystem::path &filename) {
	_qImage->save(QString::fromStdString(filename.string()));
}

void QtCanvas::setPixelAt(int x, int y, unsigned int pixel) {
	if (NULL == _qImage) return;

	reinterpret_cast<unsigned int *>(_qImage->scanLine(y))[x] = pixel;
}

int QtCanvas::width() const {
	if (NULL == _qImage) return 0;

	return _qImage->width();
}

QImage *QtCanvas::qImage() const {
	return _qImage;
}

}

