TARGET = TimingService-qt

include(../../../main/Timing/Timing.pri)

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
