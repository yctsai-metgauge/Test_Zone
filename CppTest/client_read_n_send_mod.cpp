#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>

#include <chrono>
#include <thread>
#include <time.h>
#include <unistd.h>
#include <bits/stdc++.h>
// #include <fstream>
typedef std::chrono::high_resolution_clock Clock;


void parse_format2Tibbo(char *outStr,float num, int max_digit_after_dot=3, int target_digit_num=6){
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

    // std::cout<<num<<std::endl;
    num = num*pow(10.0,max_digit_after_dot);    //<- problem here122
    // std::cout<<num<<std::endl;
    // char test[10];
    // sprintf(test,"%06.0f",num);

    char sprintf_format[]{"%06.0f"};

    if (target_digit_num != 6){
        char target_digit_num_char[1];
        sprintf(target_digit_num_char,"%d",target_digit_num);
        *(sprintf_format+2) = *target_digit_num_char;
    }
    
    sprintf(outStr,sprintf_format,num);
    std::cout<<"parse_format2Tibbo: "<<outStr<<std::endl;

    // std::string string_num = std::to_string(num);
    // std::cout<<string_num<<std::endl;
    // for(int i=0; i < target_digit_num; i++){
    //     outStr[i] = string_num[i];
    // }
    

}

int main()
{
    char c; // to eat the commas

    float LDX, LDY, z;
    std::vector<float> LDX_Vec, LDY_Vec;

    std::ifstream file("sample_data.csv");
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        ss >> LDX >> c >> LDY;
        LDX_Vec.push_back(LDX);
        LDY_Vec.push_back(LDY);
    }


    char hello[6];
    parse_format2Tibbo(hello, 3.688,3,6);
    std::cout<<hello<<std::endl;
    
    return 0;
}
