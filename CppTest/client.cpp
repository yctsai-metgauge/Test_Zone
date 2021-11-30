#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 1001
#include <iostream>
#include <chrono>
#include <thread>
#include <time.h>
#include <unistd.h>
// #include <fstream>
typedef std::chrono::high_resolution_clock Clock;

void selectsleep(int microseconds) {

    struct timeval timeout = {
        0,
        microseconds
    };

    struct timeval old_timeout = { timeout.tv_sec, timeout.tv_usec };

    while (true) {
        (void)select(0, NULL, NULL, NULL, &timeout);
        if (timeout.tv_sec<=0 && timeout.tv_usec<=0)
            break;
    }
}
void microsleep(int microseconds){
    struct timespec req;
    req.tv_sec = microseconds/1000000;
    req.tv_nsec = (microseconds%1000000) * 1000;
    nanosleep(&req,NULL);
}
int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    const char *hello = "0x00";
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "192.168.50.99", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    double target_hz {800};
    double target_msec {(1e+06/target_hz)};
    int cali_msec {(int) target_msec};
    int cali_cycle {1000};
    int ctr{0};

    // std::ofstream myfile;
    // myfile.open("selectsleep_diviation.csv");

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

            send(sock , hello , strlen(hello) , 0 );
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
        ctr++;
    }

    // myfile.close();
    
    return 0;
}