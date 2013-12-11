TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    MultiLayerGraph/multilayergraph.cpp \
    MultiLayerGraph/maxflow.cpp \
    MultiLayerGraph/graph.cpp \
    adaptivegraphcuts.cpp

INCLUDEPATH += D:\OpenCV-2.4.3\build\include\

LIBS += D:\OpenCV-2.4.3\build\x86\qt5\install\lib\libopencv_core243.dll.a

LIBS += D:\OpenCV-2.4.3\build\x86\qt5\install\lib\libopencv_highgui243.dll.a

LIBS += D:\OpenCV-2.4.3\build\x86\qt5\install\lib\libopencv_imgproc243.dll.a

HEADERS += \
    MultiLayerGraph/multilayergraph.h \
    MultiLayerGraph/mlginstances.inc \
    MultiLayerGraph/instances.inc \
    MultiLayerGraph/graph.h \
    MultiLayerGraph/block.h \
    adaptivegraphcuts.h
