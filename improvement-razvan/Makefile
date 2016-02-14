INCLUDE=-I /opt/local/include
LIB=-L /opt/local/lib # -lX11

.PHONY: clean all run

all: a.out 

a.out: main.o compute.o io.o # draw.o
	g++ -std=c++11 -o $@ $(LIB) $^

%.o: %.cpp
	g++ -O2 -std=c++11 $(INCLUDE) -c $<

clean:
	rm -f *.o a.out

src.zip: *.cpp *.h Makefile
	zip src *.cpp *.h Makefile