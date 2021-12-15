#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
// #define PORT 1002
#include <chrono>
#include <thread>
#include <time.h>
#include <unistd.h>
#include <bits/stdc++.h>
// #include <fstream>
typedef std::chrono::high_resolution_clock Clock;


int main(int argc, char *argv[])
{
    const char *tibbo_ip;
    tibbo_ip = argv[1];
    int port;
    port = atoi(argv[2]);




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
    serv_addr.sin_port = htons(port);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, tibbo_ip, &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    unsigned long long ctr{0};
    int cali_cycle{100};
    double time_deviation_avg {0.0};
    double time_avg {0.0};    
    auto start_time = Clock::now();
    auto end_time = Clock::now();
    double dur_micro{0.0};
    while(true){
        start_time = Clock::now();
        valread = read( sock , buffer, 1024);
        end_time = Clock::now();
        dur_micro = std::chrono::duration<double, std::micro>(end_time - start_time).count();
        time_avg += dur_micro;

        if (ctr % cali_cycle == cali_cycle-1){

            time_avg = time_avg / cali_cycle;
            std::cout<< "avg_Hz: " << (1e+06/time_avg) << std::endl;
            time_deviation_avg = 0.0;
            time_avg = 0.0;
        }
        ctr++;

    }

    // valread = read( sock , buffer, 1024);
    // std::cout<<buffer<<std::endl;
    // printf("%s\n",buffer );



    return 0;
}
