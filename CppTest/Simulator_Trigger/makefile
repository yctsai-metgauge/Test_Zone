out: client_read_n_send_mod.o dictionary.o iniparser.o     
	g++ client_read_n_send_mod.o dictionary.o iniparser.o -o out.exe
client_read_n_send_mod.o: client_read_n_send_mod.cpp           
	g++ -std=c++17 client_read_n_send_mod.cpp -c          
dictionary.o : dictionary.c             
	gcc dictionary.c -c   
iniparser.o : iniparser.c             
	gcc iniparser.c -c          
clean:                 
	rm -rf client_read_n_send_mod.o iniparser.o dictionary.o