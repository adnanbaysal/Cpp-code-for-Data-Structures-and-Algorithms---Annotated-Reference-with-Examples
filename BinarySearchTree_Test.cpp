//
//  BinarySearchTree_Test.cpp
//  Created by Adnan Baysal on 22.12.2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "BinarySearchTree.h"

int main(int argc,char **argv){ // usage: "./a.out N" where N is an integer
    // testing BinarySearchTree.h
    BinarySearchTree<int> myBST;
    myBST.insert(2);
    myBST.print();
    myBST.insert(1);
    myBST.print();
    myBST.insert(3);
    myBST.print();
    myBST.remove(2);
    myBST.print();
    myBST.remove(1);
    myBST.print();
    myBST.remove(3);
    myBST.print();
    srand(atoi(argv[1]));
    for(int i=0;i<10;i++){
        int t = rand()%10;
        cout << t << endl;
        myBST.insert(t);
    }
    myBST.print();
    for(int i=0;i<10;i++){
        if(myBST.findNode(i)!=NULL) cout << i << " is in the tree" << endl;
        else cout << i << " is not in the tree" << endl;
    }
    cout << endl;
    myBST.breadthFirstPrint();
    cout << endl;
    cout << "Removing nodes..." << endl;
    for(int i=0;(i<40)&&(myBST.get_root()!=NULL);i++){
        cout << i%10 << " is" << (myBST.remove(i%10)?" ":" not ") << "removed" << endl;
        myBST.print();
    }
    return 0;
}
