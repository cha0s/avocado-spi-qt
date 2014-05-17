#ifndef AVOCADO_QTSPRITE_H
#define AVOCADO_QTSPRITE_H

#include "core/avocado-global.h"

#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtGui/QPixmap>
#include <QtWidgets/QSlider>

#include "core/Graphics/Canvas.h"
#include "core/Graphics/GraphicsService.h"
#include "core/Graphics/Sprite.h"
#include "core/Graphics/Window.h"

namespace avo {

/**
 * @addtogroup Graphics
 * @{
 */

/**
 * Qt Sprite SPI implementation (SPII).
 *
 * @ingroup Qt
 */
class QtSprite : public Sprite {

public:

	QtSprite();

	void renderTo(Canvas *destination) const;

	/**
	 * TODO: Currently unsupported.
	 */
	void renderTo(Window *destination) const;

	void setAlpha(double alpha);

	void setBlendMode(GraphicsService::BlendMode blendMode);

	void setPosition(int x, int y);

	void setRotation(double angle, int orientX, int orientY);

	void setScale(double factorX, double factorY);

	void setSourceRectangle(int x, int y, int w, int h);

	static AbstractFactory<QtSprite> *factory;

private:

	double alpha;

	GraphicsService::BlendMode blendMode;

	int x;
	int y;

	double angle;
	int orientX;
	int orientY;

	double factorX;
	double factorY;

	int sourceX;
	int sourceY;
	int sourceW;
	int sourceH;

};

/**
 * @ingroup Manufacturing
 * @ingroup Qt
 * @ingroup SPI
 */
template <>
class AbstractFactory<QtSprite> : public AbstractFactory<Sprite> {

public:

	virtual ~AbstractFactory<QtSprite>() {}

	QtSprite *create() {
		return new QtSprite();
	}

};

/**
 * @}
 */

}

#endif // AVOCADO_QTSPRITE_H
