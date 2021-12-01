#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#define PORT 1001
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
    // std::cout<<"parse_format2Tibbo: "<<outStr<<std::endl;

    // std::string string_num = std::to_string(num);
    // std::cout<<string_num<<std::endl;
    // for(int i=0; i < target_digit_num; i++){
    //     outStr[i] = string_num[i];
    // }
    

}

int main()
{

    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    // const char *hello;
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "192.168.50.88", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }


    char c; // to eat the commas

    float LDX, LDY, z;
    std::vector<float> LDX_Vec, LDY_Vec;
    int data_size{0};
    std::ifstream file("ar_19_5mm_20211112085324_394_raw.csv");
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        ss >> LDX >> c >> LDY;
        LDX_Vec.push_back(LDX);
        LDY_Vec.push_back(LDY);
        data_size++;
    }

    char LDX_char[6],LDY_char[6];
    char send2Tibbo[12];
    

    double target_hz {800};
    double target_msec {(1e+06/target_hz)};
    int cali_msec {(int) target_msec};
    int cali_cycle {1000};
    // int ctr{0};


    while (true){
        double time_deviation_sum {0.0};
        double time_deviation_avg {0.0};
        double time_avg {0.0};
        double shift {0.0};
        double max_shift{0.0};
        

        for (int i = 0; i < cali_cycle; i++){

            auto start_time = Clock::now();

            std::this_thread::sleep_for(std::chrono::microseconds(cali_msec));
            // microsleep(cali_msec);
            // selectsleep(cali_msec);
            parse_format2Tibbo(LDX_char, LDX_Vec.at(i%(data_size)), 3, 6);
            parse_format2Tibbo(LDY_char, LDY_Vec.at(i%(data_size)), 3, 6);
            strcpy (send2Tibbo,LDX_char);
            strcat (send2Tibbo,LDY_char);
            send(sock , send2Tibbo , strlen(send2Tibbo) , 0 );
            auto end_time = Clock::now();
            double dur_micro = std::chrono::duration<double, std::micro>(end_time - start_time).count();
            // std::cout <<"Time difference:"<< dur_micro <<" microseconds" << std::endl;
            time_avg += dur_micro;
            time_deviation_sum+=(dur_micro-target_msec);

        }
        time_deviation_avg = time_deviation_sum / cali_cycle;
        // myfile << time_deviation_avg << std::endl;
        cali_msec = cali_msec - int (time_deviation_avg);
        time_avg = time_avg / cali_cycle;
        std::cout<< "avg_Hz: " << (1e+06/time_avg) << std::endl;
        // ctr++;
    }



    return 0;
}
