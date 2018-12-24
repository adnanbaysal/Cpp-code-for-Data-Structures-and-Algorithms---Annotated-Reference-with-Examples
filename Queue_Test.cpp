//
//  Queue.h
//  Created by Adnan Baysal on 23.12.2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "Queue.h"

int main(){
    Queue<int> Q;
    Q.Enqueue(3);
    Q.Enqueue(2);
    Q.Enqueue(1);
    Q.Enqueue(0);
    cout << "The queue: " << endl;
    for(int i=0;i<16;i++){
        int s = Q.Dequeue();
        cout << s << endl;
        Q.Enqueue(s);
    }
    for(int i=0;i<4;i++){
        int s = Q.Dequeue();
    }
    cout << "Q.isEmpty() = " << Q.isEmpty() << endl;
    return 0;
}
