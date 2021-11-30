#include <stdio.h>

#include <stdlib.h>

#include "iniparser.h"




int main(void)

{

    dictionary *ini;

    int n = 0;

    const char *str;

    ini = iniparser_load("example.ini");//parser the file

    if(ini == NULL)

    {

        fprintf(stderr,"can not open %s","example.ini");

        exit(EXIT_FAILURE);

    }

    printf("dictionary obj:\n");

    iniparser_dump(ini,stderr);//save ini to stderr

    printf("\n%s:\n",iniparser_getsecname(ini,0));//get section name

    n = iniparser_getint(ini,"tcp:port",-1);

    printf("port : %d\n",n);

    str = iniparser_getstring(ini,"tcp:ip","null");

    printf("ip : %s\n",str);

    iniparser_freedict(ini);//free dirctionary obj

    return 0;

}