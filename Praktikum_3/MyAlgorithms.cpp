#include "MyAlgorithms.h"
#include <omp.h>

namespace MyAlgorithms
{
    void QuickSort(vector<int> &arr, int left, int right)
    {

    }

    void MergeSort(vector<int> &a, vector<int> &b, int low, int high)
    {

    }

    void HeapSort(vector<int> &a, int n)
    {

    }

    void ShellSort(vector<int> &a, int n)
    {

    }

    //Matrix Multiplication Column Major
    void MatrixMul_ColMajor(vector<double> &A,
                            vector<double> &B,
                            vector<double> &C,
                            int n,
                            int numThreads)
    {
        //lda, ldb, ldc are leading dimensions of matrices A,B and C
        int lda = n;
        int ldb = n;
        int ldc = n;
        double s = 0.0;

        for (int i=0; i<n ; i++)
        {
            for (int j=0; j<n ; j++)
            {
                s = 0.0;
                for (int k=0; k<n; k++)
                {
                    s = s + A[i+k*lda] * B[k+j*ldb];
                }
                C[i+j*ldc]=s;
            }
        }
    }

    //Matrix Multiplication Row Major
    void MatrixMul_RowMajor(vector<double> &A,
                            vector<double> &B,
                            vector<double> &C,
                            int n,
                            int numThreads)
    {


    }

    // helper functions

    double fRand(double fMin, double fMax)
    {
        double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

    void randomizeMatrix(vector<double> &matrix, int n)
    {
        matrix.resize(n*n);
        int i;
        for (i=0;i<matrix.size();i++)
            matrix[i]=fRand(-1000,1000);
    }

    void randomizeArray(vector<int> &array, int n)
    {
        array.resize(n);

        for(int i=0;i<array.size();i++)
            array[i]=rand() % 1000000;
    }
}
