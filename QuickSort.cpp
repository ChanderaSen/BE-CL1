 #include <iostream>
#include <stdlib.h>
#include <omp.h>
using namespace std;


int partition(int * a, int p, int r)
{
    int lt[r-p];
    int gt[r-p];
    int i;
    int j;
    int key = a[r];
    int lt_n = 0;
    int gt_n = 0;

#pragma omp parallel for
    for(i = p; i < r; i++){
        if(a[i] < a[r]){
            lt[lt_n++] = a[i];
        }else{
            gt[gt_n++] = a[i];
        }  
    }  

    for(i = 0; i < lt_n; i++){
        a[p + i] = lt[i];
    }  

    a[p + lt_n] = key;

    for(j = 0; j < gt_n; j++){
        a[p + lt_n + j + 1] = gt[j];
    }  

    return p + lt_n;
}

void quicksort(int * a, int p, int r)
{
    int div;

    if(p < r)
   { 
        div = partition(a, p, r); 
        #pragma omp parallel sections
        {  
            #pragma omp section
            quicksort(a, p, div - 1); 
             #pragma omp section
            quicksort(a, div + 1, r); 

        }
    }
}

int main(void)
{
   int i, n, a[10];
   cout<<"Enter the count to sort the numbers:- ";
   cin>>n;
   cout<<endl;
   cout<<"Enter the elements to sort the numbers:- ";
    for(i = 0;i < n; i++)
        {
            cin>>a[i];
    }

    quicksort(a, 0, n-1);
    cout<<"The Sorted elements are:- "<<endl;
    for(i = 0;i < n; i++){
        cout<<"\t"<<a[i];
    }
   cout<<endl;
    return 0;
}
