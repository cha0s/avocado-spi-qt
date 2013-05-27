#include "core/avocado-global.h"

#include "QtCanvas.h"

namespace avo {

AbstractFactory<QtCanvas> *QtCanvas::factory = new AbstractFactory<QtCanvas>;

QPainter::CompositionMode mapCompositionMode(Canvas::DrawMode drawMode) {

	switch (drawMode) {
	default:
	case Canvas::DrawMode_Blend:
		return QPainter::CompositionMode_SourceOver;

	case Canvas::DrawMode_Replace:
		return QPainter::CompositionMode_Source;
	}
}

QtCanvas::QtCanvas()
	: Canvas()
	, qImage(NULL)
{
}

QtCanvas::QtCanvas(int width, int height)
	: Canvas()
	, qImage(new QImage(width, height, QImage::Format_ARGB32))
{
}

QtCanvas::QtCanvas(const boost::filesystem::path &uri)
	: Canvas()
{
	qImage = new QImage(QString::fromStdString(uri.string()));

	if (!qImage || qImage->isNull()) throw std::runtime_error(
		"Qt couldn't load the image."
	);

	setUri(uri);
}

QtCanvas::~QtCanvas() {
	if (qImage) delete qImage;
}

void QtCanvas::drawCircle(int x, int y, int radius, int r, int g, int b, int a, DrawMode drawMode) {
	if (NULL == qImage) return;

	QPainter painter(qImage);

	// Translate the rendering mode to Qt's composition mode.
	painter.setCompositionMode(mapCompositionMode(drawMode));

	painter.setPen(QPen(QColor(r, g, b, a)));
	painter.drawEllipse(QRect(x, y, radius * 2, radius * 2));
}

void QtCanvas::drawFilledBox(int x, int y, int w, int h, int r, int g, int b, int a, DrawMode drawMode) {
	if (NULL == qImage) return;

	QPainter painter(qImage);

	// Translate the rendering mode to Qt's composition mode.
	painter.setCompositionMode(mapCompositionMode(drawMode));

	painter.fillRect(QRect(x, y, w, h), QColor(r, g, b, a));
}

void QtCanvas::drawLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a, DrawMode drawMode) {
	if (NULL == qImage) return;

	QPainter painter(qImage);

	// Translate the rendering mode to Qt's composition mode.
	painter.setCompositionMode(mapCompositionMode(drawMode));

	painter.setPen(QPen(QColor(r, g, b, a)));
	painter.drawLine(QLine(x1, y1, x2, y2));
}

void QtCanvas::drawLineBox(int x, int y, int w, int h, int r, int g, int b, int a, DrawMode drawMode) {
	if (NULL == qImage) return;

	QPainter painter(qImage);

	// Translate the rendering mode to Qt's composition mode.
	painter.setCompositionMode(mapCompositionMode(drawMode));

	painter.setPen(QPen(QColor(r, g, b, a)));
	painter.drawRect(QRect(x, y, w, h));
}

void QtCanvas::fill(int r, int g, int b, int a) {
	if (NULL == qImage) return;

	// @TODO Should we allow blending?
	drawFilledBox(
		0, 0, width(), height(),
		r, g, b, a,
		DrawMode_Replace
	);
}

int QtCanvas::height() const {
	if (NULL == qImage) return 0;

	return qImage->height();
}

unsigned int QtCanvas::pixelAt(int x, int y) const {
	if (NULL == qImage) return 0;

	return reinterpret_cast<unsigned int *>(qImage->scanLine(y))[x];
}

void QtCanvas::render(int x, int y, Canvas *destination, int alpha, DrawMode mode, int sx, int sy, int sw, int sh) const {
	if (NULL == qImage) return;

	QPainter painter(superCast<QtCanvas>(destination)->qImage);

	if (DrawMode_Blend == mode) painter.setOpacity((float)alpha / 255);

	// Translate the rendering mode to Qt's composition mode.
	painter.setCompositionMode(mapCompositionMode(mode));

	// If src_rect doesn't have a valid width or height, set them
	// to this Canvas object's dimensions. Not sure if Qt needs this
	// actually...
	if (0 == sw || 0 == sh) {
		sw = width();
		sh = height();
	}

	painter.drawImage(
		QPoint(x, y),
		*qImage,
		QRect(sx, sy, sw, sh)
	);
}

void QtCanvas::saveToFile(const boost::filesystem::path &filename) {
	qImage->save(QString::fromStdString(filename.string()));
}

void QtCanvas::setPixelAt(int x, int y, unsigned int pixel) {
	if (NULL == qImage) return;

	reinterpret_cast<unsigned int *>(qImage->scanLine(y))[x] = pixel;
}

int QtCanvas::width() const {
	if (NULL == qImage) return 0;

	return qImage->width();
}

}

