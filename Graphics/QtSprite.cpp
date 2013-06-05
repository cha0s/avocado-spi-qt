#include "core/avocado-global.h"

#include "QtCanvas.h"
#include "QtImage.h"
#include "QtSprite.h"

namespace avo {

AbstractFactory<QtSprite> *QtSprite::factory = new AbstractFactory<QtSprite>;

QtSprite::QtSprite()
	: Sprite()
	, alpha(1)
	, blendMode(GraphicsService::BlendMode_Blend)
	, x(0)
	, y(0)
	, factorX(1)
	, factorY(1)
	, sourceX(0)
	, sourceY(0)
	, sourceW(0)
	, sourceH(0)
{
}

static QPainter::CompositionMode mapCompositionMode(GraphicsService::BlendMode blendMode) {

	switch (blendMode) {
	default:
	case GraphicsService::BlendMode_Blend:
		return QPainter::CompositionMode_SourceOver;

	case GraphicsService::BlendMode_Replace:
		return QPainter::CompositionMode_Source;
	}
}

void QtSprite::renderTo(Canvas *destination) const {
	if (NULL == canvas() && NULL == image()) return;

	QPainter painter(Canvas::superCast<QtCanvas>(destination)->qImage());

	if (GraphicsService::BlendMode_Blend == blendMode) painter.setOpacity(alpha);

	painter.rotate(angle);

	painter.scale(factorX, factorY);

	// Translate the rendering mode to Qt's composition mode.
	painter.setCompositionMode(mapCompositionMode(blendMode));

	int sw = sourceW;
	int sh = sourceH;

	// If src_rect doesn't have a valid width or height, set them
	// to this Image object's dimensions. Not sure if Qt needs this
	// actually...
	if (0 == sw || 0 == sh) {
		sw = canvas() ? canvas()->width() : image()->width();
		sh = canvas() ? canvas()->height() : image()->height();
	}

	if (image()) {
		painter.drawPixmap(
			QPoint(x, y),
			*Image::superCast<QtImage>(image())->qPixmap(),
			QRect(sourceX, sourceY, sw, sh)
		);
	}
	else if (canvas()) {
		painter.drawImage(
			QPoint(x, y),
			*Canvas::superCast<QtCanvas>(canvas())->qImage(),
			QRect(sourceX, sourceY, sw, sh)
		);
	}
}

void QtSprite::renderTo(Window *destination) const {
	AVOCADO_UNUSED(destination);
}

void QtSprite::setAlpha(double alpha) {
	this->alpha = alpha;
}

void QtSprite::setBlendMode(GraphicsService::BlendMode blendMode) {
	this->blendMode = blendMode;
}

void QtSprite::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

void QtSprite::setRotation(double angle) {
	this->angle = angle;
}

void QtSprite::setScale(double factorX, double factorY) {
	this->factorX = factorX;
	this->factorY = factorY;
}

void QtSprite::setSourceRectangle(int x, int y, int w, int h) {
	this->sourceX = x;
	this->sourceY = y;
	this->sourceW = w;
	this->sourceH = h;
}

}
