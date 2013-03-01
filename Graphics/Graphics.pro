TARGET = GraphicsService-qt

include(../../../main/Graphics/Graphics.pri)

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
