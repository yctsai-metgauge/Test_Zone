#include <stdio.h>
//#include <iostream.h>

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



int main(int argc, char **argv)
{
	printf("hello world\n");
//    char test_hex[] = {'5','2','4','7'};
//    char *hex = &test_hex
    char *hex  = "5247";
    float func_result{0.0};
    func_result = hex2decNew(hex,4);
    printf(func_result);
//    std::cout<< func_result <<endl;
	return 0;
}
