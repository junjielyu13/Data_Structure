#include <cstdlib>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

template<typename Comparable>
void heapsort(vector<Comparable>& arr);

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
    heapsort(list);
    for(int num : list){
        cout << " " << num;
    }
    cout << endl;

}

template<typename Comparable>
void max_heapify(vector<Comparable>& arr, int start, int end){
    int dad = start;
    int son = dad*2+1;

    while(son <= end){
        if(son+1 <= end && arr[son] < arr[son+1]){
            son++;
        }
        if(arr[dad] > arr[son]){
            return;
        }else{
            swap(arr[dad],arr[son]);
            dad = son;
            son = dad*2+1;
        }

    }
}



template<typename Comparable>
void heapsort(vector<Comparable>& arr){
    for(int i=arr.size()/2-1; i>=0; i--){
        max_heapify(arr,i,arr.size()-1);
    }
    for(int i=arr.size()-1; i>0; i--){
        swap(arr[0],arr[i]);
        max_heapify(arr,0,i-1);
    }

}