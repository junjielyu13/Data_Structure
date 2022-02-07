
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

template<typename Comparable>
void selectionsort(vector<Comparable>& list);

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
    selectionsort(list);
    for(int num : list){
        cout << " " << num;
    }
    cout << endl;

}


template<typename Comparable>
void selectionsort(vector<Comparable>& list){
    for(int i=0; i<list.size()-1; i++){
        int min = i;
        for(int j=i+1; j<list.size(); j++){
            if(list[j] < list[min]){
                min = j;
            }
        }
        swap(list[i],list[min]);
    }
}