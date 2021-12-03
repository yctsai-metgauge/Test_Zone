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



    char c; // to eat the commas

    float LD1, LD2, LD3, LD4, LD5, LD6;
    std::vector<float> LD1_Vec, LD2_Vec, LD3_Vec, LD4_Vec, LD5_Vec, LD6_Vec;
    int data_size{0};
    std::ifstream file("test_RC.csv");
    std::string line, word;
    std::vector<std::string> row;
    char LD1_char[6],LD2_char[6],LD3_char[6],LD4_char[6],LD5_char[6],LD6_char[6],Offset_empty[6]={0x30,0x30,0x30,0x30,0x30,0x30};
    char send2Tibbo_M[36],send2Tibbo_S[36];


    if(file.is_open())
	{
		while(getline(file, line))
		{
            // std::cout << line << std::endl;
        	while(getline(file, word, ';')){
                row.push_back(word);
                std::cout << word << std::endl;
            }
            for (auto it = row.begin(); it != row.end(); ++it) std::cout << ' ' << *it; 
            row.clear();
		}
	}



    // while (std::getline(file, line)) {
    //     std::istringstream ss(line);
    //     ss >> LD1 >> c >> LD2 >> c >> LD3 >> c >> LD4 >> c >> LD5 >> c >> LD6;
    //     LD1_Vec.push_back(LD1);
    //     LD2_Vec.push_back(LD2);
    //     LD3_Vec.push_back(LD3);
    //     LD4_Vec.push_back(LD4);
    //     LD5_Vec.push_back(LD5);
    //     LD6_Vec.push_back(LD6);
    //     data_size++;
    // }


    file.close();

    

    // for (int i = 0; i < 100; i++){
    //     parse_format2Tibbo(LD1_char, LD1_Vec.at(i%(data_size)), 3, 6);
    //     parse_format2Tibbo(LD2_char, LD2_Vec.at(i%(data_size)), 3, 6);
    //     parse_format2Tibbo(LD3_char, LD3_Vec.at(i%(data_size)), 3, 6);
    //     parse_format2Tibbo(LD4_char, LD4_Vec.at(i%(data_size)), 3, 6);
    //     parse_format2Tibbo(LD5_char, LD5_Vec.at(i%(data_size)), 3, 6);
    //     parse_format2Tibbo(LD6_char, LD6_Vec.at(i%(data_size)), 3, 6);
    //     strcpy (send2Tibbo_M,LD1_char);
    //     strcat (send2Tibbo_M,Offset_empty);
    //     strcat (send2Tibbo_M,LD2_char);
    //     strcat (send2Tibbo_M,Offset_empty);
    //     strcat (send2Tibbo_M,LD3_char);
    //     strcat (send2Tibbo_M,Offset_empty);
    //     strcpy (send2Tibbo_S,LD4_char);
    //     strcat (send2Tibbo_S,Offset_empty);
    //     strcat (send2Tibbo_S,LD5_char);
    //     strcat (send2Tibbo_S,Offset_empty);
    //     strcat (send2Tibbo_S,LD6_char);
    //     strcat (send2Tibbo_S,Offset_empty);
            
    //     std::cout << send2Tibbo_M << std::endl;


    //  }



    return 0;
}
