TARGET = GraphicsService-qt

include(../../../core/Graphics/Graphics.pri)

CONFIG += qt

SOURCES += \
	\
	QtGraphicsService.cpp \
	\
	QtImage.cpp

HEADERS += \
	\
	QtGraphicsService.h \
	\
	QtImage.h
