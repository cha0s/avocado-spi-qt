TARGET = GraphicsService-qt

include(../../../core/Graphics/Graphics.pri)

CONFIG += qt

SOURCES += \
	\
	QtGraphicsService.cpp \
	\
	QtCanvas.cpp QtImage.cpp QtSprite.cpp

HEADERS += \
	\
	QtGraphicsService.h \
	\
	QtCanvas.h QtImage.h QtSprite.h
