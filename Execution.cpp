#include<time.h>
#include<iostream>
#include<cstdlib>
#include"Sort.h"
using namespace std;
#define asize 10
int main() {
	srand(time(NULL));
	int arr[asize];
	for (int i = 0; i < asize; ++i) {
		arr[i] = rand() % 100;
	}
	display("Before Insertionsort!",arr, asize);
	Insertionsort(arr, asize);
	display("After the Insertionsort!",arr, asize);
   getchar();
}