#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; 
    int i = low - 1; 

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

int randomizedPartition(int arr[], int low, int high) {
    int randomPivot = low + rand() % (high - low + 1);
    swap(arr[randomPivot], arr[high]); 
    return partition(arr, low, high);
}


int randomizedSelect(int arr[], int low, int high, int i) {
    if (low == high) 
        return arr[low];

    int q = randomizedPartition(arr, low, high);
    int k = q - low + 1;  

    if (i == k) 
        return arr[q]; 
    else if (i < k) 
        return randomizedSelect(arr, low, q - 1, i);
    else 
        return randomizedSelect(arr, q + 1, high, i - k);
}

int main() {
    srand(time(0));
    int arr[] = {12, 3, 5, 7, 4, 19, 26};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 4; 

    cout << i << "rd smallest element is " 
         << randomizedSelect(arr, 0, n - 1, i) << endl;

    return 0;
}
