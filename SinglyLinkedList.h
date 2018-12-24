//
//  SinglyLinkedList.h
//  
//
//  Created by Adnan Baysal on 21.12.2018.
//

using namespace std;

template <typename T>
struct SLLNode{
    // template struct for a single node in a simply linked list
    T nodeValue; // any type is valid for the values in nodes
    // a newly created struct will have null for the next node
    SLLNode *nextNode = NULL;
};

template <typename T>
class SinglyLinkedList{
    // template class for sigly linked lists
    SLLNode<T> *head = NULL; // beginning of the list
    SLLNode<T> *tail = NULL; // end of the list
    unsigned nodeCount = 0; // total number of nodes in the list
public:
    void addValue(T); // adds an new node at the tail with a value
    void print(); // prints the entire list
    bool contains(T); // returns true if the value is in the list
    bool remove(T); // removes the value and returns true if value exist
    unsigned get_nodeCount() { return nodeCount;}; // getter for nodeCount
};

template <typename T> void SinglyLinkedList<T>::addValue(T value){
    SLLNode<T> *newNode = new SLLNode<T>();
    newNode->nodeValue = value;// create a new node with value
    if(head==NULL){ // if the list is empty
        head = newNode;
        tail = newNode;
    }
    else{ // list is not empty, insert to the end
        (tail)->nextNode = newNode;
        tail = newNode;
    }
    nodeCount++;
}

template <typename T> void SinglyLinkedList<T>::print(){
    if(nodeCount==0){ // empty list
        cout << "List is empty!" << endl;
    }
    else{
        SLLNode<T> *curr = head;
        int ctr = 0;
        while(curr){
            cout << "Node #" << ++ctr << " : " << curr->nodeValue << endl;
            curr = curr->nextNode;
        }
    }
}

template <typename T> bool SinglyLinkedList<T>::contains(T value){
    SLLNode<T> *curr = head;
    while(curr&&((curr->nodeValue)!=value)) curr = curr->nextNode;
    if(curr) return true; // if the value is in the list then the pointer is not NULL
    return false;
}

template <typename T> bool SinglyLinkedList<T>::remove(T value){
    /*
     1. the list is empty; or
     2. the node to remove is the only node in the linked list; or
     3. we are removing the head node; or
     4. we are removing the tail node; or
     5. the node to remove is somewhere in between the head and tail; or
     6. the item to remove doesn't exist in the linked list
    */
    if (head==NULL) return false; // case 1
    SLLNode<T> *curr = head;
    if (curr->nodeValue==value){
        if (curr==tail){// case 2
            head = NULL;
            tail = NULL;
        }
        else head = curr->nextNode; // case 3
        nodeCount--;
        return true;
    }
    while((curr->nextNode)&&((curr->nextNode->nodeValue)!=value)) curr = curr->nextNode;
    if(curr->nextNode){
        if((curr->nextNode)==tail) tail = curr; // case 4
        curr->nextNode = curr->nextNode->nextNode; // case 5
        nodeCount--;
        return true;
    }
    return false; // case 6
}
