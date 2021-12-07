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

    int sock_M = 0, sock_S = 0, valread;
    struct sockaddr_in serv_addr_M, serv_addr_S;
    // const char *hello;
    char buffer[1024] = {0};

    if ((sock_M = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket(Master) creation error \n");
        return -1;
    }
    if ((sock_S = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket(Slave) creation error \n");
        return -1;
    }
   
    serv_addr_M.sin_family = AF_INET;
    serv_addr_M.sin_port = htons(PORT);
    serv_addr_S.sin_family = AF_INET;
    serv_addr_S.sin_port = htons(PORT);  

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "192.168.50.99", &serv_addr_M.sin_addr)<=0) 
    {
        printf("\nInvalid Master address/ Address not supported \n");
        return -1;
    }
    if(inet_pton(AF_INET, "192.168.50.100", &serv_addr_S.sin_addr)<=0) 
    {
        printf("\nInvalid Slave address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock_M, (struct sockaddr *)&serv_addr_M, sizeof(serv_addr_M)) < 0)
    {
        printf("\nMaster Connection Failed \n");
        return -1;
    }
    if (connect(sock_S, (struct sockaddr *)&serv_addr_S, sizeof(serv_addr_S)) < 0)
    {
        printf("\nSlave Connection Failed \n");
        return -1;
    }

    char c; // to eat the commas

    float LD1, LD2, LD3, LD4, LD5, LD6;
    std::vector<float> LD1_Vec, LD2_Vec, LD3_Vec, LD4_Vec, LD5_Vec, LD6_Vec;
    int data_size{0};
    std::ifstream file("_ar_210714-13_210715_1842_175_mod.csv");
    std::string line;
    char LD1_char[6],LD2_char[6],LD3_char[6],LD4_char[6],LD5_char[6],LD6_char[6],Offset_empty[6]={0x30,0x30,0x30,0x30,0x30,0x30};
    char send2Tibbo_M[36],send2Tibbo_S[36];
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        ss >> LD1 >> c >> LD2 >> c >> LD3 >> c >> LD4 >> c >> LD5 >> c >> LD6;
        LD1_Vec.push_back(LD1);
        LD2_Vec.push_back(LD2);
        LD3_Vec.push_back(LD3);
        LD4_Vec.push_back(LD4);
        LD5_Vec.push_back(LD5);
        LD6_Vec.push_back(LD6);
        data_size++;
    }
    std::cout<< "data size: " << (data_size) << std::endl;
    double target_hz {800};
    double target_msec {(1e+06/target_hz)};
    int cali_msec {(int) target_msec};
    int cali_cycle {1000};
    int ctr{0};

    double time_deviation_sum {0.0};
    double time_deviation_avg {0.0};
    double time_avg {0.0};

    while (ctr < data_size){

        auto start_time = Clock::now();

        std::this_thread::sleep_for(std::chrono::microseconds(cali_msec));
        // microsleep(cali_msec);
        // selectsleep(cali_msec);
        parse_format2Tibbo(LD1_char, LD1_Vec.at(ctr), 3, 6);
        parse_format2Tibbo(LD2_char, LD2_Vec.at(ctr), 3, 6);
        parse_format2Tibbo(LD3_char, LD3_Vec.at(ctr), 3, 6);
        parse_format2Tibbo(LD4_char, LD4_Vec.at(ctr), 3, 6);
        parse_format2Tibbo(LD5_char, LD5_Vec.at(ctr), 3, 6);
        parse_format2Tibbo(LD6_char, LD6_Vec.at(ctr), 3, 6);
        strcpy (send2Tibbo_M,LD1_char);
        strcat (send2Tibbo_M,Offset_empty);
        strcat (send2Tibbo_M,LD2_char);
        strcat (send2Tibbo_M,Offset_empty);
        strcat (send2Tibbo_M,LD3_char);
        strcat (send2Tibbo_M,Offset_empty);
        strcpy (send2Tibbo_S,LD4_char);
        strcat (send2Tibbo_S,Offset_empty);
        strcat (send2Tibbo_S,LD5_char);
        strcat (send2Tibbo_S,Offset_empty);
        strcat (send2Tibbo_S,LD6_char);
        strcat (send2Tibbo_S,Offset_empty);

        send(sock_M , send2Tibbo_M , strlen(send2Tibbo_M) , 0 );
        send(sock_S , send2Tibbo_S , strlen(send2Tibbo_S) , 0 );
        auto end_time = Clock::now();
        double dur_micro = std::chrono::duration<double, std::micro>(end_time - start_time).count();
        // std::cout <<"Time difference:"<< dur_micro <<" microseconds" << std::endl;
        time_avg += dur_micro;
        time_deviation_sum+=(dur_micro-target_msec);

        if (ctr % cali_cycle == cali_cycle-1){
            time_deviation_avg = time_deviation_sum / cali_cycle;
            // myfile << time_deviation_avg << std::endl;
            cali_msec = cali_msec - int (time_deviation_avg*0.5);
            time_avg = time_avg / cali_cycle;
            std::cout<< "avg_Hz: " << (1e+06/time_avg) << std::endl;
            time_deviation_sum = 0.0;
            time_deviation_avg = 0.0;
            time_avg = 0.0;

        }
        
        ctr++;
        if (ctr == data_size) ctr=0;

    }



    return 0;
}
