CC=g++
CFLAGS=-c
FLAG=
SOURCES=matrix.cpp vector_col.cpp vector_row.cpp dot_product.cpp dot_product_strassen.cpp
MAIN=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
STATIC_LIB=matrix_lib.a
EXECUTABLE=matmul
STD=c++17

all:
	$(CC) $(CFLAGS) $(SOURCES) $(FLAG)
	ar rc $(STATIC_LIB) $(OBJECTS) # собираем библиотеку для статической линковки
	g++ -std=$(STD) $(MAIN) $(STATIC_LIB) -o $(EXECUTABLE) # линкуем эту библиотеку к main.cpp
	rm *.o *.a

clean:
	rm -rf *.o $(EXECUTABLE)

run:
	./$(EXECUTABLE)