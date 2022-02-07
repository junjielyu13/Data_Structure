

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

template<typename Comparable>
void insertionSort(vector<Comparable>& list);

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
    insertionSort(list);
    for(int num : list){
        cout << " " << num;
    }
    cout << endl;

}

//Algorithm. insertion sort
template<typename Comparable>
void insertionSort(vector<Comparable>& list){

    int j;
    for(int i=0; i<list.size(); i++){
        Comparable tmp = list[i];
        for(j=i; j>0 && tmp<list[j-1]; j--){
            list[j] = list[j-1];
        }
        list[j] = tmp; 
    }
}

//STL Implementation of InsertionSort
template<typename Iterator>
void insertionSort(const Iterator& begin, const Iterator& end){
    if(begin != end){
        insertionSortHelp(begin,end,*begin);
    }

}

template<typename Iterator, typename Object>
void insertionSortHelp(const Iterator& begin, const Iterator& end, const Object& obj){
    insertionSort(begin,end,less<Object>());
}

template<typename Iterator, typename Comparator>
void insertionSort(const Iterator& begin, const Iterator& end, Comparator lessThan){
    if(begin != end){
        insertionSort(begin,end,*begin);
    }
}

template<typename Iterator, typename Comparator, typename Object>
void insertionSort(const Iterator& begin, const Iterator& end, Comparator lessThan, const Object& obj){

    Iterator j;
    for(Iterator p=begin+1; p!=end; ++p){
        Object tmp = *p;
        for(j=p; j!=begin && lessThan(tmp, *(j-1)); --j){
            *j = *(j-1);
        }
        *j = tmp;
    }
}

