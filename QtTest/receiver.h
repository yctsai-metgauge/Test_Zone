#ifndef RECIEVER_H
#define RECIEVER_H

#include <QObject>

class Reciever : public QObject
{
    Q_OBJECT
public:
    explicit Reciever(QObject *parent = 0);

signals:

public slots:
    void slotRecieveButtonClicked(); //用來接收按鈕送出的訊號。
};
