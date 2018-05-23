#ifndef _MYALGORITHMS_H_
#define _MYALGORITHMS_H_

#include <vector>
#include <iostream>

using namespace std;

namespace MyAlgorithms
{
    void QuickSort(vector<int> &arr, int left, int right);
    void QuickMed(vector<int> &arr, int left, int right);
    int QuickPart(vector<int> &arr, int left, int right);
    void swap(vector<int> &arr, int swap1, int swap2);
    void MergeSort(vector<int> &a, int low, int high);
    void Merge(vector<int> &a, int low, int high);
    void HeapSort(vector<int> &a, int n);
    void percDown(vector<int> &arr, int i, int n);
    int leftChild(int i);
    void ShellSort(vector<int> &a, int n);

    //Matrix Multiplikation Column Major *
    void MatrixMul_ColMajor(vector<double> &A,
                            vector<double> &B,
                            vector<double> &C,
                            int n,
                            int numThreads);

    //Matrix Multiplikation Row Major
    void MatrixMul_RowMajor(vector<double> &A,
                            vector<double> &B,
                            vector<double> &C,
                            int n,
                            int numThreads);

    // helper functions

    double fRand(double fMin, double fMax);
    void randomizeMatrix(vector<double> &matrix, int n);   //fills vector<double> with n*n random double values
    void randomizeArray(vector<int> &array, int n);   //fills vector<int> with n random integer values

}
#endif