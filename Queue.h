//
//  Queue.h
//  Created by Adnan Baysal on 23.12.2018.
//

template <typename T>
struct QueueNode {
    T nodeValue;
    QueueNode *nextNode = NULL;
};

template <typename T>
class Queue {
    QueueNode<T> *head = NULL;
    QueueNode<T> *tail = NULL;
    unsigned nodeCount = 0;
public:
    void Enqueue(T); // pushes new_node to queue
    T Dequeue(); // pops the front value from queue
    bool isEmpty() {if(nodeCount==0) return true; else return false;};
};

template <typename T>
void Queue<T>::Enqueue(T new_node) {
    QueueNode<T> *new_qnode = new QueueNode<T>();
    new_qnode->nodeValue = new_node;
    if(head==NULL){
        head = new_qnode;
        tail = head;
    }
    else{
        tail->nextNode = new_qnode;
        tail = new_qnode;
    }
    nodeCount++;
}

template <typename T>
T Queue<T>::Dequeue() {
    if(head==NULL) return NULL;
    T node = head->nodeValue;
    head = head->nextNode;
    nodeCount--;
    return node;
}

