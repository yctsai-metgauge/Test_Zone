#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <chrono>
#include <thread>
#include <time.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include "iniparser.h"
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

    num = num*pow(10.0,max_digit_after_dot);

    char sprintf_format[]{"%06.0f"};

    if (target_digit_num != 6){
        char target_digit_num_char[1];
        sprintf(target_digit_num_char,"%d",target_digit_num);
        *(sprintf_format+2) = *target_digit_num_char;
    }
    
    sprintf(outStr,sprintf_format,num);

}

int main()
{
    // --------------read ini----------------
    dictionary *ini;

    ini = iniparser_load("simulator.ini");//parser the file

    if(ini == NULL)

    {

        fprintf(stderr,"can not open %s","simulator.ini");

        exit(EXIT_FAILURE);

    }

    int ATON_TYPE{0};
    ATON_TYPE = iniparser_getint(ini,"MODEL_TYPE:ATON_TYPE",-1);
    // 0 for ROD, 1 for BAR, 2 for Wire
    printf("ATON_TYPE : %d\n",ATON_TYPE);

    
    // tibbo_ip = iniparser_getstring(ini,"TCP_SETTING:ip","null");
    // std::cout << tibbo_ip << '\n';
    const char *RC_master_tibbo_ip, *RC_slave_tibbo_ip;
    const char *WC_tibbo_ip;
    if (ATON_TYPE == 0)
    {
        RC_master_tibbo_ip = "192.168.50.99";
        printf("RC master tibbo ip : %s\n",RC_master_tibbo_ip);
        RC_slave_tibbo_ip = "192.168.50.100";
        printf("RC slave tibbo ip : %s\n",RC_slave_tibbo_ip);
    }else if (ATON_TYPE == 2)
    {  
        WC_tibbo_ip = "192.168.50.88";
        printf("WC tibbo ip : %s\n",WC_tibbo_ip);
    }
     
    int port{0};
    port = iniparser_getint(ini,"TCP_SETTING:port",-1);
    printf("port : %d\n",port);

    double target_hz{0.0};
    target_hz = iniparser_getdouble(ini,"TRIGGER_SETTING:target_hz",-1);
    printf("target_hz : %.1f\n",target_hz);

    int cali_cycle{0};
    cali_cycle = iniparser_getint(ini,"TRIGGER_SETTING:cali_cycle",-1);
    printf("cali_cycle : %d\n",cali_cycle);

    const char *file_path;
    file_path = iniparser_getstring(ini,"FILE_SETTING:file_path","null");
    printf("file_path : %s\n",file_path);
    
    // ----------end read ini----------------

    // ---------------socket-----------------
    int sock_M = 0, sock_S = 0, valread;
    struct sockaddr_in serv_addr_M, serv_addr_S;

    char buffer[1024] = {0};

    if (ATON_TYPE == 0)
    {
        if ((sock_M = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket(Master) creation error \n");
            return -1;
        }
        if ((sock_S = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n RC Socket(Slave) creation error \n");
            return -1;
        }
        serv_addr_M.sin_family = AF_INET;
        serv_addr_M.sin_port = htons(port);
        serv_addr_S.sin_family = AF_INET;
        serv_addr_S.sin_port = htons(port);
        if(inet_pton(AF_INET, RC_master_tibbo_ip, &serv_addr_M.sin_addr)<=0) 
        {
            printf("\n Invalid RC Master address/ Address not supported \n");
            return -1;
        }
        if(inet_pton(AF_INET, RC_slave_tibbo_ip, &serv_addr_S.sin_addr)<=0) 
        {
            printf("\n Invalid RC Slave address/ Address not supported \n");
            return -1;
        }
        if (connect(sock_M, (struct sockaddr *)&serv_addr_M, sizeof(serv_addr_M)) < 0)
        {
            printf("\n RC Master Connection Failed \n");
            return -1;
        }
        if (connect(sock_S, (struct sockaddr *)&serv_addr_S, sizeof(serv_addr_S)) < 0)
        {
            printf("\n RC Slave Connection Failed \n");
            return -1;
        }
    }else if (ATON_TYPE == 2)
    {

        if ((sock_M = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n WC Socket creation error \n");
            return -1;
        }
        serv_addr_M.sin_family = AF_INET;
        serv_addr_M.sin_port = htons(port);
        if(inet_pton(AF_INET, WC_tibbo_ip, &serv_addr_M.sin_addr)<=0) 
        {
            printf("\n WC Invalid address/ Address not supported \n");
            return -1;
        }
        if (connect(sock_M, (struct sockaddr *)&serv_addr_M, sizeof(serv_addr_M)) < 0)
        {
            printf("\n WC Connection Failed \n");
            return -1;
        }
    }
    // --------------end socket----------------

    // --------------read csv------------------
    char c; // to eat the commas

    float LD1, LD2, LD3, LD4, LD5, LD6;
    std::vector<float> LD1_Vec, LD2_Vec, LD3_Vec, LD4_Vec, LD5_Vec, LD6_Vec;
    int data_size{0};
    std::ifstream file(file_path);
    std::string line;
    char LD1_char[6],LD2_char[6],LD3_char[6],LD4_char[6],LD5_char[6],LD6_char[6],Offset_empty[6]={0x30,0x30,0x30,0x30,0x30,0x30};
    char send2Tibbo_M[36],send2Tibbo_S[36];
    char send2Tibbo_WC[12];

    if (ATON_TYPE==0){
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
    }else if (ATON_TYPE==2)
    {
        while (std::getline(file, line)) {
        std::istringstream ss(line);
        ss >> LD1 >> c >> LD2;
        LD1_Vec.push_back(LD1);
        LD2_Vec.push_back(LD2);
        data_size++;
    }
    }
    
    
    std::cout<< "data size: " << (data_size) << std::endl;

    
    // ----------end read csv------------------


    double target_msec {(1e+06/target_hz)};
    int cali_msec {(int) target_msec};
    int ctr{0};

    double time_deviation_sum {0.0};
    double time_deviation_avg {0.0};
    double time_avg {0.0};    
    auto start_time = Clock::now();
    auto end_time = Clock::now();
    double dur_micro{0.0};
    while (ctr < data_size){

        start_time = Clock::now();

        std::this_thread::sleep_for(std::chrono::microseconds(cali_msec));
        // microsleep(cali_msec);
        // selectsleep(cali_msec);
        if (ATON_TYPE==0){
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
        }else if (ATON_TYPE==2){
            parse_format2Tibbo(LD1_char, LD1_Vec.at(ctr), 3, 6);
            parse_format2Tibbo(LD2_char, LD2_Vec.at(ctr), 3, 6);
            strcpy (send2Tibbo_WC,LD1_char);
            strcat (send2Tibbo_WC,LD2_char);
            send(sock_M , send2Tibbo_WC , strlen(send2Tibbo_WC) , 0 );
        }
                

        end_time = Clock::now();
        dur_micro = std::chrono::duration<double, std::micro>(end_time - start_time).count();
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

    iniparser_freedict(ini);//free dirctionary obj
    return 0;
}
