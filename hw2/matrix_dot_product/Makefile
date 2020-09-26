all:
	g++ -c matrix.cpp
	g++ -c vector_col.cpp
	g++ -c vector_row.cpp
	g++ -c dot_product.cpp
	g++ -c dot_product_strassen.cpp
	ar rc matrix_lib.a matrix.o vector_col.o vector_row.o dot_product.o dot_product_strassen.o
	g++ -std=c++17 main.cpp matrix_lib.a -o matmul
	rm *.o *.a

flag_O3:
	g++ -c matrix.cpp -O3
	g++ -c vector_col.cpp -O3
	g++ -c vector_row.cpp -O3
	g++ -c dot_product.cpp -O3
	g++ -c dot_product_strassen.cpp -O3
	ar rc matrix_lib.a matrix.o vector_col.o vector_row.o dot_product.o dot_product_strassen.o
	g++ -std=c++17 main.cpp matrix_lib.a -o matmul
	rm *.o *.a

flag_g:
	g++ -c matrix.cpp -g
	g++ -c vector_col.cpp -g
	g++ -c vector_row.cpp -g
	g++ -c dot_product.cpp -g
	g++ -c dot_product_strassen.cpp -g
	ar rc matrix_lib.a matrix.o vector_col.o vector_row.o dot_product.o dot_product_strassen.o
	g++ -std=c++17 main.cpp matrix_lib.a -o matmul
	rm *.o *.a

clean:
	rm -f *.o *.a matmul
run:
	./matmul

