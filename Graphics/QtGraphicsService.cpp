#include "main/avocado-global.h"

#include "QtGraphicsService.h"

#include "QtImage.h"

namespace avo {

AbstractFactory<QtGraphicsService> *QtGraphicsService::factory = new AbstractFactory<QtGraphicsService>;

QtGraphicsService::QtGraphicsService() {

	Image::factoryManager.setInstance(QtImage::factory);
}

QtGraphicsService::~QtGraphicsService() {
}

GraphicsService::SpecialKeyCodes QtGraphicsService::specialKeyCodes() {

	SpecialKeyCodes keyMap;

	return keyMap;
}

}
