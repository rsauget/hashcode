INCLUDE=-I /opt/local/include
LIB=-L /opt/local/lib

.PHONY: clean

a.out: main.o io.o compute.o eval.o
	g++ -std=c++11 -o $@ $(LIB) $^

%.o: %.cpp
	g++ -std=c++11 $(INCLUDE) -c $<

clean:
	rm -f *.o a.out