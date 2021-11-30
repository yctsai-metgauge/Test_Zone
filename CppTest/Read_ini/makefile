out: simulator.o dictionary.o iniparser.o     
	g++ example.o dictionary.o iniparser.o -o out.exe
simulator.o: simulator.cpp           
	g++ simulator.cpp -c          
dictionary.o : dictionary.c             
	g++ dictionary.c -c   
iniparser.o : iniparser.c             
	g++ iniparser.c -c          
clean:                 
	rm -rf simulator.o iniparser.o dictionary.o