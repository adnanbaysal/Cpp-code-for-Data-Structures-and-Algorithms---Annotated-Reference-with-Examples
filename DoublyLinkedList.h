//
//  DoublyLinkedList.h
//  Created by Adnan Baysal on 22.12.2018.
//

using namespace std;

template <typename T>
struct DLLNode{
    // template struct for a single node in a simply linked list
    T nodeValue; // any type is valid for the values in nodes
    // a newly created struct will have null for the prev and next node
    DLLNode *prevNode = NULL;
    DLLNode *nextNode = NULL;
};

template <typename T>
class DoublyLinkedList{
    // template class for sigly linked lists
    DLLNode<T> *head = NULL; // beginning of the list
    DLLNode<T> *tail = NULL; // end of the list
    unsigned nodeCount = 0; // number of nodes in the list
public:
    void addValue(T); // adds an new node at the tail with a value
    void print(); // prints the entire list
    void reversePrint(); // prints the entire list in reverse order
    bool contains(T); // returns true if the value is in the list
    bool remove(T); // removes the value and returns true if value exist
    unsigned get_nodeCount(){return nodeCount;}; // getter for nodeCount
};

template <typename T> void DoublyLinkedList<T>::addValue(T value){
    DLLNode<T> *newNode = new DLLNode<T>();
    newNode->nodeValue = value;
    if(head==NULL){ // list is empty
        head = newNode;
        tail = newNode;
    }
    else{ // list is not empty, add value to the tail
        newNode->prevNode = tail;
        (tail)->nextNode = newNode;
        tail = newNode;
    }
    nodeCount++;
}

template <typename T> void DoublyLinkedList<T>::print(){
    if(head==NULL){ // empty list
        cout << "List is empty!" << endl;
    }
    else{ // prints values in order --> values should be 'printable' by cout
        DLLNode<T> *curr = head;
        int ctr = 0;
        while(curr){
            cout << "Node #" << ++ctr << " : " << curr->nodeValue << endl;
            curr = curr->nextNode;
        }
    }
}

template <typename T> void DoublyLinkedList<T>::reversePrint(){ // reverse printing the values
    if(head==NULL){
        cout << "List is empty!" << endl;
    }
    else{
        DLLNode<T> *curr = tail;
        int ctr = 0;
        while(curr){
            cout << "Node #" << --ctr << " : " << curr->nodeValue << endl;
            curr = curr->prevNode;
        }
    }
}

template <typename T> bool DoublyLinkedList<T>::contains(T value){
    DLLNode<T> *curr = head;
    while(curr&&((curr->nodeValue)!=value)) curr = curr->nextNode;
    if(curr) return true; // if the value is in the list, curr is not NULL
    return false;
}

template <typename T> bool DoublyLinkedList<T>::remove(T value){
    /*
     1. the list is empty; or
     2. the node to remove is the only node in the linked list; or
     3. we are removing the head node; or
     4. we are removing the tail node; or
     5. the node to remove is somewhere in between the head and tail; or
     6. the item to remove doesn't exist in the linked list
    */
    if (head==NULL) return false; // case 1
    if (head->nodeValue==value){
        if (head==tail){// case 2
            head = NULL;
            tail = NULL;
        }
        else{
            head = head->nextNode; // case 3
            head->prevNode = NULL;
        }
        nodeCount--;
        return true;
    }
    DLLNode<T> *curr = head;
    while(curr&&((curr->nodeValue)!=value)) curr = curr->nextNode;
    if(curr==tail){// case 4
        tail = tail->prevNode;
        tail->nextNode = NULL;
        nodeCount--;
        return true;
    }
    else if(curr){ // case 5
        curr->prevNode->nextNode = curr->nextNode;
        curr->nextNode->prevNode = curr->prevNode;
        nodeCount--;
        return true;
    }
    return false; // case 6
}
