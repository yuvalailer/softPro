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
	int dim = spPointGetDimension(arr[0]); // checking dimension of sppoints in arr
	Tuple* temp = (Tuple*)malloc(sizeof(Tuple)*size);
	for (i = 0; i < size; i++) { //initialize special array of tuples
		temp[i].point = spPointCopy(arr[i]);
		temp[i].sortingindex = 0;
	}
	ans->mat = (int**)malloc(sizeof(int*)*size); //initialize matrix of indexes
	for (i = 0; i < size; ++i) {
		ans->mat[i] = (int*)malloc(sizeof(int)*dim);
	}

	for (i = 0; i < dim; ++i) { //fill matrix of indexes
		for(j=0;j<size;j++){
			temp[j].sortingindex = i;
		}
		qsort(temp,size,sizeof(Tuple),tuplesort); // sort the array
		for(j=0;j<size;j++){
			ans->mat[i][j] = spPointGetIndex(temp[j].point);
		}
	}
	ans->rows = dim;
	ans->col = size;
	for (i = 0; i < size; ++i) {
		ans->pointsarr[i] = (SPPoint)malloc(sizeof(SPPoint));
		ans->pointsarr[i] = spPointCopy(arr[i]);
	}
	return ans;
}

/*
int main(){

	int size = 5;
	int dim = 2;

	SPPoint* arr = (SPPoint*)malloc(sizeof(SPPoint)*size);

	double a1[2]= {1,2};
	double b1[2] = {123,70};
	double c1[2] = {2,7};
	double d1[2] = {9,11};
	double e1[2]= {3,4};

	arr[0] = (spPointCreate(a1,dim,0));
	arr[1] = (spPointCreate(b1,dim,1));
	arr[2] = (spPointCreate(c1,dim,2));
	arr[3] = (spPointCreate(d1,dim,3));
	arr[4] = (spPointCreate(e1,dim,4));

	SPKDArray kdarr = Init(arr,size);

	return 0;
}
*/





