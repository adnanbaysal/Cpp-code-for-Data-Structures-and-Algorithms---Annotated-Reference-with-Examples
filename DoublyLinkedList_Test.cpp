//
//  DoublyLinkedList_Test.cpp
//  Created by Adnan Baysal on 22.12.2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "DoublyLinkedList.h"

int main(){ // testing DoublyLinkedList.h
    DoublyLinkedList<int> myDLL;
    for (int i=0; i<4; i++) {
        myDLL.addValue(i*i);
        cout << "List has " << myDLL.get_nodeCount() << " elements" << endl;
    }
    //myDLL.print();
    myDLL.reversePrint();
    for (int i=0; i<10; i++) {
        cout << "List contains " << i << " : " << myDLL.contains(i) << endl;
    }
    for (int i=0; i<4; i++) {
        cout << "removing " << i*i*i << " : " << myDLL.remove(i*i*i)
             << " (" << myDLL.get_nodeCount() << " nodes remaining)" << endl;
        //myDLL.print();
        myDLL.reversePrint();
    }
    myDLL.remove(9);
    cout << myDLL.get_nodeCount() << " nodes remaining" << endl;
    //myDLL.print();
    myDLL.reversePrint();
    myDLL.remove(4);
    cout << myDLL.get_nodeCount() << " nodes remaining" << endl;
    //myDLL.print();
    myDLL.reversePrint();
    return 0;
}
