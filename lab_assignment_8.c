#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n)
{
    int maxHeapSize = 0; 

    for (int i = n / 2 - 1; i >= 0; i--){
        int parent = i;
        while (parent * 2 + 1 < n){
            int largerChild = parent * 2 + 1; 
            if (largerChild + 1 < n && arr[largerChild] < arr[largerChild + 1]){
                largerChild = largerChild + 1;
            }
            if (arr[parent] < arr[largerChild]){
                int temp = arr[parent];
                arr[parent] = arr[largerChild];
                arr[largerChild] = temp;
            }
            else{
                break; 
            }
            parent = largerChild;
        }
        maxHeapSize = parent + 1; 
    }

    
    for (int i = n - 1; i > 0; i--){
        
        int temp = arr[i];
        arr[i] = arr[0];
        arr[0] = temp;

        
        int parent = 0;
        while (parent * 2 + 1 < i){
            int largerChild = parent * 2 + 1; 
            if (largerChild + 1 < i && arr[largerChild] < arr[largerChild + 1]){
                largerChild = largerChild + 1;
            }
            if (arr[parent] < arr[largerChild]){
                int temp = arr[parent];
                arr[parent] = arr[largerChild];
                arr[largerChild] = temp;
            }
            else{
                break; 
            }
            parent = largerChild;
        }
    }

    int extraMemoryAllocated = maxHeapSize * sizeof(int); 

}


void mergeSort(int pData[], int l, int r)
{
	if (l < r) {
  int m = l + (r - l) / 2;
  mergeSort(pData, l, m);
  mergeSort(pData, m + 1, r);

  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

 
  int* L = (int*) malloc(n1 * sizeof(int));
  int* R = (int*) malloc(n2 * sizeof(int));

  for (i = 0; i < n1; i++){
    L[i] = pData[l + i];
    extraMemoryAllocated += sizeof(int);
        }
  for (j = 0; j < n2; j++){
    R[j] = pData[m + 1 + j];
    extraMemoryAllocated += sizeof(int);}

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2){
       if (L[i] <= R[j]) {
       pData[k] = L[i];
        i++;   }
            else{
                pData[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1){
            pData[k] = L[i];
            i++;
            k++;
        }

        while (j < n2){
            pData[k] = R[j];
            j++;
            k++;
        }
        free(L);
        free(R);
    }
}

int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile){
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		if (*ppData == NULL){
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i){
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
  
	for (i=0;i<100;++i){
    if(i>=dataSz){
      printf("\n\n");
      return;
    }
    printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i){
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0) //added to get rid of garbage, only thing altered about the main
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}