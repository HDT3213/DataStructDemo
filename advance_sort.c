#include<stdio.h>

#define M 16

#define out(arr,Len) \
for (int k = 0; k < Len; k++) { \
	printf("%d ", arr[k]); }\
	printf("\n");


//shell sort
int *shell_sort(int *arr, int Len)  {
   int i, j, t, gap;
   for (gap = Len / 2; gap > 0; gap /= 2) {
   	for (i = gap; i < Len; i++) {
   		for ( j = i - gap; j >= 0 && arr[j] > arr[j + gap]; j -= gap) {
   			t = arr[j];
   			arr[j] = arr[j+gap];
   			arr[j+gap] = t;
   		}
   	}
   }
   return arr;
}


//quick sort
int *q_sort(int *arr, int left, int right) {
	int i, j, t, temp;
	if (left >= right) {
		return arr;	
	}
	temp = arr[left];
	i = left;
	j = right;
	while (i != j) {
		while (arr[j] >= temp && i<j) {
			j--;
    	}
		while (arr[i] <= temp && i<j) {
			i++;
		}
		if (i < j) {
			t = arr[i];
			arr[i] = arr[j];
			arr[j] = t; 	
		}	
	}
	arr[left] = arr[i];
	arr[i] = temp;
	q_sort(arr,left, i-1);
	q_sort(arr,i+1, right);
	return arr;
}


//merge sort
void merge_array(int *arr, int first, int mid, int last, int *temp) {
	int i = first, j = mid + 1, k = 0;
	int m = mid, n = last;
	
	while (i <= m && j <= n) {
		if (arr[i] <= arr[j]) {
			temp[k++] = arr[i++];	
		}
		else {
			temp[k++] = arr[j++];	
		}	
	}
	while (i <= m) {
		temp[k++] = arr[i++];	
	}
	while (j <= n) {
		temp[k++] = arr[j++];	
	}
	
	for (i = 0; i < k; i++) {
		arr[first + i] = temp[i];	
	}
}

void merge_sorting(int *arr, int first,  int last, int *temp) {
	int mid = (first + last) / 2;	
	
	if (first < last) {
		merge_sorting(arr, first, mid, temp);
		merge_sorting(arr, mid + 1, last, temp);
		merge_array(arr,first, mid, last, temp);
	}
}

int *merge_sort(int *arr, int n) {
	int temp[M];
	merge_sorting(arr, 0, n-1, temp);
	return arr;
}

int main()  {
	int arr[M];
	int i, Len;
	scanf("%d", &Len);
	for (i = 0; i < Len; i++) {
		scanf("%d", &arr[i]);
	}
	//q_sort(arr, 0, Len-1);
	merge_sort(arr, Len);
	out(arr,Len);	 	
	return 0;
}