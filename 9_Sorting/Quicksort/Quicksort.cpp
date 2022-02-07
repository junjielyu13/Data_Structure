
#include <cstdlib>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

template<typename Comparable>
void quicksort(vector<Comparable>& arr, int low, int high);

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
    quicksort(list, 0, list.size());
    for(int num : list){
        cout << " " << num;
    }
    cout << endl;

}

template<typename Comparable>
int paritition(vector<Comparable>& arr, int low, int high){
    int pivot = arr[low];
    while(low < high){
        while(low < high){
            --high;
        }
        arr[low] = arr[high];
        while (low < high && arr[low] <= pivot){
            ++low;
        }
        arr[high] = arr[low];
    }
    arr[low] = pivot;
    return low;
}



template<typename Comparable>
void quicksort(vector<Comparable>& arr, int low, int high){
    if(low < high){
        int pivot = paritition(arr,low,high);
        quicksort(arr, low, pivot-1);
        quicksort(arr, pivot+1, high);
    }
}