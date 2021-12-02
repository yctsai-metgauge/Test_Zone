# all: one two three
# one:
# 	touch one
# two:
# 	touch two
# three:
# 	touch three
# clean:
# 	rm -f one two three

# ==================use $@ 工作目標檔名==================#

# all: one two three
# one two three:
# 	echo $@
# clean:
# 	rm -r one two three

# ===================$^：代表所有的依賴檔案(prerequisites)=============================#
# ===================$?：代表示比目標還要新的依賴檔案列表。以空格分隔======================#

# hey: one two
# 	# Outputs "hey", since this is the first target
# 	echo $@
# 	# Outputs all prerequisites newer than the target
# 	echo $?
# 	# Outputs all prerequisites
# 	echo $^
# 	touch hey
# one:
# 	touch one
# two:
# 	touch two
# clean:
# 	rm -f hey one two

#------------------------------------------------------------------------------------

# hey: one two
# 	echo $^
# 	echo "---------------"
# 	echo $?
# 	echo "---------------"
# 	touch hey
# one:
# 	touch one
# two:
# 	touch two
# clean:
# 	rm -f hey one two

#============ https://makefiletutorial.com/ ============================================#

# files = file1 file2
# some_file: $(files)
# 	echo "Look at this variable: " $(files)
# 	touch some_file

# file1:
# 	touch file1
# file2:
# 	touch file2

# clean:
# 	rm -f file1 file2 some_file

#--------------------------------------------------
all: f1.o f2.o

f1.o f2.o:
	echo $@

