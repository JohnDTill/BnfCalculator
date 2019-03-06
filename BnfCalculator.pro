QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BnfCalculator
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

INCLUDEPATH += AST

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        AST/eliteralnode.cpp \
        AST/piliteralnode.cpp \
        AST/numberliteralnode.cpp \
    AST/rationalliteralnode.cpp \
    AST/subtractnode.cpp \
    AST/multiplynode.cpp \
    AST/modulusnode.cpp \
    AST/exponentnode.cpp \
    AST/dividenode.cpp \
    AST/additionnode.cpp \
    AST/tangentnode.cpp \
    AST/sinenode.cpp \
    AST/cosinenode.cpp \
    AST/absolutenode.cpp \
    AST/factorialnode.cpp \
    AST/groupingnode.cpp \
    AST/lognode.cpp \
    AST/naturallognode.cpp \
    AST/negatenode.cpp

HEADERS += \
        mainwindow.h \
        token.h \
        tokentypes.h \
        scanner.h \
        parser.h \
        astnode.h \
        errorhandling.h \
        numbers.h \
        ast.h \
        AST/eliteralnode.h \
        AST/piliteralnode.h \
        AST/numberliteralnode.h \
    AST/rationalliteralnode.h \
    AST/subtractnode.h \
    AST/multiplynode.h \
    AST/modulusnode.h \
    AST/exponentnode.h \
    AST/dividenode.h \
    AST/additionnode.h \
    AST/tangentnode.h \
    AST/sinenode.h \
    AST/cosinenode.h \
    AST/absolutenode.h \
    AST/factorialnode.h \
    AST/groupingnode.h \
    AST/lognode.h \
    AST/naturallognode.h \
    AST/negatenode.h

FORMS += mainwindow.ui

DISTFILES += Notes

RC_ICONS += resources/Pi.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
