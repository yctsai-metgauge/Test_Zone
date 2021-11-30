#include <math.h>
#include <QDebug>
#include "parse.h"

parse::parse()
{

}

char parse::Metgauge_CalcChecksum(char* data, int length)
{
    int i;
    char checksum = 0;
    for (i=0;i<length-1;i++) {
        checksum += *data++;
        checksum = checksum & 0x000000ff;
    }
    return checksum;
}

//bool parse::verifyChecksum(char* data, int length)
//{
//    char checksum = Metgauge_CalcChecksum(data,length);
//    if (checksum == data[length-1])
//      return true;
//    else
//      return false;
//}

int parse::Metgauge_TempVerifyChecksum(char* data, int length)
{
    char checksum;
    checksum = Metgauge_CalcChecksum(data,length-1);
    if (checksum == data[length-1])
      return 1;
    else
      return 0;
}

int parse::Metgauge_GaugeVerifyChecksum(char* data, int length)
{
    char checksum;
    checksum = Metgauge_CalcChecksum(data,length);
    if (checksum == data[length-1])
      return 1;
    else
      return 0;
}



// Rounding num for index digit
double parse::rounding(double num, int index)
{
    bool isNegative = false;
    if (num < 0) {
        isNegative = true;
        num = -num;
    }

    if (index >= 0) {
        int multiplier;
        multiplier = pow(10, index);
        num = (int)(num * multiplier + 0.5) / (multiplier * 1.0);
    }

    if (isNegative)
        num = -num;
    return num;
}

void parse::setParameter(qreal coeff, qreal steelT)
{
    coefficient = coeff;
    steel_temperature = steelT;
}



