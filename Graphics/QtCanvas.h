#ifndef AVOCADO_QTCANVAS_H
#define AVOCADO_QTCANVAS_H

#include "core/avocado-global.h"

#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtGui/QSlider>

#include "core/FS.h"
#include "core/Graphics/Canvas.h"

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
class QtCanvas : public Canvas {

public:

	friend class QtImage;

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

	void drawCircle(int x, int y, int radius, int r, int g, int b, int a = 255, DrawMode drawMode = DrawMode_Blend);

	void drawFilledBox(int x, int y, int w, int h, int r, int g, int b, int a = 255, DrawMode drawMode = DrawMode_Blend);

	void drawLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a = 255, DrawMode drawMode = DrawMode_Blend);

	void drawLineBox(int x, int y, int w, int h, int r, int g, int b, int a = 255, DrawMode drawMode = DrawMode_Blend);

	void fill(int r, int g, int b, int a = 255);

	int height() const;

	bool isValid() const { return width() != 0 && height() != 0; }

	unsigned int pixelAt(int x, int y) const;

	void render(int x, int y, Canvas *destination, int alpha = 255, DrawMode mode = DrawMode_Blend, int sx = 0, int sy = 0, int sw = 0, int sh = 0) const AVOCADO_ENSURE_STACK_ALIGNED_FOR_SSE;

	void saveToFile(const boost::filesystem::path &filename);

	void setPixelAt(int x, int y, unsigned int pixel);

	int width() const;

	static AbstractFactory<QtCanvas> *factory;

private:

	QImage *qImage;

};

/**
 * @ingroup Manufacturing
 * @ingroup Qt
 * @ingroup Resources
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
