#ifndef BFE4D5AD_1277_4333_B833_47920874BC0F
#define BFE4D5AD_1277_4333_B833_47920874BC0F

#include <iostream>
#include <math.h>

using namespace std;

/*Função auxiliar:*/

template <typename T>
void change_places(T *x, T *y){
    T temp = *y;
    *y = *x;
    *x = temp;
}

/*Implementação do Quicksort:*/

template <typename T>
int medianThree(T *array, int a, int b, int c) {
    if ((array[a] > array[b]) ^ (array[a] > array[c])) 
        return a;
    else if ((array[b] < array[a]) ^ (array[b] < array[c])) 
        return b;
    else
        return c;
}

template<typename T>
int partition(T *array, int lo, int hi) 
{
    int m = (lo + hi) / 2;
    int i = lo-1;
    int j = hi+1;
    T pivot = array[m];
    while(true)
    {
        do
        {
            j =  j-1;
        
        } while(array[j] > pivot);
        do
        {
            i =  i+1;
        
        } while(array[i] < pivot);
        if(i < j)
        {
            T tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
        } 
        else return j; 
    } 
}

template<typename T>
void quicksort_range(T *array, int lo, int hi) {
    if (lo < hi) {
        int p = partition(array, lo, hi);
        quicksort_range(array, lo, p);
        quicksort_range(array, p + 1, hi);
    }
}

template<typename T>
void quickort(T *array, int n) {
    quicksort_range(array, 0, n-1);
}


/*Fim da implementação do Quicksort*/

/*Implementação do Heapsort:*/

/* int parent(int i){
    return ((i-1)/2);
}

int sonOfLeft(int i){
    return (2*i+1);
}

int sonOfRight(int i){
    return (2*i+2);
} */

template <typename T>
void maxHeapify(T *array, int i, int n) 
{
    int l = 2*i + 1;
    int r = 2*i + 2;
    int m = i;

    if(l < n && array[l] > array[m]){
        m = l;
    }

    if(r < n && array[r] > array[m]){
        m = r;
    }

    if(m != i){
        change_places(&array[i], &array[m]);
        maxHeapify(array, m, n);
    }
}

template <typename T>
void buildHeapMax(T *array, int n){
    for(int i = n/2 - 1; i >= 0; i--){
        maxHeapify(array, i, n);
    }
}

template <typename T>
void heapSort(T *array, int n){

    buildHeapMax(array, n);
    
    for (int i = n-1; i > 0; i--)
    {
        change_places(&array[0], &array[i]);
        maxHeapify(array, 0, i);
    }
}

/*Fim da implementação do Heapsort*/

/*Implementação do TimSort:*/

template <typename T>
void insertionS(T *array, int left, int right){
    for (int i = left + 1; i <= right; i++){
        int aux = array[i];

        int j = i - 1;

        while (array[j] > aux && j >= left){
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = aux;
    }
}

template <typename T>
void merge(T *array, int left, int middle, int right){

    int lenghtFirst = middle - left + 1;
    int lenghtSecond = right - middle;

    T auxLeft[lenghtFirst], auxRight[lenghtSecond]; 

    int i, j, k;

    i = j = k = 0;

    for (i = 0; i < lenghtFirst; i++){
        auxLeft[i] = array[left + i];
    }

    for (i = 0; i < lenghtSecond; i++){
        auxRight[i] = array[middle + 1 + i];
    }
    
    

    i = 0, j = 0, k = left;

    while(i < lenghtFirst && j < lenghtSecond){
        if(auxLeft[i] <= auxRight[j]){
            array[k] = auxLeft[i];
            i++;
        } else{
            array[k] = auxRight[j];
            j++;
        }
        k++;
    }

    while(i < lenghtFirst){
        array[k] = auxLeft[i];
        k++;
        i++;
    }

    while(j < lenghtSecond){
        array[k] = auxRight[j];
        k++;
        j++;
    }
}

template <typename T>
void timSort(T *array, int n){
    int TAM = 50;

    for(int i = 0; i < n; i+=TAM){
        insertionS(array, i, min((i+TAM-1), (n-1)));
    }

    for(int size = TAM; size < n; size = 2*size){
        for(int left = 0; left < n; left += 2*size){
            int middle = left + size - 1;
            int right = min((left + 2*size - 1), (n - 1));

            if(middle < right) {
                merge(array, left, middle, right);
            }
        }
    }
}

/*Fim da implementação do TimSort*/

#endif /* BFE4D5AD_1277_4333_B833_47920874BC0F */
