# out: simulator.o dictionary.o iniparser.o     
# 	g++ simulator.o dictionary.o iniparser.o -o out.exe
# simulator.o: simulator.cpp           
# 	g++ -std=c++11 simulator.cpp -c          
# dictionary.o : dictionary.c             
# 	gcc dictionary.c -c   
# iniparser.o : iniparser.c             
# 	gcc iniparser.c -c          
# clean:                 
# 	rm -rf simulator.o iniparser.o dictionary.o

# all: one two three
# one two three:
# 	echo $@
# clean:
# 	rm -r one two three

hey: one two
	echo $^
	echo "---------------"
	echo $?
	echo "---------------"
	touch hey
one:
	touch one
two:
	touch two
clean:
	rm -f hey one two

# https://iter01.com/600516.html