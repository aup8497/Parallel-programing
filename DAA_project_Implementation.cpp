#include <iostream>
#include <cmath>
#include <cstdio>
#include <omp.h>
#include <time.h>

using namespace std;

int a[10000007],n,i;

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    int L[n1], R[n2];
 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    i = 0; 
    j = 0;
    k = l; 
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void coordinate_recorded_mergeSort(int a[],int low,int high){

	int gap=1;

	int	n=ceil(log2f(high-low+1));

	for(int count=1;count<=n;count++){
		cout << pow(2,count) << endl; 
		gap*=2;

		#pragma omp parallel for 
		for(i=0;i<high;i+=gap){
			merge(a, i, (i+gap/2-1) , (i+gap-1) );
		}
	}

}

int main(){

	clock_t t=clock();


	cout << "enter the number of elements in the array " << endl;
	cin >> n;
	cout << "enter the elements" << endl;
	for(i=0;i<n;i++){
		cin >> a[i] ;
	}

	int	num=ceil(log2f(n));
	int lim=pow(2,num);

	for (i = n; i <= lim; ++i){
		a[i]=99999;
	}

	coordinate_recorded_mergeSort(a,0,lim-1);

  printf ( "  Number of processors available = %d\n", omp_get_num_procs ( ) );
  printf ( "  Number of threads =              %d\n", omp_get_max_threads ( ) );

	for (int i = 0; i < n; ++i){
		cout << a[i] << " " ;
	}
	cout << endl;


	clock_t t1=clock();

	cout << (double)(t1-t) / CLOCKS_PER_SEC << endl;

return 0;
}
