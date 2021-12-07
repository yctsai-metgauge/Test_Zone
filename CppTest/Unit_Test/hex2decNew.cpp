#include <stdio.h>
#include <iostream>
#include <math.h>

float hex2decNew(char* hex, int length)
{
    float fresult = 0.0;
    unsigned long result = 0;
    unsigned long tmp = 0;
    
    for (int i=0; i<length; i++) {
        switch (i)
        {
        case 0:
            tmp = (hex[i] & 0xff);
            break;
        case 1:
            tmp = (hex[i] & 0xff) << 8;
            break;
        case 2:
            tmp = (hex[i] & 0xff) << 16;
            break;
        default:
            tmp = (hex[i] & 0xff) << 24;
            break;
        }
        result += tmp;
    }
    fresult = result / 1000.0;
    return fresult;
        
}

unsigned long laser_hex2dec(char* hex, int length)
{
    unsigned long result = 0;
    
    for (int i=0; i<length; i++){
        unsigned long tmp = 0;
        tmp = (hex[i] & 0xff);
        tmp = tmp/16;
        tmp = tmp*10;
        // tmp+=(hex[i] & 0xff) / 16 * 10;
        tmp+=(hex[i] & 0xff) % 16 * pow(10,2*(length-i-1));
        // result += ((hex[i] & 0xff) / 16 * 10 + (hex[i] & 0xff) % 16 * pow(10,2*(length-i-1)));
        result += tmp;
    }
    return result;
}

unsigned long hex2dec(char* hex, int length)
{
    unsigned long result = 0;
    
    for (int i=0; i<length; i++){
        
        result += (hex[i] & 0xff) * pow(16,(length-i));
    }
    return result;
}



unsigned char laser_dec2dhex(unsigned char in) {
    // (14)dec  ->  (14)hex=(20)dec
    return ((in % 10) * 0x01) + ((in / 10) * 0x10);
}



int main(int argc, char **argv)
{
	printf("hello world...\n");
    // char test_hex[] = {0x32,0x35,0x39,0x38,0x34};
    // char test_hex[] = {0x03,0x06,0x91} ;  // 5000(10) = 1388(16)
    // char *hex = test_hex;
    // float func_result = 0.0;
    // float f = 30705;
    // float d;
    // d=f/1000.0;
    // func_result = laser_hex2dec(hex,3);
    unsigned char a = laser_dec2dhex(14);
    std::cout<< a <<std::endl;
    // std::cout<< d <<std::endl;
    // int a = 17;
    // char test_hex[4]={0};
    // test_hex[0]=char(a);


	return 0;

}
