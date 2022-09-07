#ifndef EF222E81_A3D8_4C32_92F4_98B7C377DAC5
#define EF222E81_A3D8_4C32_92F4_98B7C377DAC5

#include "MinHeapNode.h"

class MinHeap{
    public:
        MinHeap(unsigned capacity);
        void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b);
        void minHeapify(int idx);
        MinHeapNode* extractMin();
        void insertMinHeap(MinHeapNode* minHeapNode);
        void buildMinHeap();
        void createAndBuildMinHeap(char* data, int* freq, int s);
        bool isSizeOne();

    private:
        unsigned size;
        unsigned capacity;
        MinHeapNode** array;
        char* values;
        char* encodedValues;
};

MinHeap::MinHeap(unsigned capacity) 
{
    this->size = 0;
    this->capacity = capacity;
    this->array = new MinHeapNode* [capacity * sizeof(MinHeapNode*)];
}

void MinHeap::swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) 
{
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void MinHeap::minHeapify(int idx) 
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if(left < this->size && array[left]->getFrequency() < this->array[smallest]->getFrequency()){
        smallest = left;
    }

    if(right < this->size && array[right]->getFrequency() < this->array[smallest]->getFrequency()){
        smallest = right;
    }

    if(smallest != idx){
        swapMinHeapNode(&this->array[smallest], &this->array[idx]);
        minHeapify(smallest);
    }
}

MinHeapNode* MinHeap::extractMin() 
{
    MinHeapNode* temp = this->array[0];
    this->array[0] = this->array[this->size - 1];

    this->size--;
    minHeapify(0);

    return temp;

}

void MinHeap::insertMinHeap(MinHeapNode* minHeapNode)
{
    int i = this->size++;

    while (i &&
        minHeapNode->getFrequency()
        < this->array[(i - 1) / 2]->getFrequency())
    {
        this->array[i] = this->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    this->array[i] = minHeapNode;
}

bool MinHeap::isSizeOne() 
{
    return (this->size == 1);
}

void MinHeap::buildMinHeap()
{
    int n = this->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
    {
        minHeapify(i);
    }

}

void MinHeap::createAndBuildMinHeap(char* data, int* freq, int s)
{
    // 1

    for (int i = 0; i < s; ++i)
    {
        this->array[i] = new MinHeapNode(data[i], freq[i]);
    }

    this->size = s;
    buildMinHeap();
}


#endif /* EF222E81_A3D8_4C32_92F4_98B7C377DAC5 */
