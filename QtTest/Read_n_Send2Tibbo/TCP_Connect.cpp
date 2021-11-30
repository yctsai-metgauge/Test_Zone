#include "TCP_Connect.h"

void connectTcp()
{
    QByteArray data= QByteArrayLiteral("\x12\x00\xa4\x42\x51\x00\x00\x99");

    tcpClient = new QTcpSocket( );

    tcpClient->connectToHost("192.168.50.88", 1001);
    if( tcpClient->waitForConnected() ) {
        for(int i=0;i<10;i++){
            tcpClient->write( data );
        }

    }
}
