//
//  Heap.cpp
//  Created by Adnan Baysal on 23.12.2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "Heap.h"

int main(int argc,char **argv){// usage: "./a.out N" where N is an integer
    srand(atoi(argv[1]));
    Heap<int> H = Heap<int>(10);
    H.set_min_max(Heap<int>::MAXHEAP);// comment this line to make a min heap
    for (int i=0; i<10; i++) {
        H.addValue((rand()%10));
        H.print();
    }
    cout << "Heap size is : " << H.get_heap_size() << endl;
    for (int i=0; i<10; i++){
        cout << "Index of " << i << " : " << H.findIndex(i) << endl;
    }
    for(int i=0;i<40 && H.get_heap_size()>0;i++){
        cout << "Removing " << i%10 << " : " << H.remove(i%10) << endl;
        H.print();
    }
    return 0;
}
