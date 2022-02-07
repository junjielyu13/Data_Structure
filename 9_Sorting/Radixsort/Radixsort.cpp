#include <cstdlib>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

template<typename Comparable>
void radixsort(vector<Comparable>& arr);

int main(int argc, char** argv) {

    vector<int> list;
    for(int i=0; i<20; i++){
        list.push_back(rand());
    }

    cout << "original: ";
    for(int num : list){
        cout << num << " ";
    }
    cout << endl;

    cout << "sorting: ";
    radixsort(list);
    for(int num : list){
        cout << " " << num;
    }
    cout << endl;
}

template<typename Comparable>
int getMax(vector<Comparable>& arr, int n){
    int mx = arr[0];
    for (int i = 1; i < n; i++){
        if (arr[i] > mx){
            mx = arr[i];
        }
    }
    return mx;
}
 
template<typename Comparable>
void countSort(vector<Comparable>& arr, int n, int exp){
    int output[n]; // output array
    int i, count[10] = { 0 };
 
    for (i = 0; i < n; i++){
        count[(arr[i] / exp) % 10]++;
    }
    for (i = 1; i < 10; i++){
        count[i] += count[i - 1];
    }
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
 
    for (i = 0; i < n; i++){
        arr[i] = output[i];
    }
}
 
template<typename Comparable>
void radixsort(vector<Comparable>& arr){

    int n = arr.size();
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10){
        countSort(arr, n, exp);
    }
}