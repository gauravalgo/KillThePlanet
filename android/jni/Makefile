CXX=g++
C_FLAGS=-c -Wall -std=c++11 -DPLATFORM_LINUX -DGL_GLEXT_PROTOTYPES -pthread -fpic -I/opt/local/include -O3
L_FLAGS= -L/opt/local/lib -lX11 -lGL -lpthread

TARGET=./../../Asteroids
SOURCES=main.cpp engine.cpp engineLinux.cpp aux.cpp render.cpp game.cpp
HEADERS=minimath.h utils.h engine.h render.h game.h

OBJECTS=$(SOURCES:.cpp=.o)
.SUFFIXES: .cpp .o


all: $(SOURCES) $(HEADERS) $(TARGET) Makefile

$(TARGET): $(OBJECTS) Makefile
	$(CXX) $(OBJECTS) $(L_FLAGS) -o $@
	
.cpp.o: $(SOURCES) 
	$(CXX) $(C_FLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET)
	rm -f $(OBJECTS)