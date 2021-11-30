#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <QtNetwork>
#include <chrono>
#include <thread>
#include <time.h>
#include <QVector>
#include <QObject>
typedef std::chrono::high_resolution_clock Clock;

QTcpSocket *tcpClient_WCtrigger;



void parse_format2Tibbo(QByteArray &decimal_num,unsigned __int8 max_digit_after_dot=3,unsigned __int8 target_digit_num=6){
/*
    Transform the format to:
    1. pure digits ( w/o dot )
    2. target number of digits
    The function can also hadle higher input precision input data (more digit after dot)
    ex. input precision: 3 decimal point, target digit number: 6
    9.9   -> 009900
    9.99  -> 009990
    9.999 -> 009999
    99.9  -> 099900
    The function is equal to num*1000 and prepend 0 to target digit number
*/


    bool ok;
    float num = decimal_num.toFloat(&ok);
    if (!ok) qDebug() << "check parse_format2Tibbo";
    num = num*(10^max_digit_after_dot);

    decimal_num.setNum(num);
    while (decimal_num.size() < target_digit_num){
        decimal_num.prepend("0");
    }


}


QVector<QByteArray> LDX_Vector,LDY_Vector;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


        auto start_time = Clock::now();
    QFile file("C:/Users/user/Documents/Real_Data/ar_Test_20211111113025_001.csv");
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << file.errorString();
            return 1;
        }

        QByteArray LDX,LDY;
        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            LDX = line.split(',').at(0);
            parse_format2Tibbo(LDX);
            LDX_Vector.append(LDX);
            LDY = line.split(',').at(1);
            parse_format2Tibbo(LDY);
            LDY_Vector.append(LDY);
        }

        auto end_time = Clock::now();
        double dur_micro = std::chrono::duration<double, std::micro>(end_time - start_time).count();
        qDebug() << "time cost for reading data:" << dur_micro;
        file.close();
//        int entries_of_data {LDX_Vector.size()};
//        connectTcp();


        double target_hz {10};
        double target_msec {(1e+06/target_hz)};
        int cali_msec {(int) target_msec};
//        int cali_cycle {100};
//        int ctr{0};

//        QByteArray data= QByteArrayLiteral("\x12\x00\xa4\x42\x51\x00\x00\x99");
//        connectTcp();
        tcpClient_WCtrigger = new QTcpSocket( );

        tcpClient_WCtrigger->connectToHost("192.168.50.88", 1001);

//                double time_deviation_sum {0.0};
//                double time_deviation_avg {0.0};
//                double time_avg {0.0};

//                for (int i = 0; i < cali_cycle; i++){


                    std::this_thread::sleep_for(std::chrono::microseconds(cali_msec));

//                    auto start_time = Clock::now();
//                    QTimer *timer = new QTimer();
//                    timer->start(1000);


//                    send(sock , hello , strlen(hello) , 0 );

                    tcpClient_WCtrigger->write( "data" );
//                    auto end_time = Clock::now();
//                    double dur_micro = std::chrono::duration<double, std::micro>(end_time - start_time).count();
                    // std::cout <<"Time difference:"<< dur_micro <<" microseconds" << std::endl;
//                    time_avg += dur_micro;
//                    time_deviation_sum+=(dur_micro-target_msec);

//                }
//                time_deviation_avg = time_deviation_sum / cali_cycle;
                // myfile << time_deviation_avg << std::endl;
//                cali_msec = cali_msec - int (time_deviation_avg);
//                time_avg = time_avg / cali_cycle;
//                qDebug()<< "avg_Hz: " << (1e+06/time_avg);

    qDebug() << "over";
    return a.exec();
}
