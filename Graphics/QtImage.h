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
 * Qt image SPI implementation (SPII). The SPII uses QPixmap to implement the
 * image operations.
 *
 * @ingroup Qt
 * @ingroup Resources
 */
class QtImage : public Image {

public:

	/**
	 * Build a NULL QPixmap.
	 */
	QtImage();

	/**
	 * Load a QPixmap from a filename.
	 */
	QtImage(const boost::filesystem::path &uri);

	/**
	 * Destroy QPixmap.
	 */
	~QtImage();

	int height() const;

	int width() const;

	/**
	 * Get the pixmap.
	 */
	QPixmap *qPixmap() const;

	static AbstractFactory<QtImage> *factory;

private:

	QPixmap *_qPixmap;

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
