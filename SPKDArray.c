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

struct sort_tuple{
	SPPoint point;
	int sortingindex;
	int pdex; // index in pointsarray
};

struct splitkdarrtuple{
	SPKDArray* left;
	SPKDArray* right;
};

int tuplesort(const void * x,const void * y){
	SortTuple* a = (SortTuple*)x; SortTuple* b = (SortTuple*)y;
	return ((spPointGetAxisCoor(a->point,a->sortingindex)) - (spPointGetAxisCoor(b->point,b->sortingindex)));
}

SPKDArray* Init(SPPoint* arr, int size){
	SPKDArray* ans = (SPKDArray*)malloc(sizeof(SPKDArray));
	int i;
	int j;

	int dim = spPointGetDimension(arr[0]); // checking dimension of SPPoints in arr

	SortTuple* temp = (SortTuple*)malloc(sizeof(SortTuple)*size);
	for (i = 0; i < size; i++) { //initialize special array of tuples
		temp[i].point = spPointCopy(arr[i]);
		temp[i].sortingindex = 0;
		temp[i].pdex = i;
	}

	ans->mat = (int**)malloc(sizeof(int*)*dim); //initialize matrix of indexes
	for (i = 0; i < dim; ++i) {
		ans->mat[i] = (int*)malloc(sizeof(int)*size);
	}


	for (i = 0; i < dim; ++i) { //fill matrix of indexes
		for(j=0;j<size;j++){
			temp[j].sortingindex = i;
		}
		qsort(temp,size,sizeof(SortTuple),tuplesort); // sort the array
		for(j=0;j<size;j++){
			ans->mat[i][j] = (temp[j].pdex);
		}
	}

	ans->rows = dim;
	ans->col = size;

	ans->pointsarr = arr; /*(SPPoint*)malloc(sizeof(SPPoint)*size); // copying arr into pointsarr
	for (i = 0; i < size; ++i) {
		ans->pointsarr[i] = spPointCopy(arr[i]); //TODO delete if working
	}*/

	TupleDestroy(temp,size);
	return ans;
}

KDArrayTuple* Split(SPKDArray* kdArr, int coor){

	int size = kdArr->col;
	int dim = kdArr->rows;
	int num; // the num from the matrix.
	int i,j,t,p;
	int sizeR = (int)size/2;
	int sizeL = size - sizeR;
	int X[size];
	for (i = 0; i < size; ++i) { //initialize X to be all 1.
		X[i] = 1;
	}
	int map1[size];
	int map2[size];

	KDArrayTuple* ans = (KDArrayTuple*)malloc(sizeof(KDArrayTuple));
	SPKDArray* left = (SPKDArray*)malloc(sizeof(SPKDArray));
	SPKDArray* right = (SPKDArray*)malloc(sizeof(SPKDArray));
	right->pointsarr = (SPPoint*)malloc(sizeof(SPPoint)*sizeR);
	left->pointsarr = (SPPoint*)malloc(sizeof(SPPoint)*sizeL);

	right->mat = (int**)malloc(sizeof(int*)*dim); //initialize matrix of indexes of right SPKDArray
	for (i = 0; i < dim; ++i) {
		right->mat[i] = (int*)malloc(sizeof(int)*sizeR);
	}

	left->mat = (int**)malloc(sizeof(int*)*dim); //initialize matrix of indexes of left SPKDArray
	for (i = 0; i < dim; ++i) {
		left->mat[i] = (int*)malloc(sizeof(int)*sizeL);
	}

	for(i=0;i<sizeL;i++){ // fill all left in x; o.k!
		X[kdArr->mat[coor][i]] = 0;
	}
	// now we have X[1,0,...]



	// make the P's:
	for(i=0;i<sizeL;i++){ // fill left
		left->pointsarr[i] = kdArr->pointsarr[kdArr->mat[coor][i]];
	}

	for(i=0;i<sizeR;i++){ //fill right
		right->pointsarr[i] = kdArr->pointsarr[kdArr->mat[coor][i+sizeL]];
	}


	// initializing map1 and 2 to be all -1;

	for (i = 0; i < size; i++) {
		map2[i] = -1;
		map1[i] = -1;
	}

	//filling map1 & map2

	for(i=0;i<sizeL;i++){
		map1[kdArr->mat[coor][i]] =  i;
	}

	for(i=0;i<sizeR;i++){
		map2[kdArr->mat[coor][i+sizeL]] =  i;
	}

	// scanning all the original matrix to fill right and left matrix.

	for(i=0;i<dim;i++){ //iterate over cols
		t = 0; p = 0;
		for(j=0;j<size;j++){ // move on row
			num = kdArr->mat[i][j];
			if(X[num] == 0){ // if the cell is in p1
				left->mat[i][t] = map1[num]; // a1 in place t is the new coordinate in p1;
				t++;
			} else { // if the cell is in p2
				right->mat[i][p] = map2[num];// a2 in place p is the new coordinate in p2;
				p++;
			}
		}
	}


	left->col = sizeL;
	right->col = sizeR;
	left->rows = kdArr->rows;
	right->rows = kdArr->rows;
	ans->left = left;
	ans->right = right;

	return ans;
}

