#ifndef BFE4D5AD_1277_4333_B833_47920874BC0F
#define BFE4D5AD_1277_4333_B833_47920874BC0F

#include <iostream>
#include <math.h>

using namespace std;

/*Função auxiliar:*/

template <typename T>
void change_places(T *x, T *y, int &keyMoviment)
{
    T temp = *y;
    *y = *x;
    *x = temp;
    keyMoviment = keyMoviment + 1;
}

/*Implementação do Quicksort:*/

template <typename T>
int medianThree(T *array, int a, int b, int c)
{
    if ((array[a] > array[b]) ^ (array[a] > array[c]))
        return a;
    else if ((array[b] < array[a]) ^ (array[b] < array[c]))
        return b;
    else
        return c;
}

template<typename T>
int partition(T *array, int lo, int hi, int &keyComparation, int &keyMovement)
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
            keyComparation = keyComparation +1;

        }
        while(array[j] > pivot);
        do
        {
            i =  i+1;
            keyComparation = keyComparation +1;

        }
        while(array[i] < pivot);
        keyComparation = keyComparation +1;
        if(i < j)
        {
            keyMovement = keyMovement + 1;
            T tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
        }
        else return j;
    }
}

template<typename T>
void quicksort_range(T *array, int lo, int hi, int &keyComparation, int &keyMovement)
{
    if (lo < hi)
    {
        keyComparation = keyComparation + 1;
        int p = partition(array, lo, hi, keyComparation, keyMovement);
        quicksort_range(array, lo, p, keyComparation, keyMovement);
        quicksort_range(array, p + 1, hi, keyComparation, keyMovement);
    }
}

template<typename T>
void quicksortFollowers(T *array, int n, int &keyComparation, int &keyMovement)
{
    quicksort_range(array, 0, n-1, keyComparation, keyMovement);
}


/*Fim da implementação do Quicksort*/

/*Implementação do Heapsort:*/

int parent(int i)
{
    return ((i-1)/2);
}

int sonOfLeft(int i)
{
    return (2*i+1);
}

int sonOfRight(int i)
{
    return (2*i+2);
}

template <typename T>
void maxHeapify(T *array, int i, int n, int &keyComparation, int &keyMoviment)
{
    int l = 2*i + 1;
    int r = 2*i + 2;
    int m = i;

    if(l < n && array[l] > array[m])
    {
        m = l;
        keyComparation = keyComparation + 1;
    }

    if(r < n && array[r] > array[m])
    {
        m = r;
        keyComparation = keyComparation + 1;
    }

    if(m != i)
    {
        change_places(&array[i], &array[m],keyMoviment);
        maxHeapify(array, m, n, keyMoviment, keyComparation);
        keyMoviment = keyMoviment + 1;
    }
}

template <typename T>
void buildHeapMax(T *array, int n, int &keyComparation, int &keyMoviment)
{
    for(int i = n/2 - 1; i >= 0; i--)
    {
        maxHeapify(array, i, n,keyMoviment, keyComparation);
        keyComparation = keyComparation + 1;
        keyMoviment = keyMoviment + 1;
    }
}

template <typename T>
void heapSortFollowers(T *array, int n, int &keyComparation, int &keyMoviment)
{

    buildHeapMax(array, n, keyMoviment, keyComparation);

    for (int i = n-1; i > 0; i--)
    {
        change_places(&array[0], &array[i], keyMoviment);
        maxHeapify(array, 0, i, keyMoviment, keyComparation);
        keyComparation = keyComparation + 1;
        keyMoviment = keyMoviment + 1;
    }
}

/*Fim da implementação do Heapsort*/

/*Implementação do TimSort:*/

template <typename T>
void insertionS(T *array, int left, int right,int &keyComparation, int &keyMovement)
{
    for (int i = left + 1; i <= right; i++)
    {
        int aux = array[i];

        int j = i - 1;

        while (array[j] > aux && j >= left)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = aux;
    }
}

template <typename T>
void merge(T *array, int left, int middle, int right, int &keyComparation, int &keyMovement)
{

    int lenghtFirst = middle - left - 1;
    int lenghtSecond = right - middle;

    T auxLeft[lenghtFirst], auxRight[lenghtSecond];

    int i, j, k;

    i = j = k = 0;

    for (i = 0; i < lenghtFirst; i++)
    {
        auxLeft[i] = array[left + i];
        keyMovement = keyMovement + 1;
    }

    for (i = 0; i < lenghtSecond; i++)
    {
        auxRight[i] = array[middle + 1 + i];
        keyComparation = keyComparation + 1;
    }



    i = 0, j = 0, k = left;

    while(i < lenghtFirst && j < lenghtSecond)
    {
        if(auxLeft[i] <= auxRight[j])
        {
            array[k] = auxLeft[i];
            keyComparation = keyComparation + 1;
            i++;
        }
        else
        {
            array[k] = auxRight[j];
            keyMovement = keyMovement + 1;
            j++;
        }
        k++;
    }

    while(i < lenghtFirst)
    {
        array[k] = auxLeft[i];
        keyComparation = keyComparation + 1;
        k++;
        i++;
    }

    while(j < lenghtSecond)
    {
        array[k] = auxRight[j];
        keyMovement = keyMovement + 1;
        k++;
        j++;
    }
}

template <typename T>
void timSortFollowers(T *array, int n, int &keyComparation, int &keyMovement)
{
    int TAM = n;

    for(int i = 0; i < n; i+=TAM)
    {
        insertionS(array, i, min((i+TAM-1), (n-1)), keyComparation, keyMovement);
    }

    for(int size = TAM; size < n; size = 2*size)
    {
        for(int left = 0; left < n; left += 2*size)
        {
            int middle = left + size - 1;
            int right = min((left + 2*size - 1), (n - 1));

            merge(array, left, middle, right,keyComparation, keyMovement);
            keyMovement = keyMovement + 1;
        }
    }
}

/*Fim da implementação do TimSort*/

#endif /* BFE4D5AD_1277_4333_B833_47920874BC0F */
