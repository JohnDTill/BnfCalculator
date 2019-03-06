#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

/*
#include "numbers.h"
#include <iostream>
int main(){
    big_uint a("3");
    std::cout << a << std::endl;

    big_uint b("10");
    std::cout << b << std::endl;

    std::cout << a + b << std::endl;
    //std::cout << a - b << std::endl;
    std::cout << a * b << std::endl;

    big_uint c;
    big_uint d;
    big_uint::longDivision(a,b,c,d);
    std::cout << c << std::endl;
    std::cout << d << std::endl;

    big_uint::longDivision(b,a,c,d);
    std::cout << c << std::endl;
    std::cout << d << std::endl;

    std::cout << pow(a,b) << std::endl;

    return 0;
}
*/
