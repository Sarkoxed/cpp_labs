#include "vect.hpp"

using namespace vector;

void heapify(int arr[], int n, int i){
    int largest = i;
    int l = 2*i+1;
    int r = 2*i+2;

    if(l < n && arr[l] > arr[largest]){
        largest = l;
    }
    if(r < n && arr[r] > arr[largest]){
        largest = r;
    }
    if(largest != i){
        int tmp = arr[i];
        arr[i]=arr[largest];
        arr[largest] = tmp;
        heapify(arr, n, largest);
    }
}

void heapsort(int z[],  size_t n){
    for(size_t i = 0; i < n; i++){
        heapify(z, n, i); 
    }
    for(size_t i = n - 1; i >= 0; i--){
        int tmp = z[0];
        z[0] = z[i];
        z[i] = tmp;
        heapify(z, i, 0);
    } 
}



