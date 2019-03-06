#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

#include <iostream>
#include <string>
#include <QStatusBar>

static QStatusBar* error_status_bar;

[[noreturn]]
inline void error(std::string msg){
    error_status_bar->showMessage(QString::fromStdString(msg));
    std::cout << msg << std::endl;
    throw(1);
}

#endif // ERRORHANDLING_H
