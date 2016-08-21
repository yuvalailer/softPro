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
	ans->mat = (int**)malloc(sizeof(int*)*dim); //initialize matrix of indexes
	for (i = 0; i < dim; ++i) {
		ans->mat[i] = (int*)malloc(sizeof(int)*size);
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
	free (temp);
	return ans;
}

SPKDArray* Split(SPKDArray kdArr, int coor){
	int size = kdArr->col;
	int dim = kdArr->rows;
	int i,j;
	int sizeR = (int)size/2;
	int sizeL = size - sizeR;
	int* map1 = (int*)malloc(sizeof(int)*size);
	int* map2 = (int*)malloc(sizeof(int)*size);

	SPKDArray* ans = (SPKDArray*)malloc(sizeof(SPKDArray)*2);

	SPKDArray left = (SPKDArray)malloc(sizeof(SPKDArray));
	SPKDArray right = (SPKDArray)malloc(sizeof(SPKDArray));
	for(j = 0;j < dim ; j++ ) {

		for (i = 0; i < size; i++) {
			map1[i] = -1; map2[i] = -1; // fill map1 and 2 to be all -1;
		}

		for(i=0;i<sizeL;i++){
			map1[kdArr->mat[coor][i]] =  i;
		}
		for(i=0;i<sizeR;i++){
			map2[kdArr->mat[coor][i+sizeL]] =  i;
		}
	}
	// make the P's;
	for(i=0;i<sizeL;i++){ // fill left
		left->pointsarr[i] = kdArr->pointsarr[kdArr->mat[coor][i]];
	}

	for(i=0;i<sizeR;i++){ //fill right
		right->pointsarr[i] = kdArr->pointsarr[kdArr->mat[coor][i+sizeL]]; // TODO is sizeL the correcrt?
	}

	//	left->col = sizeL;
	//	right->col = sizeR;
	//	left->rows = kdArr->rows;
	//	right->rows = kdArr->rows;

	ans[0] = left;
	ans[1] = right;
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

	int i,j;

	for (i = 0; i < kdarr->rows; i++) {
		for (j = 0; j < kdarr->col;j++) {
			printf("%d ",kdarr->mat[i][j]);
		}
		printf("\n");
	}

	return 0;
}

 */




