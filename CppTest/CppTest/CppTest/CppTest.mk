##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=CppTest
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=C:/Users/user/Documents/Test/CppTest/CppTest
ProjectPath            :=C:/Users/user/Documents/Test/CppTest/CppTest/CppTest
IntermediateDirectory  :=../build-$(ConfigurationName)/CppTest
OutDir                 :=../build-$(ConfigurationName)/CppTest
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=user
Date                   :=01/11/2021
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/Strawberry/c/bin/g++.exe
SharedObjectLinkerName :=C:/Strawberry/c/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=..\build-$(ConfigurationName)\bin\$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
RcCmpOptions           := 
RcCompilerName         :=C:/Strawberry/c/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/Strawberry/c/bin/ar.exe rcu
CXX      := C:/Strawberry/c/bin/g++.exe
CC       := C:/Strawberry/c/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/Strawberry/c/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=../build-$(ConfigurationName)/CppTest/main.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../build-$(ConfigurationName)/CppTest/.d $(Objects) 
	@if not exist "..\build-$(ConfigurationName)\CppTest" mkdir "..\build-$(ConfigurationName)\CppTest"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@if not exist "..\build-$(ConfigurationName)\CppTest" mkdir "..\build-$(ConfigurationName)\CppTest"
	@if not exist ""..\build-$(ConfigurationName)\bin"" mkdir ""..\build-$(ConfigurationName)\bin""

../build-$(ConfigurationName)/CppTest/.d:
	@if not exist "..\build-$(ConfigurationName)\CppTest" mkdir "..\build-$(ConfigurationName)\CppTest"

PreBuild:


##
## Objects
##
../build-$(ConfigurationName)/CppTest/main.cpp$(ObjectSuffix): main.cpp ../build-$(ConfigurationName)/CppTest/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/user/Documents/Test/CppTest/CppTest/CppTest/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/CppTest/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/CppTest/main.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/CppTest/main.cpp$(DependSuffix) -MM main.cpp

../build-$(ConfigurationName)/CppTest/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/CppTest/main.cpp$(PreprocessSuffix) main.cpp


-include ../build-$(ConfigurationName)/CppTest//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


