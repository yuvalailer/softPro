/* SPKDArray.c
 *
 *  Created on: 15 баев„ 2016
 *///     Author: yuval ailer & michael ozeri


#include "SPKDArray.h"

struct sp_kdarray_t {
	SPPoint* pointsarr;
	int rows;
	int col;
	int** mat; // the array of sorted indexes referring to P array;
};

typedef struct tuple{
	SPPoint point;
	int dex;
	int sortingindex;
}Tuple;

int tuplesort(const void * x,const void * y){
	Tuple* a = (Tuple*)x; Tuple* b = (Tuple*)y;

	return ((spPointGetAxisCoor(a->point,a->sortingindex)) - (spPointGetAxisCoor(b->point,b->sortingindex)));

}

SPKDArray Init(SPPoint* arr, int size){

	SPKDArray ans = (SPKDArray)malloc(sizeof(SPKDArray));

	int i;
	int j;
	int dim = spPointGetDimension(arr[0]);
	int sortingindex = 0;
	Tuple* temp = (Tuple*)malloc(sizeof(Tuple)*size);
	for (i = 0; i < size; ++i) { //initialize special array of tuples
		temp[i].point = spPointCopy(arr[i]);
		temp[i].dex = i;
	}

	for(i=0 ; i<size;i++){
		printf("point is: (%d,%d)\n",spPointGetAxisCoor(temp[i].point,0)
				,spPointGetAxisCoor(temp[i].point,1));
	}
	for(i=0 ; i<size;i++){
			printf("index is: %d\n",temp[i].dex);
		}


	ans->mat = (int**)malloc(sizeof(int*)*size); //initialize matrix of indexes

	for (i = 0; i < size; ++i) {
		ans->mat[i] = (int*)malloc(sizeof(int)*dim);
	}

	for (i = 0; i < dim; ++i) { //fill matrix of indexes

		for(j=0;j<size;j++){
			temp[i].sortingindex = i;
		}
		printf("the %d-th row is: ",i);
		qsort(temp,size,sizeof(Tuple),tuplesort); // sort the array

		for(j=0;j<size;j++){
			ans->mat[i][j] = temp[j].dex;
			printf("%d ",temp[j].dex);
		}
		sortingindex++;
		printf("sorting by index number %d\n",i);
	}
	ans->rows = dim;
	ans->col = size;

	for (i = 0; i < size; ++i) {
		ans->pointsarr[i] = (SPPoint)malloc(sizeof(SPPoint));
		ans->pointsarr[i] = spPointCopy(arr[i]);
	}

	return ans;
}

int main(){

	int j;

	int size = 5;
	int dim = 2;
	int i=0;

	SPPoint* arr = (SPPoint*)malloc(sizeof(SPPoint)*size);

	int a1[2] = {1,2};
	int b1[2] = {123,70};
	int c1[2] = {2,7};
	int d1[2] = {9,11};
	int e1[2] = {3,4};

	SPPoint a = spPointCreate(a1,dim,1);
	SPPoint b = spPointCreate(b1,dim,1);
	SPPoint c = spPointCreate(c1,dim,1);
	SPPoint d = spPointCreate(d1,dim,1);
	SPPoint e = spPointCreate(e1,dim,1);

	arr[0] = a;
	arr[1] = b;
	arr[2] = c;
	arr[3] = d;
	arr[4] = e;


	SPKDArray kdarr = Init(arr,size);

	return 0;
}





