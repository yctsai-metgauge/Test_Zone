#include <stdio.h>

#include <stdlib.h>

#include "iniparser.h"




int main(void)

{

    dictionary *ini;

    ini = iniparser_load("simulator.ini");//parser the file

    if(ini == NULL)

    {

        fprintf(stderr,"can not open %s","simulator.ini");

        exit(EXIT_FAILURE);

    }

    printf("dictionary obj:\n");

    iniparser_dump(ini,stderr);//save ini to stderr

    printf("\n%s:\n",iniparser_getsecname(ini,0));//get section name

    const char *tibbo_ip;
    tibbo_ip = iniparser_getstring(ini,"TCP_SETTING:ip","null");
    printf("ip : %s\n",tibbo_ip);
    printf("ip len : %d\n",strlen(tibbo_ip));
    

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

    iniparser_freedict(ini);//free dirctionary obj

    return 0;

}