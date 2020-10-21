CXX = arm-himix200-linux-g++
BIN = bin/centerface
SRCS = src/main.cpp
OBJS = $(SRCS:.cpp=.o)
CFLAGS = -O3 -std=c++11 -fopenmp -Iinclude -Iinclude/opencv -Iinclude/hisi 
LIBFLAGS = -fopenmp -lstdc++ -Llib -lcenterface -Llib/hisi -lnnie -lmpi -lVoiceEngine -ldnvqe -lsecurec -lupvqe -Llib/opencv -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_video -lopencv_videoio

all: $(BIN)

$(OBJS):

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

$(BIN): $(OBJS)
	$(CXX) $^ $(LIBFLAGS) -o $@ 

clean:
	rm -f $(BIN) ./src/*.o

