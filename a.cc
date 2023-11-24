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

int main(int argc, char* argv[]) {

    vector<int>  test1 = {4, 7, 1, 9, 12, 0, -2, 44};

    // bubbleSort(test1, test1.size());
    // selectionSort(test1, test1.size());
    insertionSort(test1, test1.size());

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
