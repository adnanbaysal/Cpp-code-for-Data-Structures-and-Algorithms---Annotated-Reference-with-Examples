//
//  BinarySearchTree.h
//  Created by Adnan Baysal on 22.12.2018.
//

using namespace std;

#include "Queue.h"

template <typename T>
struct BSTNode{
    // template struct for a single node in a binary search tree
    T nodeValue; // any type is valid for the values in nodes
    // a newly created struct will have null for the left and right child and parent
    BSTNode *leftChild = NULL;
    BSTNode *rightChild = NULL;
    BSTNode *parent = NULL;
};

template <typename T>
class BinarySearchTree{
    // template class for sigly linked lists
    unsigned nodeCount = 0; // total number of nodes in the tree
    unsigned counter; // counts the total nodes printed
    BSTNode<T> *root = NULL; // root node of the tree
    void insertNode(BSTNode<T>*,T); // recursive fnc used in insert()
    void printNode(BSTNode<T>*); // recursive fnc used in print()
    BSTNode<T> *findNodeRecursively(BSTNode<T>*,T); // recursive fnc used in findNode()
    BSTNode<T> *findParentRecursively(BSTNode<T>*,T); // recursive fnc used in findParent()
public:
    void insert(T); // inserts a value in the correct position
    void print(); // prints values in ascending order
    BSTNode<T> *findNode(T value); // returns true if the value is in the tree
    BSTNode<T> *findParent(T value); // this is not necessary when parent pointer is in the struct
    bool remove(T); // removes the first occurance of a value and rearranges the tree
    T findMax(); // finds the max (i.e. rightmost) value in the tree
    T findMin(); // finds the min (i.e. leftmost) value in the tree
    void breadthFirstPrint(); // prints the tree in breadth first manner
    BSTNode<T>* get_root() {return root;}; // returns the root of the tree
};

template <typename T>
void BinarySearchTree<T>::insert(T value){
    if(!root){ // if the root is empty, just create the a tree with only the root
        BSTNode<T> *n = new BSTNode<T>();
        n->nodeValue = value;
        root = n;
    }
    else insertNode(root,value); // if tree is not empty, branch to recursive function to insert
    nodeCount++;
}

template <typename T>
void BinarySearchTree<T>::insertNode(BSTNode<T> *curr,T value){
    if(value<(curr->nodeValue)){ // value will be inserted to left sub-tree
        if(curr->leftChild==NULL){ // if the leftChild is empty, create new
            BSTNode<T> *n = new BSTNode<T>();
            n->nodeValue = value;
            n->parent = curr;
            curr->leftChild = n;
        }
        else{ // if left is not empty, recursively search left sub-tree
            curr = curr->leftChild;
            insertNode(curr,value);
        }
    }
    else{ // reverse case of the above
        if(curr->rightChild==NULL){
            BSTNode<T> *n = new BSTNode<T>();
            n->nodeValue = value;
            n->parent = curr;
            curr->rightChild = n;
        }
        else{
            curr = curr->rightChild;
            insertNode(curr,value);
        }
    }
}

template <typename T>
void BinarySearchTree<T>::print() { // user interface for printing the tree
    if(root==NULL){ // the tree is empty
        cout << "The tree is empty!" << endl;
        return;
    }
    counter = 0;
    cout << "Root value: " << root->nodeValue << endl;
    cout << "Nodes:" << endl;
    printNode(root); // call the recursive printing function (hidden from user)
    cout << "Min node: " << findMin() << endl;
    cout << "Max node: " << findMax() << endl << endl; // an extra new line
}

template <typename T>
void BinarySearchTree<T>::printNode(BSTNode<T> *curr_root) { // prints the tree in ascending order
    if(curr_root->leftChild){
        printNode(curr_root->leftChild); // branch to left sub-tree
    }
    cout << "Node #" << ++counter << " : " << curr_root->nodeValue << endl; // print the current node
    if(curr_root->rightChild){
        printNode(curr_root->rightChild); // branch to right sub-tree
    }
}

template <typename T>
BSTNode<T> * BinarySearchTree<T>::findNode(T value){
    return findNodeRecursively(root,value); // call recursive fnc for non-empty tree
}

template <typename T>
BSTNode<T> * BinarySearchTree<T>::findNodeRecursively(BSTNode<T> *curr_root,T value){
    if(curr_root==NULL) return NULL;
    if((curr_root->nodeValue)==value) return curr_root;
    if(value<(curr_root->nodeValue))
        return findNodeRecursively(curr_root->leftChild,value); // value possibly in left
    else return findNodeRecursively(curr_root->rightChild,value); // value possibly in right
}

template <typename T>
BSTNode<T> * BinarySearchTree<T>::findParent(T value){
    if(value==root->nodeValue) return NULL;
    return findParentRecursively(root,value); // call recursive fnc for non-empty tree
}

