TARGET = TimingService-qt

include(../../../core/Timing/Timing.pri)

CONFIG += qt

SOURCES += \
	\
	QtTimingService.cpp \
	\
	QtCounter.cpp

HEADERS += \
	\
	QtTimingService.h \
	\
	QtCounter.h
