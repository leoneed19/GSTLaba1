#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

//  nvcc Cuda.cu -o Cuda; ./Cuda
// ssh -p 9003 root@samos.dozen.mephi.ru
// gst2019
struct MyStruct {
    int m;
    int n;
    int *res;
};


long current_timestamp() {
    struct timeval te;
    gettimeofday(&te, NULL);
    long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
    return milliseconds;
}


struct MyStruct readFromFile() {
    int s = 0, k = 0;
    int iterations = 0;
    struct MyStruct result;
    FILE *myFile;
    myFile = fopen("input.txt", "r");
    int *Res;

    while ((fscanf(myFile, "%d", &s) != EOF)) {
        if (!myFile)
            break;
        k += 1;
    }

    Res = (int *) malloc(k * sizeof(int));
    rewind(myFile);
    for (int i = 0; i < k; i++) {
        if (iterations == 0) {
            fscanf(myFile, "%d", &result.m);
            iterations++;
        }
        if (iterations == 1) {
            fscanf(myFile, "%d", &result.n);
            iterations++;
        }
        fscanf(myFile, "%i", &Res[i]);
    }
    printf("\n");
    result.res = Res;
    fclose(myFile);
    return result;
}


__global__ void process(long grid_size, long treads, int *data_set, int M, int *res) {

    long next_column = 0;

    while ((next_column + blockIdx.x * treads + threadIdx.x) <= M) {
        int *r = &(data_set[M*(next_column + blockIdx.x * treads + threadIdx.x)]);
        int summ = 0;
        for (int c = 0; c < M; c++) {
            summ = summ + r[c];
        }
        res[next_column + blockIdx.x * treads + threadIdx.x] = summ / M;
        next_column += grid_size * treads;
    }
}


int main(int argc, char *argv[]) {
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    int *data_set, *dev_data_set, size, res_size, grid_size, treads_size, M = 0;
    grid_size = atoi(argv[2]);
    treads_size = atoi(argv[3]);

    struct MyStruct result = readFromFile();

    M = result.m;
    res_size = M * sizeof(int);
    printf("M = %i\n", M);

    int *dev_res = (int *) malloc(M * sizeof(int));
    int *host_res = (int *) malloc(M * sizeof(int));

    data_set = result.res;
    for (int i=0; i < M; i++){
        printf("%i\t",data_set[i]);
    }
    printf("READ DATA STARTS....\n");
    size = M * M * sizeof(int);
    printf("Size %li\n", size);

    // Чтение данных из файла
    printf("READ DATA ENDS....\n");

    printf("res_size = %i\n", res_size);
    printf("size = %i\n", size);
    cudaMalloc(&dev_data_set, size);
    cudaMalloc(&dev_res, res_size);

    // копируем ввод на device
    cudaEventRecord(start);
    cudaMemcpy(dev_data_set, data_set, size, cudaMemcpyHostToDevice);
    cudaEventRecord(start);
    process << < grid_size, treads_size >> > (grid_size, treads_size, dev_data_set, M, dev_res);

    cudaEventRecord(stop);
    // копируем результат работы device обратно на host - копию c
    cudaMemcpy(data_set, dev_data_set, size, cudaMemcpyDeviceToHost);
    cudaMemcpy(host_res, dev_res, res_size, cudaMemcpyDeviceToHost);
    cudaEventSynchronize(stop);
    cudaFree(dev_data_set);
    cudaFree(dev_res);
    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    for (int i = 0; i < 10; i++) {
        printf("%i\n", host_res[i]);

    }

    printf("time = %f\n", milliseconds);
    return 0;
}