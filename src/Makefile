SRC=main4C.C image.C sink.C source.C PNMreader.C PNMwriter.C filters.C logging.C  filter.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o performance_test

.C.o: $<
	g++  -g -I. -c $<

clean:
	rm *.o performance_test
