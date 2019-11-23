QT -= core gui widgets

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ./include
DEPENDPATH  += ./include

SOURCES += \
    src/main.cpp

HEADERS += \
    include/cs/Types.h \
    include/cs/ExprBase.h \
    include/cs/BinaryOperators.h \
    include/cs/impl/BinaryOperatorsImpl.h \
    include/cs/impl/ArrayImpl.h \
    include/cs/Array.h \
    include/cs/NumericArray.h \
    include/cs/impl/FunctionsImpl.h \
    include/cs/impl/UnaryOperatorsImpl.h \
    include/cs/Functions.h \
    include/cs/UnaryOperators.h \
    include/cs/impl/Indexing.h \
    include/cs/IndexPolicy.h \
    include/cs/impl/IndexPolicyImpl.h
