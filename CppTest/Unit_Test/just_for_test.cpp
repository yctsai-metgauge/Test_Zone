#include <iostream>

#include <sys/time.h>

using namespace std;

int main(int argc ,char *argv[]){
   int n{19985};
   char hex_string[20];
   char result[4]={19985};
   sprintf(hex_string, "%X", n); //convert number to hex
//    result=char(n);
//    result[1]='0x'+hex_string[2]+hex_string[3];
   cout << hex_string;
}


