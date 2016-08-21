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
	ans->pointsarr = (SPPoint*)malloc(sizeof(SPPoint)*size);
	for (i = 0; i < size; ++i) {
		ans->pointsarr[i] = spPointCopy(arr[i]);
	}
	free (temp);
	return ans;
}

SPKDArray* Split(SPKDArray kdArr, int coor){
	int size = kdArr->col;
	int dim = kdArr->rows;
	int num; // the num from the matrix.
	int i,j,t,p;
	int sizeR = (int)size/2;
	int sizeL = size - sizeR;
	int* X = (int*)malloc(sizeof(int)*size);
	int* map1 = (int*)malloc(sizeof(int)*size);
	int* map2 = (int*)malloc(sizeof(int)*size);

	SPKDArray* ans = (SPKDArray*)malloc(sizeof(SPKDArray)*2);
	SPKDArray left = (SPKDArray)malloc(sizeof(SPKDArray));
	SPKDArray right = (SPKDArray)malloc(sizeof(SPKDArray));

	for(i=0;i<sizeR;i++){ // fill all left in x;
		X[kdArr->mat[coor][i]] = 0;
	}
	for(i=0;i<sizeR;i++){ // fill all the right in X;
		X[kdArr->mat[coor][i+sizeL]] =  1;
	}
	// now we have x[1,0,...]

	// make the P's;
		for(i=0;i<sizeL;i++){ // fill left
			left->pointsarr[i] = kdArr->pointsarr[kdArr->mat[i][coor]];
		}

		for(i=0;i<sizeR;i++){ //fill right
			right->pointsarr[i] = kdArr->pointsarr[kdArr->mat[coor][i+sizeL]]; // TODO is sizeL the correcrt?
		}
	// maping 1 and 2.

		for (i = 0; i < size; i++) {
			map1[i] = -1; map2[i] = -1; // fill map1 and 2 to be all -1;
		}

		for(i=0;i<sizeL;i++){
			map1[kdArr->mat[coor][i]] =  i;
		}
		for(i=0;i<sizeR;i++){
			map2[kdArr->mat[coor][i+sizeL]] =  i;
		}

		// scanning all the original matrix to fill right and left matrix.

		for(i=0;i<dim;i++){ // move on col
			t = 0; p = 0;
			for(j=0;j<size;j++){ // move on row
				num = kdArr->mat[i][j]; //TODO first row or col? in i and j?
				if(X[num] == 0){ // if the cell is in p1
					left->mat[i][t] = map1[num]; // a1 in place t is the new cordinate in p1;
					t++;
				} else { // if the cell is in p2
					right->mat[i][p] = map2[num];// a2 in place p is the new cordinate in p2;
					p++;
				}
			}
		}


		left->col = sizeL;
		right->col = sizeR;
		left->rows = kdArr->rows;
		right->rows = kdArr->rows;

		ans[0] = left;
		ans[1] = right;
		return ans;
}


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
	SPKDArray* sparr = Split(kdarr,0);
	SPKDArray ail1 = sparr[0];
	SPKDArray ail2 = sparr[1];

	for (i = 0; i < 2; ++i) {
		for (j = 0; j < 3; ++j) {
			printf("%d ",ail1->mat[i][j]);
		}
		printf("\n");
	}

	for (i = 0; i < 2; ++i) {
			for (j = 0; j < 2; ++j) {
				printf("%d ",ail2->mat[i][j]);
			}
			printf("\n");
		}

	return 0;
}






