#ifndef PARSE_H
#define PARSE_H

#include <QObject>

#include "rodcheck.h"

typedef unsigned int   uint32;


class parse
{
public:
    parse();


    char Metgauge_CalcChecksum(char* data, int length);
    //bool verifyChecksum(char* data, int length);
    int Metgauge_TempVerifyChecksum(char* data, int length);
    int Metgauge_GaugeVerifyChecksum(char* data, int length);

    double rounding(double num, int index);

    // Thermal compensation

    void setParameter(qreal, qreal);


private:

    qreal coefficient  = 0;
    qreal steel_temperature = 20;

};

#endif // PARSE_H