template <typename T>
BSTNode<T> * BinarySearchTree<T>::findParentRecursively(BSTNode<T> *curr_root,T value){
    if(value<(curr_root->nodeValue)){
        if(curr_root->leftChild==NULL) return NULL;
        else if(curr_root->leftChild->nodeValue==value) return curr_root;
        else return findParentRecursively(curr_root->leftChild,value);
    }
    else{
        if(curr_root->rightChild==NULL) return NULL;
        else if(curr_root->rightChild->nodeValue==value) return curr_root;
        else return findParentRecursively(curr_root->rightChild,value);
    }
}

template <typename T>
bool BinarySearchTree<T>::remove(T value) {
    /* Cases:
     1. the value to remove is a leaf node; or
     2. the value to remove has a right subtree, but no left subtree; or
     3. the value to remove has a left subtree, but no right subtree; or
     4. the value to remove has both a left and right subtree in which case we
     promote the largest value in the left subtree.
     */
    BSTNode<T> *node2remove = findNode(value);
    if(node2remove==NULL) return false;
    if(nodeCount==1) root = NULL;
    else if((node2remove->leftChild==NULL)&&(node2remove->rightChild==NULL)){
        // case 1 --> leaf
        if(value<((node2remove->parent)->nodeValue))
            (node2remove->parent)->leftChild = NULL;
        else
            (node2remove->parent)->rightChild = NULL;
        delete node2remove; // clean-up removed node
    } else if((node2remove->leftChild==NULL)&&(node2remove->rightChild!=NULL)){
        // case 2 --> only right sub-tree
        if((node2remove->parent)==NULL){// this check is not done on the book --> contact Authors
            root = node2remove->rightChild;
            root->parent = NULL; // otherwise root may have a parent!
        }
        else{
            (node2remove->rightChild)->parent = (node2remove->parent);
            if((node2remove->nodeValue)<((node2remove->parent)->nodeValue))
                (node2remove->parent)->leftChild = node2remove->rightChild;
            else (node2remove->parent)->rightChild = node2remove->rightChild;
        }
        delete node2remove; // clean-up removed node
    } else if((node2remove->leftChild!=NULL)&&(node2remove->rightChild==NULL)){
        // case 3 --> only left sub-tree
        if((node2remove->parent)==NULL){ // this check is not done on the book --> contact Authors
            root = node2remove->leftChild;
            root->parent = NULL; // otherwise root may have a parent!
        }
        else{
            (node2remove->leftChild)->parent = (node2remove->parent);
            if((node2remove->nodeValue)<((node2remove->parent)->nodeValue))
                (node2remove->parent)->leftChild = node2remove->leftChild;
            else (node2remove->parent)->rightChild = node2remove->leftChild;
        }
        delete node2remove; // clean-up removed node
    } else { // case 4 --> both sub-trees
        BSTNode<T> *largestNodeOnLeft = node2remove->leftChild;
        bool right_baranched = false; // this is necessary when the left sub-tree has no right sub-tree
        while ((largestNodeOnLeft->rightChild)!=NULL){
            largestNodeOnLeft = largestNodeOnLeft->rightChild;
            right_baranched = true; // if while never entered, then right_baranched will remain false
        }
        // the below check is not done in the book --> e-mail to Authors
        if(!right_baranched) (largestNodeOnLeft->parent)->leftChild = NULL;
        else (largestNodeOnLeft->parent)->rightChild = NULL;
        node2remove->nodeValue = largestNodeOnLeft->nodeValue;
        delete largestNodeOnLeft; // clean-up removed node
    }
    nodeCount--;
    return true;
}

template <typename T>
T BinarySearchTree<T>::findMax(){
    if (root==NULL) {
        cout << "Tree is empty!" << endl;
        T t; // just a random value
        return t;
    }
    T mx = root->nodeValue;
    BSTNode<T> *curr = root;
    while(curr->rightChild!=NULL){
        curr = curr->rightChild;
        if((curr->nodeValue)>mx) mx = curr->nodeValue;
    }
    return mx;
}

template <typename T>
T BinarySearchTree<T>::findMin(){
    if (root==NULL) {
        cout << "Tree is empty!" << endl;
        T t; // just a random value
        return t;
    }
    T mn = root->nodeValue;
    BSTNode<T> *curr = root;
    while(curr->leftChild!=NULL){
        curr = curr->leftChild;
        if((curr->nodeValue)<mn) mn = curr->nodeValue;
    }
    return mn;
}

template <typename T>
void BinarySearchTree<T>::breadthFirstPrint() { // user interface for printing the tree
    if(root==NULL){ // the tree is empty
        cout << "The tree is empty!" << endl;
        return;
    }
    counter = 0;
    cout << "Breadth first Nodes:" << endl;
    BSTNode<T> *curr_root = root;
    Queue<BSTNode<T>*> Q;
    while(curr_root){
        cout << "Node #" << ++counter << " : " << curr_root->nodeValue << endl;
        if(curr_root->leftChild) Q.Enqueue(curr_root->leftChild);
        if(curr_root->rightChild) Q.Enqueue(curr_root->rightChild);
        if(!(Q.isEmpty())) curr_root = Q.Dequeue();
        else curr_root = NULL;
    }
    cout << "Min node: " << findMin() << endl;
    cout << "Max node: " << findMax() << endl << endl; // an extra new line
}
