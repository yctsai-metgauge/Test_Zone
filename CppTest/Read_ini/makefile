out: example.o dictionary.o iniparser.o     
	g++ example.o dictionary.o iniparser.o -o out.exe
example.o: example.cpp           
	g++ example.cpp -c          
dictionary.o : dictionary.c             
	g++ dictionary.c -c   
iniparser.o : iniparser.c             
	g++ iniparser.c -c          
clean:                 
	rm -rf example.o iniparser.o dictionary.o