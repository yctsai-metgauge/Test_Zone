out: RC_WC_Trigger.o dictionary.o iniparser.o     
	g++ RC_WC_Trigger.o dictionary.o iniparser.o -o out.exe
RC_WC_Trigger.o: RC_WC_Trigger.cpp           
	g++ -std=c++17 RC_WC_Trigger.cpp -c          
dictionary.o : dictionary.c             
	gcc dictionary.c -c   
iniparser.o : iniparser.c             
	gcc iniparser.c -c          
clean:                 
	rm -rf RC_WC_Trigger.o iniparser.o dictionary.o