#include <iostream>
#include <chrono>
#include <cstring>
#include <string>
#include "matrix.h"
#include "vector_row.h"
#include "vector_col.h"
#include "dot_product.h"
#include "dot_product_strassen.h"


int main(int argc, char *argv[]) {

    int n = 512;

    if (argc > 1 && argv[1]) {
        n = std::stoi(argv[1]);
    }

    Matrix m1 = Matrix(n, n);
    Matrix m2 = Matrix(n, n);

    Matrix m(0, 0);

    auto start = std::chrono::high_resolution_clock::now();
    std::string dot_product_type = "simple";
    if (argc > 2 && strcmp(argv[2], "strassen") == 0) {
        dot_product_type = "Strassen";
//        std::cout << "Strassen dot product, n=" << n << std::endl;
        m = DotProductStrassen(m1, m2);
    } else {
//        std::cout << "Just dot product, n=" << n << std::endl;
        m = DotProduct(m1, m2);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Duration: " << duration.count() << " ms | n=" << n <<
              " | Dot product type: " << dot_product_type << std::endl;

    return 0;
}