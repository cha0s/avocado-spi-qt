#include "core/avocado-global.h"

#include "QtCanvas.h"
#include "QtImage.h"

namespace avo {

AbstractFactory<QtImage> *QtImage::factory = new AbstractFactory<QtImage>;

QtImage::QtImage()
	: Image()
	, _qPixmap(NULL)
{
}

QtImage::QtImage(const boost::filesystem::path &uri)
	: Image()
{
	_qPixmap = new QPixmap(QString::fromStdString(uri.string()));

	if (!_qPixmap || _qPixmap->isNull()) throw std::runtime_error(
		"Qt couldn't load the image."
	);

	setUri(uri);
}

QtImage::~QtImage() {
	if (_qPixmap) delete _qPixmap;
}

int QtImage::height() const {
	if (NULL == _qPixmap) return 0;

	return _qPixmap->height();
}

int QtImage::width() const {
	if (NULL == _qPixmap) return 0;

	return _qPixmap->width();
}

QPixmap *QtImage::qPixmap() const {
	return _qPixmap;
}

}

