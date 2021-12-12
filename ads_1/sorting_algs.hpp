#include<cstdlib>
#include<cmath>
#include<cstdbool>

#ifndef SORTING_ALGS_HPP_INCLUDED
#define SORTING_ALGS_HPP_INCLUDED

void swap(int *a, int *b) {
    /*** swaping two integers, passed by reference ***/
    int c = *a;
    *a = *b;
    *b = c;
}

void print_array(int A[], int size) {
    /*** print every element from array A to standard output ***/
    for (int i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void randomize_array(int A[], int size, int lower_bound, int upper_bound) {
    /*** insert random integers into array A from interval [lower_bound, upper_bound] ***/
    for (int i = 0; i < size; i++)
        A[i] = rand() % (upper_bound - lower_bound + 1) + lower_bound;
}

void const_array(int A[], int size, int x) {
    for (int i = 0; i < size; i++)
        A[i] = x;
}

void asc_array(int A[], int size) {
    for (int i = 1; i <= size; i++)
        A[i - 1] = i;
}

void desc_array(int A[], int size) {
    for (int i = 0; i < size; i++)
        A[i] = size - i;
}

void A_shape(int A[], int size) {
    int mid = size / 2;
    for (int i = 0; i <= mid; i++)
        A[i] = 2*i + 1;
    for (int i = 0; i <= mid; i++)
        A[(size + 1) / 2 + i] = 2 * (mid - i);
}

void V_shape(int A[], int size) {
    for (int i = 0; i <= (size - 1) / 2; i++)
        A[i] = (size - 1) / 2 * 2 + 1 - 2*i;
    for (int i = 0; i <= size / 2; i++)
        A[(size + 1) / 2 + i] = 2 * (i+1);
}

// *********************************************************************
//INSERTION SORT
void insertion_sort(int A[], int size) {
    for (int i = 1; i < size; i++) {
        int j = i, temp = A[j];
        bool c = true;
        while (j > 0 && c == true) {
            if (A[j - 1] > temp) {
                A[j] = A[j-1];
            } else {
                c = false;
                A[j] = temp;
            }
            j--;
        }
        if (c == true) {
            A[j] = temp;
        }
    }
}

// *********************************************************************
// SELECTION SORT
void selection_sort(int A[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int temp_min = i;
        // search for the min
        for (int j = i + 1; j < size; j++) {
            if (A[j] < A[temp_min]) {
                temp_min = j;
            }
        }
        // swap min with current
        swap(A + i, A + temp_min);
    }
}

// *********************************************************************
//BUBBLE SORT
void bubble_sort(int A[], int size) {
    bool stop = false;

    while (stop == false) {
        stop = true;
        for (int i = 1; i < size; i++) {
            if (A[i - 1] > A[i]) {
                swap(A + i - 1, A + i);
                stop = false;
            }
        }
    }
}

// *********************************************************************
// HEAP SORT
void heapify(int A[], int size, int parent) {
    /*** repair the heap from parent to leaves ***/
    int left = 2*parent + 1;
    int right = 2*parent + 2;

    if (right < size) { // if right child exists
        if (A[right] > A[left] && A[right] > A[parent]) { // if right child is greater than left and parent
            swap(A + right, A + parent);
            heapify(A, size, right);
        } else if (A[left] > A[parent]) { // if left child is greater than right and parent
            swap(A + left, A + parent);
            heapify(A, size, left);
        }
    } else if (left < size) {       // if right child does not exist but left does
        if (A[left] > A[parent]) { // if left child is greater than parent
            swap(A + left, A + parent);
            heapify(A, size, left);
        }
    }
}

void make_heap(int A[], int size) {
    /*** create the heap from array A ***/
    // heapify from last non leaf to root
    int start = size / 2;
    for (int i = start; i > -1; i--)
        heapify(A, size, i);
}

void pop_heap(int A[], int size) {
    /*** pop root from the heap to last position in array A ***/
    // swap last element with root
    swap(A, A + size - 1);
    // repair the heap
    heapify(A, size - 1, 0);
}

void heap_sort(int A[], int size) {
    // create a heap
    make_heap(A, size);
    // pop all elements
    for (int i = size; i > 1; i--) {
        pop_heap(A, i);
    }
}

// *********************************************************************
//QUICK SORT
int divide(int A[], int begin, int end) {
    int j = end, i = begin, piv = (begin + end) / 2;
    int x = A[piv];
    while (true) {
        while (A[j] > x) {
            j--;
        }
        while (A[i] < x) {
            i++;
        }
        if (i < j) {
            swap(&(A[i++]), &(A[j--]));
        } else {
            break;
        }
    }
    return j;
}

void quicksort(int A[], int begin, int end) {
    if (begin < end) {
        int pivot = divide(A, begin, end);
        quicksort(A, begin, pivot);
        quicksort(A, pivot+1, end);
    }
}

void quick_sort(int A[], int size) {
    quicksort(A, 0, size-1);
}

// *********************************************************************
// MERGE SORT
void merge_sorting(int A[], int B[], int begin, int end) {
    /*** proper recursive merge sort on A from begin to end with accessory array B ***/
    if (begin == end)
        return;

    // recursion on halves
    int mid = (begin + end) / 2;
    merge_sorting(A, B, begin, mid);
    merge_sorting(A, B, mid + 1, end);

    // merge halves
    int i = begin, j = mid + 1, pointer = begin;
    while (i <= mid && j <= end) {
        if (A[i] <= A[j])
            B[pointer++] = A[i++];
        else
            B[pointer++] = A[j++];
    }
    while (i <= mid)
        B[pointer++] = A[i++];
    while (j <= end)
        B[pointer++] = A[j++];

    // copy array B to array A
    for (int g = begin; g <= end; g++)
        A[g] = B[g];
}

void merge_sort(int A[], int size) {
    int *B = new int [size];
    merge_sorting(A, B, 0, size - 1);
    delete [] B;
}

// *********************************************************************
//SHELL SORT -MARCIN CIURA METHOD
void SHS_ciura(int n, int tab[]) {
    int ciura[] = {701, 301, 132, 57, 23, 10, 4, 1};    //CI¥G Z WIKIPEDII - wiadomo wzoru nie by³o, wiec trzeba bylo wypisac
    int len = 8;
    for(int i = 0; i<len; i++) {
        if(ciura[i]<n) {                                // iteracja przez ciurê
            for(int start = 0; start < ciura[i]; start++) { // iteracja przez ciura[i] podci¹ców
                for(int z = start + ciura[i]; z<n; z = z + ciura[i]) {
                    int j = z;                              // normalny IS w ka¿dym z ciura[i] podciagow
                    bool c = true;
                    int pom = tab[j];
                    while(j - ciura[i]>=0 && c == true) {
                        if(tab[j - ciura[i]] > pom) {
                            tab[j] = tab[j-ciura[i]];
                        } else {
                            c = false;
                            tab[j] = pom;
                        }
                        j = j - ciura[i];
                        if(c == true) {
                            tab[j] = pom;
                        }
                    }
                }
            }
        }
    }
}

//SHELL SORT CLASSIC METHOD
int gap_generator(int n, int iteration, int k ) {
    if (iteration == k - 1) {
        return 1;
    } else {
        return (int)(n/(2<<iteration));
    }
}

void SHS_classic(int n, int tab[]) {
    int i = 0;
    int k = log(n)/log(2);                          //- k= iteracja dla której gap = 1- bo nie zawsze tak wychodzi
    int gap = gap_generator(n, i, k);
    while(gap>0) {
        for(int start = 0; start < gap; start++) {      //tutaj praktycznie tak jak w poprzednim
            for(int z = start + gap; z<n; z = z + gap) {
                int j = z;
                bool c = true;
                int pom = tab[j];
                while(j - gap>=0 && c == true) {
                    if(tab[j - gap] > pom) {
                        tab[j] = tab[j-gap];
                    } else {
                        c = false;
                        tab[j] = pom;
                    }
                    j = j - gap;
                    if(c == true) {
                        tab[j] = pom;
                    }
                }
            }
        }
        i++;
        gap = gap_generator(n, i, k);
    }
}

// *********************************************************************
// COUNTING SORT
void counting_sort(int A[], int size) {
    // create array B for keeping number of occurrences
    int maximum_element = A[0];
    for (int i = 1; i < size; i++)
        if (A[i] > maximum_element)
            maximum_element = A[i];
    int *B = new int [maximum_element + 1];
    for (int i = 0; i <= maximum_element; i++)
        B[i] = 0;

    // count elements and make prefixes sums
    for (int i = 0; i < size; i++)
        B[A[i]]++;
    for (int i = 1; i <= maximum_element; i++)
        B[i] += B[i-1];

    // create result array and fill it
    int *C = new int [size];
    for (int i = 0; i < size; i++)
        C[B[A[i]]-- - 1] = A[i];
    // copy result array into A
    for (int i = 0; i < size; i++)
        A[i] = C[i];
    delete [] C;
    delete [] B;
}


#endif // SORTING_ALGS_HPP_INCLUDED
