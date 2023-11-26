#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <workflow/json_parser.h>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

void bubbleSort(vector<int> &arr, int n);
void selectionSort(vector<int> &arr, int n);
void insertionSort(vector<int> &arr, int n);

int partition(vector<int>&arr, int left, int right);
void quickSortHelper(vector<int>& arr, int left, int right);
void quickSort(vector<int>& arr);

int main(int argc, char* argv[]) {

    vector<int>  test1 = {4, 7, 1, 9, 12, 0, -2, 44};

    // bubbleSort(test1, test1.size());
    // selectionSort(test1, test1.size());
    // insertionSort(test1, test1.size());
    quickSort(test1);

    for (auto elem : test1) {
        cout << elem << " ";
    }
    cout << endl;

    return 0;
}


// 冒泡排序
void bubbleSort(vector<int> &arr, int n) {
    for (int j = 1; j < n; ++j) {
        for (int i = 0; i < n-j; ++i) {
            if (arr[i] > arr[i+1]) {
                int tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
            }
        }
    }
}

// 选择排序
void selectionSort(vector<int> &arr, int n) {
    for (int i = 0; i < n; ++i) {

        int minIndex = i;
        for (int j = i+1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            int tmp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = tmp;
        }
    }
}


// 插入排序
void insertionSort(vector<int> &arr, int n) {

    for (int i = 1; i < n; ++i) {
        int tmp = arr[i];
        int j = i-1;

        while (j >= 0 && arr[j] > tmp) {
            arr[j+1] = arr[j];
            --j;
        }

        arr[j+1] = tmp;
    }
}


// 快速排序 双分区
void quickSort(vector<int>& arr) {
    quickSortHelper(arr, 0, arr.size()-1);
}

void quickSortHelper(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int idx = partition(arr, left, right);
    quickSortHelper(arr, left, idx-1);
    quickSortHelper(arr, idx+1, right);
}

int partition(vector<int>& arr, int left, int right) {
    // 最左侧元素作为基准值
    int val = arr[left];

    int i = left;
    int j = right;
    while (i < j) {
        while (i < j && arr[j] >= val) {
            --j;
        }
        // i == j || arr[j] < val
        arr[i] = arr[j];

        while (i < j && arr[i] <= val) {
            ++i;
        }
        // i == j || arr[i] > val
        arr[j] = arr[i];
    }

    // i == j
    arr[i] = val;
    return i;
}

