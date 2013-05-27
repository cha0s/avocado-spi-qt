#include "core/avocado-global.h"

#include "QtCanvas.h"
#include "QtImage.h"

namespace avo {

AbstractFactory<QtImage> *QtImage::factory = new AbstractFactory<QtImage>;

QPainter::CompositionMode mapCompositionMode(Image::DrawMode drawMode) {

	switch (drawMode) {
	default:
	case Image::DrawMode_Blend:
		return QPainter::CompositionMode_SourceOver;

	case Image::DrawMode_Replace:
		return QPainter::CompositionMode_Source;
	}
}

QtImage::QtImage()
	: Image()
	, qPixmap(NULL)
{
}

QtImage::QtImage(const boost::filesystem::path &uri)
	: Image()
{
	qPixmap = new QPixmap(QString::fromStdString(uri.string()));

	if (!qPixmap || qPixmap->isNull()) throw std::runtime_error(
		"Qt couldn't load the image."
	);

	setUri(uri);
}

QtImage::~QtImage() {
	if (qPixmap) delete qPixmap;
}

int QtImage::height() const {
	if (NULL == qPixmap) return 0;

	return qPixmap->height();
}

void QtImage::render(int x, int y, Canvas *destination, int alpha, DrawMode mode, int sx, int sy, int sw, int sh) const {
	if (NULL == qPixmap) return;

	QPainter painter(Canvas::superCast<QtCanvas>(destination)->qImage);

	if (DrawMode_Blend == mode) painter.setOpacity((float)alpha / 255);

	// Translate the rendering mode to Qt's composition mode.
	painter.setCompositionMode(mapCompositionMode(mode));

	// If src_rect doesn't have a valid width or height, set them
	// to this Image object's dimensions. Not sure if Qt needs this
	// actually...
	if (0 == sw || 0 == sh) {
		sw = width();
		sh = height();
	}

	painter.drawPixmap(
		QPoint(x, y),
		*qPixmap,
		QRect(sx, sy, sw, sh)
	);
}

int QtImage::width() const {
	if (NULL == qPixmap) return 0;

	return qPixmap->width();
}

}

