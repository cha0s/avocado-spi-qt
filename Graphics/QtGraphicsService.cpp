#include "core/avocado-global.h"

#include "QtGraphicsService.h"

#include "QtImage.h"
#include "QtSprite.h"

namespace avo {

AbstractFactory<QtGraphicsService> *QtGraphicsService::factory = new AbstractFactory<QtGraphicsService>;

QtGraphicsService::QtGraphicsService() {

	Image::factoryManager.setInstance(QtImage::factory);
	Sprite::factoryManager.setInstance(QtSprite::factory);
}

QtGraphicsService::~QtGraphicsService() {
}

}
