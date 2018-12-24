//
//  Heap.h
//  Created by Adnan Baysal on 23.12.2018.
//

using namespace std;

template <typename T>
class Heap { // templated Heap data structure
    T *data; // pointer to the data
    unsigned heap_size = 0; // current number of elements in the heap
    unsigned max_size = 0; // maximum size of the heap
    bool IS_MIN_HEAP = true; // default is Min heap
public:
    static const bool MINHEAP = true; // use this to set min heap
    static const bool MAXHEAP = false;// use this to set max heap
    Heap(unsigned size){ // creates a Heap with at most size elements
        max_size = size;
        data = (T*)calloc(size,sizeof(T));
    }
    void addValue(T); // adds value to heap
    void Heapify(); // swap values to satisfy heap order
    void print(); // print array order
    int findIndex(T); // find the index of first occurence, -1 if not in the heap, optimized 
    bool remove(T); // remove the first occurence of value, and preserve heap structure
    void set_min_max(bool is_min){IS_MIN_HEAP = is_min;}; //sets the heap strategy - min or max
    unsigned get_heap_size(){return heap_size;};
};

template <typename T>
void Heap<T>::addValue(T value) {
    if(heap_size==max_size){
        cout << "Can't add value. Heap is full!" << endl;
        return;
    }
    data[heap_size++] = value; // add the data to the end
    Heapify(); // modify the array to satisfy the order
}

template <typename T>
void Heap<T>::Heapify() {
    int i = heap_size-1;
    // condition changes according to heap strategy (min or max)
    bool condition = IS_MIN_HEAP?(data[i]<data[(i-1)/2]):(data[i]>data[(i-1)/2]);
    while((i>0)&&condition){
        T temp = data[i];
        data[i] = data[(i-1)/2];
        data[(i-1)/2] = temp;
        i = (i-1)/2;
        condition = IS_MIN_HEAP?(data[i]<data[(i-1)/2]):(data[i]>data[(i-1)/2]);
    }
    return;
}

template <typename T>
void Heap<T>::print() {
    if(heap_size==0){
        cout << "Heap is empty!" << endl;
        return;
    }
    cout << "Heap : ";
    for(int i=0;i<heap_size;i++) cout << data[i] << " ";
    cout << endl;
}

template <typename T>
int Heap<T>::findIndex(T value) { // instead of contains() function, this is used
    if(heap_size==0) return -1;
    int start = 0, nodes = 1, end, count;
    while(start<heap_size){
        start = nodes-1;
        end = nodes + start;
        count = 0;
        while(start<heap_size && start<end){
            // select conditions based on heap strategy (min or max)
            bool cond1 = IS_MIN_HEAP?(value>data[(start-1)/2]):(value<data[(start-1)/2]);
            bool cond2 = IS_MIN_HEAP?(value<data[start]):(value>data[start]);
            if(value==data[start]) return start;
            else if(cond1 && cond2) count++;
            start++;
        }
        if(count==nodes) return -1;
        nodes *= 2;
    }
    return -1;
}

template <typename T>
bool Heap<T>::remove(T value) {
    int ind = findIndex(value);
    if(ind<0) return false;
    int left = 2*ind+1, right = 2*ind+2;
    heap_size--;
    data[ind] = data[heap_size];
    // select conditions based on heap strategy (min or max)
    bool condLeft = IS_MIN_HEAP?(data[ind]>data[left]):(data[ind]<data[left]);
    bool condRight = IS_MIN_HEAP?(data[ind]>data[right]):(data[ind]<data[right]);
    while((left<heap_size && condLeft)||(right<heap_size && condRight)){
        if(data[left]<data[right]){
            T temp = data[left];
            data[left] = data[ind];
            data[ind] = temp;
            ind = left;
        }
        else{
            T temp = data[right];
            data[right] = data[ind];
            data[ind] = temp;
            ind = right;
        }
        left = 2*ind+1;
        right = 2*ind+2;
        condLeft = IS_MIN_HEAP?(data[ind]>data[left]):(data[ind]<data[left]);
        condRight = IS_MIN_HEAP?(data[ind]>data[right]):(data[ind]<data[right]);
    }
    return true;
}
