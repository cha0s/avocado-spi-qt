#ifndef AVOCADO_QTIMAGE_H
#define AVOCADO_QTIMAGE_H

#include "core/avocado-global.h"

#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtGui/QPixmap>
#include <QtGui/QSlider>

#include "core/FS.h"
#include "core/Graphics/Image.h"

namespace avo {

/**
 * @addtogroup Graphics
 * @{
 */

/**
 * Qt image SPI implementation (SPII). The SPII uses QImage to implement the
 * image operations.
 *
 * @ingroup Qt
 * @ingroup Resources
 */
class QtImage : public Image {

public:

	/**
	 * Build a NULL QImage.
	 */
	QtImage();

	/**
	 * Load a QImage from a filename.
	 */
	QtImage(const boost::filesystem::path &uri);

	/**
	 * Destroy QImage.
	 */
	~QtImage();

	int height() const;

	void render(int x, int y, Canvas *destination, int alpha = 255, DrawMode mode = DrawMode_Blend, int sx = 0, int sy = 0, int sw = 0, int sh = 0) const AVOCADO_ENSURE_STACK_ALIGNED_FOR_SSE;

	int width() const;

	static AbstractFactory<QtImage> *factory;

private:

	QPixmap *qPixmap;

};

/**
 * @ingroup Manufacturing
 * @ingroup Qt
 * @ingroup Resources
 * @ingroup SPI
 */
template <>
class AbstractFactory<QtImage> : public AbstractFactory<Image> {

public:

	virtual ~AbstractFactory<QtImage>() {}

	QtImage *create(const boost::filesystem::path &uri) {
		return new QtImage(uri);
	}

	QtImage *create() {
		return new QtImage();
	}

};

/**
 * @}
 */

}

#endif // AVOCADO_QTIMAGE_H
