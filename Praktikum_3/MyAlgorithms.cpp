#include "MyAlgorithms.h"
#include <omp.h>

namespace MyAlgorithms
{
    void QuickSort(vector<int> &arr, int left, int right)
    {
        if(left < right)
        {
            int q = QuickPart(arr, left, right);
            QuickSort(arr, left, q - 1);
            QuickSort(arr, q + 1, right);
        }
    }

    void QuickMed(vector<int> &arr, int left, int right)
    {
        int center = (left + right) * 0.5;
        if(arr[center] < arr[left])
        {
            swap(arr, center, left);
        }
        if(arr[right] < arr[left])
        {
            swap(arr, right, left);
        }
        if(arr[right] > arr[center])
        {
            swap(arr, center, right);
        }
    }

    int QuickPart(vector<int> &arr, int left, int right)
    {
        QuickMed(arr, left, right);
        int x = arr[right];
        int i = left - 1;
        for(int j = left; j < right; j++)
        {
            if(arr[j] <= x)
            {
                i++;
                swap(arr, i, j);
            }
        }
        swap(arr, i + 1, right);
        return i + 1;
    }

    void swap(vector<int> &arr, int swap1, int swap2)
    {
        int tmp = arr[swap1];
        arr[swap1] = arr[swap2];
        arr[swap2] = tmp;
    }

    void MergeSort(vector<int> &arr, int low, int high)
    {
        if(low < high)
        {
            int q = low + (high - low) * 0.5;
            MergeSort(arr, low, q);
            MergeSort(arr, q + 1, high);
            Merge(arr, low, high);
        }
    }

    void Merge(vector<int> &arr, int low, int high)
    {
        int med = (low + high) * 0.5;
        int i, j, k = low;
        int n1 = med - low + 1;
        int n2 =  high - med;
        int l[n1], r[n2];

        for (i = 0; i < n1; i++) l[i] = arr[low + i];
        for (j = 0; j < n2; j++) r[j] = arr[med + 1 + j];
        i = 0;
        j = 0;
        while (i < n1 && j < n2)
        {
            if (l[i] <= r[j])
            {
                arr[k] = l[i];
                i++;
            }
            else
            {
                arr[k] = r[j];
                j++;
            }
            k++;
        }
        while (i < n1)
        {
            arr[k] = l[i];
            i++;
            k++;
        }
        while (j < n2)
        {
            arr[k] = r[j];
            j++;
            k++;
        }
    }

    void HeapSort(vector<int> &arr, int n)
    {
        for(int i = n * 0.5 - 1; i >= 0; i--) percDown(arr, i, n);
        for(int j = n - 1; j > 0; j--)
        {
            swap(arr, 0, j);
            percDown(arr, 0, j);
        }
    }

    void percDown(vector<int> &arr, int i, int n)
    {
        int child = leftChild(i);
        while(child < n)
        {
            if(child + 1 < n && arr[child] < arr[child + 1]) child++;
            if(arr[child] > arr[i])
            {
                swap(arr, i, child);
            }
            i = child;
            child = leftChild(i);
        }
    }

    int leftChild(int i)
    {
        return 2 * i + 1;
    }

    void ShellSort(vector<int> &a, int n)
    {
        int j, tmp, gap = 1;
        while(gap < n)
        {
            if(2 * gap + 1 > n) break;
            gap = 2 * gap + 1;
        }
        while(gap > 0)
        {
            for(int i = gap; i < n; i++)
            {
                tmp = a[i];
                j = i;
                for(; j >= gap && tmp < a[j - gap]; j -= gap) a[j] = a[j - gap];
                a[j] = tmp;
            }
            gap = gap * 0.5;
        }
    }

    //Matrix Multiplication Column Major
    void MatrixMul_ColMajor(vector<double> &A,
                            vector<double> &B,
                            vector<double> &C,
                            int n,
                            int numThreads)
    {
        omp_set_num_threads(numThreads);
        //lda, ldb, ldc are leading dimensions of matrices A,B and C
        int lda = n;
        int ldb = n;
        int ldc = n;
        double s = 0.0;

        #pragma omp parallel for
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
        omp_set_num_threads(numThreads);
        //lda, ldb, ldc are leading dimensions of matrices A,B and C
        int lda = n;
        int ldb = n;
        int ldc = n;
        double s = 0.0;

        #pragma omp parallel for
        for (int i=0; i<n ; i++)
        {
            for (int j=0; j<n ; j++)
            {
                s = 0.0;
                for (int k=0; k<n; k++)
                {
                    s = s + A[i*lda + k] * B[j+k*ldb];
                }
                C[j+i*ldc]=s;
            }
        }
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
