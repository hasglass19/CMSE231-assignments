#include<stdio.h>
#include<stdlib.h>
#define ARRAYSIZE 25

int bSearch(int a[], int sFor, int low, int high)
{
	int mid;
	if (low > high)
	{
		printf("Number Not Found");
		return -1;
	}
	mid = (low + high) / 2;
	if (sFor == a[mid])
		return mid;
	if (sFor < a[mid])
		return(bSearch(a, sFor, low, mid - 1));
	else
		return(bSearch(a, sFor, mid + 1, high));
}

int inOrder(int a[])
{
	for (int i = 0; i < ARRAYSIZE - 1; i++)
	{
		if (a[i] > a[i + 1])
			return 0;
	}
	return 1;
}

int partition(int a[],int low,int high)
{
	int pivot = a[low],left=low, temp;
	for (int i = low + 1; i < high; i++)
		if (a[i] < pivot)
		{
			temp = a[i];
			a[i] = a[left];
			a[left] = temp;
			left++;
		}

	temp = pivot;
	pivot = a[left];
	a[left] = temp;

	return(left);
}

void quickSort(int a[], int low, int high)
{
	if (low < high)
	{
		int pivot_location=partition(a,low,high);
		quickSort(a, low, pivot_location);
		quickSort(a, pivot_location + 1, high);
	}
}

int main()
{
	int result, numero, arra[ARRAYSIZE];
	printf("Enter your numbers:\n");
	for (int i = 0; i < ARRAYSIZE; i++)
	{
		scanf("%d", &arra[i]);
		printf("%d number(s) have been entered.\n", i+1);
	}

	printf("Enter the number you want to find:\n");
	scanf("%d", &numero);

	while (inOrder(arra) == 0)
		quickSort(arra, 0, ARRAYSIZE);

	printf("The numbers in order are:\n");
	for (int i = 0; i < ARRAYSIZE; i++)
		printf("%d ", arra[i]);
	printf("\n\n\n");
	

	result = bSearch(arra, numero, 0, ARRAYSIZE);
	if (result != -1)
		printf("The number %d was found at %d",numero,result);

	return 0;
}