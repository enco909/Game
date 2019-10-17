#Compiler and compilation standard
CXX=g++ -std=c++17

#Compilation targets
SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp, %.o, $(SOURCES))
DEPENDS := $(patsubst %.cpp, %.d, $(SOURCES))
TARGET = Game

#Compilation flags
LDFLAGS = -lSDL2 -lSDL2_image
CXXFLAGS = -O2

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) $(CMDFLAGS) -o $(TARGET) 

-include $(DEPENDS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(CMDFLAGS) -MMD -MP -c $<

#Create fprofile data
profiling: CXXFLAGS += -fprofile-generate
profiling: TARGET = cpiwp_profiling
profiling: all

#Optimized with fprofile
optimized: CXXFLAGS += -fprofile-use -fprofile-correction
optimized: TARGET = cpiwp_optimized
optimized: all

#Run program with flags specified in RUNFLAGS
run: 
	./$(TARGET)

clean:
	$(RM) $(OBJECTS) $(DEPENDS) cpiwp*
