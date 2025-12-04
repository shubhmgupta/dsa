#include <iostream>
#include <ctime>
using namespace std;
int comparison=0;
int partition(int arr[], int low, int high) {
    int pivotIndex = low + rand() % (high - low + 1);
    int pivotValue = arr[pivotIndex]; 
    swap(arr[pivotIndex], arr[high]);
    int i = low - 1;
    for (int j = low; j < high; j++) {
        comparison++;
        if (arr[j] < pivotValue) { 
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[],int size, int low, int high){
    if (low < high) {
        int pivot = partition(arr, low, high);
        quickSort(arr, size, low, pivot - 1);
        quickSort(arr, size, pivot + 1, high);
    }
}


int main(){
    srand(time(0));
    int arr[]= {5, 2, 9, 1, 5, 6};
    int size = sizeof(arr)/sizeof(arr[0]);
    quickSort(arr, size, 0, size - 1);
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout<<endl;
    cout<<"comparison "<<comparison<<endl;
    return 0;
}