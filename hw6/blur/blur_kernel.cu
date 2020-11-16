#include <iostream>
#include <opencv2/opencv.hpp>


__global__ void Blur(int kernel_size, int rows, int cols, const double *data, double *data_result) {
    unsigned int xIdx = threadIdx.x + blockIdx.x * blockDim.x;
    unsigned int yIdx = threadIdx.y + blockIdx.y * blockDim.y;
    int b = kernel_size / 2;
    int n = kernel_size * kernel_size;

    double pix = 0;
    if (xIdx > b && yIdx > b && yIdx < (rows - b) && xIdx < (cols - b)) {
        for (int k = -b; k <= b; k++) {
            for (int l = -b; l <= b; l++) {
                pix += (1.0 / n) * data[(yIdx + l) * cols + (xIdx + k)];
            }
        }
    } else {
        pix = data[yIdx * cols + xIdx];
    }
    data_result[yIdx * cols + xIdx] = pix;
}

int main() {
    int kernel_size = 15;

    cv::Mat image = cv::imread("../dog.png", cv::IMREAD_GRAYSCALE);
    uchar *data_char = image.data;
    int rows = image.rows;
    int cols = image.cols;
    unsigned long N = rows * cols;
    double *h_data = new double[N];
    double *h_data_result = new double[N];
    double *d_data;
    double *d_data_result;

    cudaMalloc(&d_data, N * sizeof(double));
    cudaMalloc(&d_data_result, N * sizeof(double));


    for (int i = 0; i < N; i++) {
        h_data[i] = data_char[i] / 255.0;
    }

    const dim3 blockSize(8, 8, 1);
    const dim3 gridSize(cols / blockSize.x + 1, rows / blockSize.y + 1, 1);

    cudaMemcpy(d_data, h_data, N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_data_result, h_data_result, N * sizeof(double), cudaMemcpyHostToDevice);

    Blur<<<gridSize, blockSize>>>(kernel_size, rows, cols, d_data, d_data_result);

    cudaMemcpy(h_data_result, d_data_result, N * sizeof(double), cudaMemcpyDeviceToHost);

    for (int i = 0; i < N; i++) {
        h_data_result[i] = h_data_result[i] * 255.0;
    }

    cv::Mat imgGray(rows, cols, CV_64F, h_data_result);

    cv::imwrite("../dog_result.png", imgGray);

    delete [] h_data;
    delete [] h_data_result;
    cudaFree(d_data);
    cudaFree(d_data_result);

    return 0;
}
