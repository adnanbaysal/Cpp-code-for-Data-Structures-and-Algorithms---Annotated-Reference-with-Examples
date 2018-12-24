//
//  SinglyLinkedList_Test.cpp
//  Created by Adnan Baysal on 21.12.2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "SinglyLinkedList.h"

int main(){
    SinglyLinkedList<int> mySLL;
    for (int i=0; i<4; i++) { // add some values to the list
        mySLL.addValue(i*i);
        cout << mySLL.get_nodeCount() << " nodes in the list" << endl;
    }
    mySLL.print();
    for (int i=0; i<10; i++) { // check if the values are in the list
        cout << "List contains " << i << " : " << mySLL.contains(i) << endl;
    }
    for (int i=0; i<4; i++) { // remove values from the list
        cout << "removing " << i*i*i << " : " << mySLL.remove(i*i*i) << endl;
        cout << mySLL.get_nodeCount() << " nodes remaining" << endl;
        mySLL.print();
    }
    mySLL.remove(9);
    cout << mySLL.get_nodeCount() << " nodes remaining" << endl;
    mySLL.print();
    mySLL.remove(4);
    cout << mySLL.get_nodeCount() << " nodes remaining" << endl;
    mySLL.print();
    return 0;
}
