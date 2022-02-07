

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

template<typename Comparable>
void bubblesort(vector<Comparable>& list);

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
    bubblesort(list);
    for(int num : list){
        cout << " " << num;
    }
    cout << endl;

}

template<typename Comparable>
void bubblesort(vector<Comparable>& list){
    for(int i=0; i<list.size()-1; i++){
        for(int j=0; j<list.size()-1-i; j++){
            if(list[j] < list[j+1]){
                swap(list[j],list[j+1]);
            }
        }
    }
}


