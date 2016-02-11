INCLUDE=-I /opt/local/include
LIB=-L /opt/local/lib # -lX11

.PHONY: clean

a.out: main.o compute.o io.o eval.o # draw.o
	g++ -std=c++11 -o $@ $(LIB) $^

%.o: %.cpp
	g++ -std=c++11 $(INCLUDE) -c $<

clean:
	rm -f *.o a.out