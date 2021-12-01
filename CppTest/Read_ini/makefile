out: simulator.o dictionary.o iniparser.o     
	g++ simulator.o dictionary.o iniparser.o -o out.exe
simulator.o: simulator.cpp           
	g++ -std=c++11 simulator.cpp -c          
dictionary.o : dictionary.c             
	gcc dictionary.c -c   
iniparser.o : iniparser.c             
	gcc iniparser.c -c          
clean:                 
	rm -rf simulator.o iniparser.o dictionary.o