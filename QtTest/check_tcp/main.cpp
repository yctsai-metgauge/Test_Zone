#include <QCoreApplication>
#include "new_tcp_thread.h"
QString WireMaster;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    new_tcp_thread n;
    n.Connect(WireMaster,1002);
    return a.exec();
}
