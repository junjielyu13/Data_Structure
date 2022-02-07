
#include <cstdlib>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

template<typename Comparable>
void mergesort(vector<Comparable>& arr, int front, int end);

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
    mergesort(list, 0, list.size());
    for(int num : list){
        cout << " " << num;
    }
    cout << endl;

}

template<typename Comparable>
void merge(vector<Comparable>&arr, int front, int mid, int end){
    
    vector<Comparable> leftSubArray(arr.begin()+front, arr.begin()+mid+1);
    vector<Comparable> rightSubArray(arr.begin()+mid+1, arr.begin()+end+1);
    
    int leftIndex = 0;
    int rightIndex = 0;
    leftSubArray.insert(leftSubArray.end(), numeric_limits<int>::max());
    rightSubArray.insert(rightSubArray.end(), numeric_limits<int>::max());

    for(int i=front; i<=end; i++){
        if(leftSubArray[leftIndex]  < rightSubArray[rightIndex]){
            arr[i] = leftSubArray[leftIndex];
            leftIndex++;
        }else{
            arr[i] = rightSubArray[rightIndex];
            rightIndex++;
        }
    }

}

template<typename Comparable>
void mergesort(vector<Comparable>& arr, int front, int end){
    if(front >= end){
        return;
    }
    int mid = (front + end) / 2;
    mergesort(arr, front, mid);
    mergesort(arr, mid+1, end);
    merge(arr, front, mid, end);
}

