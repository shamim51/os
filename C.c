#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int arr1[50] = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8}, arr2[50], arr3[50], arr4[50];
int subarr1, subarr2, total;

void *subarr1_func(void* arg) {
	sleep(1);
	printf("\nFirst subarray: ");
	for (int i = 0; i < subarr1; i++) {
		printf("%d  ", arr2[i]);
	}
	for (int i = 0; i < subarr1; i++) {
		for (int j = 0; j < subarr1 - (i + 1); j++) {
			if (arr2[j] > arr2[j + 1]) {
				int temp = arr2[j];
				arr2[j] = arr2[j + 1];
				arr2[j + 1] = temp;
			}
		}
	}
	printf("\nFirst Sorted array: ");
	for (int i = 0; i < subarr1; i++) {
		printf("%d  ", arr2[i]);
	}
}

void *subarr2_func(void* arg) {
	sleep(2);
	printf("\nSecond subarray: ");
	for (int i = 0; i < subarr2; i++) {
		printf("%d  ", arr3[i]);
	}
	for (int i = 0; i < subarr2; i++) {
		for (int j = 0; j < subarr2 - (i + 1); j++) {
			if (arr3[j] > arr3[j + 1]) {
				int temp = arr3[j];
				arr3[j] = arr3[j + 1];
				arr3[j + 1] = temp;
			}
		}
	}

	printf("\nSecond Sorted array: ");
	for (int i = 0; i < subarr2; i++) {
		printf("%d  ", arr3[i]);
	}
}

void *merge_func(void* arg) {
	sleep(3);
	total = subarr1 + subarr2;
	for (int i = 0; i < subarr1; i++) {
		arr4[i] = arr2[i];
	}
	int tempsubarr1 = subarr1;
	for (int i = 0; i < subarr2; i++) {
		arr4[tempsubarr1] = arr3[i];
		tempsubarr1++;
	}
	printf("\nMerged Array: ");
	for (int i = 0; i < total; i++) {
		printf("%d  ", arr4[i]);
	}
	for (int i = 0; i < total; i++) {
		for (int j = 0; j < total - i - 1; j++) {
			if (arr4[j + 1] < arr4[j]) {
				int temp = arr4[j];
				arr4[j] = arr4[j + 1];
				arr4[j + 1] = temp;
			}
		}
	}
}

int main(int argc, char const *argv[]) {
	int n = 10;
	pthread_t t1, t2, t3;

	printf("Given Array: ");
	for (int i = 0; i < n; i++) {
		printf("%d  ", arr1[i]);
	}
	int j = 0;
	for (int i = 0; i < n / 2; i++) {
		arr2[j] = arr1[i];
		j++;
	}
	subarr1 = j;
	int k = 0;
	for (int i = n / 2; i < n; i++) {
		arr3[k] = arr1[i];
		k++;
	}
	subarr2 = k;
	pthread_create(&t1, NULL, subarr1_func, NULL);
	pthread_create(&t2, NULL, subarr2_func, NULL);
	pthread_create(&t3, NULL, merge_func, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	printf("\nSorted Merged Array: ");
	for (int i = 0; i < total; i++) {
		printf("%d  ", arr4[i]);
	}
	printf("\n");
	return 0;

}
/*
gcc -0 C C.c -lpThread
./C
10
7 12 19 3 18 4 2 6 15 8
*/

