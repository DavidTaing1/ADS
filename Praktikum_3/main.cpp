#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <omp.h>
#include "MyAlgorithms.h"

using namespace std;

int main(int argc, char** argv)
{

    // file streams
    ofstream benchmark;

    benchmark.open("/home/david/Dokumente/ADS/Praktikum_3/test.txt", ios::out | ios::app);

    //benchmark settings

    double dtime;
    int n_start = 2;
    int n_step = 1;
    int n_end = 1800;
    int numThreads = 4; //only for matrix multiplication

    //data structures for sorting algorithms (int) and matrices (double)

    vector<int> array,temp_array;
    vector<double> A,B,C;

    //benchmark main loop (run only ONE algorithm at a time) *

    for (int n = n_start; n<n_end; n+=n_step)
    {
        cout << "n: " << n << endl;

        //init data structure with random values

        //sorting algorithms
        //MyAlgorithms::randomizeArray(array,n);

        //matrix multiplication
        if(n > 800) { n_step = 11; }
        MyAlgorithms::randomizeMatrix(A,n);
        MyAlgorithms::randomizeMatrix(B,n);
        C.resize(n*n);

        //  start clock
        dtime = omp_get_wtime();

        //  execute algorithm
        //MyAlgorithms::QuickSort(array, 0, array.size()-1);
        //MyAlgorithms::ShellSort(array, array.size());
        //MyAlgorithms::MergeSort(array, 0, array.size()-1);
        //MyAlgorithms::HeapSort(array, array.size());

        // matrix
        //MyAlgorithms::MatrixMul_ColMajor(A, B, C, n, numThreads);
        MyAlgorithms::MatrixMul_RowMajor(A, B, C, n, numThreads);

        //  stop clock
        dtime = omp_get_wtime() - dtime;

        //  write results to file
        benchmark << n << "\t" << setprecision(10) << scientific << dtime << endl;

    }

    //  close file handles

    benchmark.close();
}
