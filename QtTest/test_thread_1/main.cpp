#include "cat.h"

#include <QCoreApplication>

int main(int argc, char * argv[]) {

    QCoreApplication a(argc,argv);

    Cat c;
    c.name = "A";
    c.start();              // 呼叫 run()

    Cat c2;
    c2.name = "B";
    c2.start();            // 呼叫 run()

    return a.exec();
}
