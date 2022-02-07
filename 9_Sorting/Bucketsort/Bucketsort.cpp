#include <cstdlib>
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

template<typename Comparable>
void bucketsort(vector<Comparable>& arr);

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
    bucketsort(list);
    for(int num : list){
        cout << " " << num;
    }
    cout << endl;
}

template<typename Comparable>
void bucketsort(vector<Comparable>& array){

    int size = array.size();
    vector<float> bucket[size];
    for(int i = 0; i<size; i++)  {          //put elements into different buckets
        bucket[int(size*array[i])].push_back(array[i]);
    }
    for(int i = 0; i<size; i++) {
        sort(bucket[i].begin(), bucket[i].end());       //sort individual vectors
    }
    int index = 0;
    for(int i = 0; i<size; i++) {
        while(!bucket[i].empty()) {
            array[index++] = *(bucket[i].begin());
            bucket[i].erase(bucket[i].begin());
        }
    }
}