int Getcol(SPKDArray* kdArr){
	int temp = kdArr->col;
	return temp;
}

int Getrows(SPKDArray* kdArr){
	int temp = (kdArr->rows);
	return temp;
}
int** GetMat(SPKDArray* kdArr){
	return kdArr->mat;
}

SPPoint* Getpointsarray(SPKDArray* kdArr){
	return kdArr->pointsarr;
}

SPKDArray* kdtupgetleft(KDArrayTuple* tup){
	return tup->left;
}

SPKDArray* kdtupgetright(KDArrayTuple* tup){
	return tup->right;
}

void TupleDestroy(SortTuple* tup,int size){
	int i;
	for (i = 0; i < size; ++i) {
		spPointDestroy(tup[i].point);
	}
	free(tup);


}

void KDArrayDestroy(SPKDArray* arr){
	int i;
	for (i = 0; i <  arr->rows; ++i) {
		free(arr->mat[i]);
	}
	free(arr->mat);
	for (i = 0; i < arr->col; ++i) {
		spPointDestroy(arr->pointsarr[i]);
	}
	free(arr->pointsarr);
	free(arr);
}

void KDArrayTupleDestroy(KDArrayTuple* tup){
	int i;
	//	KDArrayDestroy(tup->left);
	//	KDArrayDestroy(tup->right);
	free(tup->left->pointsarr);
	for (i = 0; i < tup->left->rows; ++i) {
		free(tup->left->mat[i]);
	}
	free(tup->left->mat);
	free(tup->left);
	free(tup->right->pointsarr);
	for (i = 0; i < tup->right->rows; ++i) {
		free(tup->right->mat[i]);
	}
	free(tup->right->mat);
	free(tup->right);
	free(tup);
}



/*int main(){

	int size = 5;
	int dim = 2;

	SPPoint* sppointarr = (SPPoint*)malloc(sizeof(SPPoint)*size);

	double a1[2]= {1,2};
	double b1[2] = {123,70};
	double c1[2] = {2,7};
	double d1[2] = {9,11};
	double e1[2]= {3,4};

	sppointarr[0] = (spPointCreate(a1,dim,0));
	sppointarr[1] = (spPointCreate(b1,dim,1));
	sppointarr[2] = (spPointCreate(c1,dim,2));
	sppointarr[3] = (spPointCreate(d1,dim,3));
	sppointarr[4] = (spPointCreate(e1,dim,4));

	SPKDArray* kdarr = Init(sppointarr,size);

	int i,j;

	printf("matix of first kdarray is : \n");

	for (i = 0; i < kdarr->rows; i++) {
		for (j = 0; j < kdarr->col;j++) {
			printf("%d ",kdarr->mat[i][j]);
		}
		printf("\n");
	}

	KDArrayTuple* kdarrtup = Split(kdarr,0);
	SPKDArray* ail1 = kdtupgetleft(kdarrtup);
	SPKDArray* ail2 = kdtupgetright(kdarrtup);

	printf("points of left kdarray are: \n");
	for (i = 0; i < 3; ++i) {
		printf("%d place - (%f,%f)\n",i,spPointGetAxisCoor(ail1->pointsarr[i],0),spPointGetAxisCoor(ail1->pointsarr[i],1));
	}
	printf("\n");

	printf("mat of left kdarray is: \n");
	for (i = 0; i < 2; ++i) {
		for (j = 0; j < 3; ++j) {
			printf("%d ",ail1->mat[i][j]);
		}
		printf("\n");
	}
	printf("points of right kdarray are: \n");
	for (i = 0; i < 2; ++i) {
		printf("%d place - (%f,%f)\n",i,spPointGetAxisCoor(ail2->pointsarr[i],0),spPointGetAxisCoor(ail2->pointsarr[i],1));
	}
	printf("\n");
	printf("mat of right kdarray is: \n");
	for (i = 0; i < 2; ++i) {
		for (j = 0; j < 2; ++j) {
			printf("%d ",ail2->mat[i][j]);
		}
		printf("\n");
	}
	printf("woohooo!");


	KDArrayTupleDestroy(kdarrtup);

	KDArrayDestroy(kdarr);


	return 0;
}*/








