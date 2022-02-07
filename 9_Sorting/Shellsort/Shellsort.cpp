

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

template<typename Comparable>
void shellsort(vector<Comparable>& list);

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
    shellsort(list);
    for(int num : list){
        cout << " " << num;
    }
    cout << endl;

}


template<typename Comparable>
void shellsort(vector<Comparable>& list){
    for(int gap=list.size()/2; gap>0; gap/=2){
        for(int i=gap; i<list.size(); i++){
            Comparable tmp = list[i];
            int j = i;
            for(; j>=gap && tmp<list[j-gap]; j-= gap){
                list[j] = list[j-gap];
            }
            list[j] = tmp;
        }
    }
}
