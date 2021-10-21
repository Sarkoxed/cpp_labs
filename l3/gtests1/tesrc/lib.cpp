#include "lib.hpp"

using namespace vector;

void heapify(int arr[], int n, int i){
    int lar = i;
    int l = 2*i+1;
    int r = 2*i+2;

    if(l < n && arr[l] > arr[lar]){
        lar = l;
    }
    if(r < n && arr[r] > arr[lar]){
        lar = r;
    }
    if(lar != i){
        int tmp = arr[i];
        arr[i] = arr[lar];
        arr[lar] = tmp;
        heapify(arr, n, lar);
    }
}

void heapsort(int z[],  int n){
    for(int i = 0; i <= n / 2; i++){
        heapify(z, n, n / 2 - i); 
    }
    for(int i = 0; i < n; i++){
        int tmp = z[0], k = n - i - 1;
        z[0] = z[k];
        z[k] = tmp;
        heapify(z, k, 0);
    } 
}



