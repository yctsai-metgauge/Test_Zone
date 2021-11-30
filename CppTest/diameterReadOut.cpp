#include <stdio.h>
#include <iostream>
#include <math.h>

// function to convert decimal to hexadecimal
void decToHexa(char *target, int n)
{
    // char array to store hexadecimal number
    char hexaDeciNum[8]={0};
 
    // counter for hexadecimal number array
    int i = 0;
    while (n != 0) {
        // temporary variable to store remainder
        int temp = 0;
 
        // storing remainder in temp variable.
        temp = n % 256;
 
        target[i] = char(temp);
 
        n = n / 256;
        i++;
    }
 
    // printing hexadecimal number array in reverse order
        

    
}

int diameterReadIn( char *target, float laser_input)
{

    target[0] = '\x11';
    target[1] = '\x4e';
    target[2] = '\x00';
    target[3] = '\x00';
    return 0; 
}


// Big endian
float diameterReadOut(char *hex, int )
{
    float fresult = 0.0;
    unsigned long result = 0;


    result += (hex[0] & 0xff);
    result += ((hex[1] & 0xff) << 8);
    result += ((hex[2] & 0xff) << 16);
    result += ((hex[3] & 0xff) << 24);


    fresult = result / 1000.0;
    return fresult;
}

int main(int argc, char **argv)
{
	printf("hello world...\n");

    // char test_hex[] = "\x11\x4e\x00\x00" ;
    char test_hex[4]={0};
    // diameterReadIn(test_hex, 19.985);
    decToHexa(test_hex,000000);
    char *hex = test_hex;
    // std::cout<< test_hex <<std::endl;
    
    float func_result {0.0};
    func_result = diameterReadOut(hex,4);
    std::cout<< func_result <<std::endl;

	return 0;

}