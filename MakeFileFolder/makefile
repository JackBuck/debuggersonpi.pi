########################################################################
# Makefile for the raspberry pi 'renispace' project.
#
########################################################################

# Define repository location on the pi (~/renispace_source is a symbolic link on the pi)
REPO_DIR := /home/pi/renispace_source
#REPO_DIR := /home/pi/swDev/Source/Repos/renispace


# Define search path for source files
#SRC_DIR := $(REPO_DIR)/src
vpath %.cpp   $(REPO_DIR)/src


# Define source files
SRCS  =     CBlockReader.cpp      \
            CBlockReader_test.cpp \
            CGraph.cpp            \
            CGraph_test.cpp       \
            Challenges.cpp        \
            CInstruction_test.cpp \
            CMap.cpp              \
            CMap_test.cpp         \
            CMazeMapper.cpp       \
            CMazeMapper_test.cpp  \
            CParseCSV.cpp         \
            CParseCSV_test.cpp    \
            CSVRow.cpp            \
            DebugLog.cpp          \
            GoodsIn.cpp           \
            GoodsOut.cpp          \
            Instructions.cpp      \
            Main.cpp              \
            Manouvre.cpp          \
            Signals.cpp           \
            TestFunctions.cpp

# Define object files (by naming rule)
OBJS  = $(SRCS:.cpp=.o)

# Define include paths
INCLUDE_DIRS := -I/usr/include/opencv

# Define linker flags for libraries
LIBS := -lopencv_core -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_video -lopencv_highgui -lopencv_features2d

# # Implicit rule variables
# CXX := g++
# CXXFLAGS := -std=c++0x $(INCLUDE_DIRS) -O0 -g0 -Wall -c -fmessage-length=0

# All target
all: renispace

# Tool invocations
renispace: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o "renispace" $^ $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x $(INCLUDE_DIRS) -O0 -g0 -Wall -c -fmessage-length=0 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

# Other Targets
clean: cleanobj
	rm renispace

cleanobj:
	rm $(OBJS)

.PHONY: all clean cleanobj
