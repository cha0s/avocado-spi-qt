#ifndef AVOCADO_QTCANVAS_H
#define AVOCADO_QTCANVAS_H

#include "core/avocado-global.h"

#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtWidgets/QSlider>

#include "core/FS.h"
#include "core/Graphics/Canvas.h"
#include "core/Graphics/GraphicsService.h"

namespace avo {

/**
 * @addtogroup Graphics
 * @{
 */

/**
 * Qt Canvas SPI implementation (SPII). The SPII uses QImage to implement the
 * image operations.
 *
 * @ingroup Qt
 */
class QtCanvas : public Canvas {

public:

	/**
	 * Build a NULL QCanvas.
	 */
	QtCanvas();

	/**
	 * Load a QCanvas from a filename.
	 */
	QtCanvas(const boost::filesystem::path &uri);

	/**
	 * Build a QCanvas to given width/height specifcations.
	 */
	QtCanvas(int width, int height);

	/**
	 * Destroy QCanvas.
	 */
	~QtCanvas();

	void drawCircle(int x, int y, int radius, int r, int g, int b, double a, GraphicsService::BlendMode blendMode);

	void drawFilledBox(int x, int y, int w, int h, int r, int g, int b, double a, GraphicsService::BlendMode blendMode);

	void drawLine(int x1, int y1, int x2, int y2, int r, int g, int b, double a, GraphicsService::BlendMode blendMode);

	void drawLineBox(int x, int y, int w, int h, int r, int g, int b, double a, GraphicsService::BlendMode blendMode);

	void fill(int r, int g, int b, double a);

	int height() const;

	unsigned int pixelAt(int x, int y) const;

	void saveToFile(const boost::filesystem::path &filename);

	void setPixelAt(int x, int y, unsigned int pixel);

	int width() const;

	/**
	 * Get the image.
	 */
	QImage *qImage() const;

	static AbstractFactory<QtCanvas> *factory;

private:

	QImage *_qImage;

};

/**
 * @ingroup Manufacturing
 * @ingroup Qt
 * @ingroup SPI
 */
template <>
class AbstractFactory<QtCanvas> : public AbstractFactory<Canvas> {

public:

	virtual ~AbstractFactory<QtCanvas>() {}

	QtCanvas *create(const boost::filesystem::path &uri) {
		return new QtCanvas(uri);
	}

	QtCanvas *create(int width, int height) {
		return new QtCanvas(width, height);
	}

	QtCanvas *create() {
		return new QtCanvas();
	}

};

/**
 * @}
 */

}

#endif // AVOCADO_QTCANVAS_H
