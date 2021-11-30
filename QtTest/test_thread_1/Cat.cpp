#include "cat.h"

Cat::Cat(){
}

void Cat::run(){
    for(int i=1; i<=100; i++){
        qDebug() << name << i;
        QThread::currentThread()->msleep(1); // 暫停 0.1 秒
    }
}
