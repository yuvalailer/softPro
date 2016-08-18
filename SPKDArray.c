/*
 * SPKDArray.c
 *
 *  Created on: 15 баев„ 2016
 *      Author: NMR
 */

#include "SPKDArray.h"

int num = 0;

struct sp_kdarray_t {
	SPPoint* pointsarr;
	int rows;
	int col;
	int** mat; // the array of sorted indexes referring to P array;
};

//TODO comperator;
int spcompare(const void * a,const void * b){
	a = (const double**) a ;b = (const double**) b;
	return (a[0][num]-b[0][num]);
}

void matrixBuild (int ** mat,int col,int rows,double*** temp) {
	int i;
	num=0;
	for (i=0;i<rows;i++){
		qsort(temp,col,sizeof(temp[0]),spcompare);
		num++;
	}
}


SPKDArray Init(SPPoint* arr, int size){
	int i;
	int j;
	int dim = spPointGetDimension(arr[0]);
	double*** temp = (double***)malloc(sizeof(double**)*size);// temp is a tapel of indexes and fetuars*;

	for(i = 0;i < size;i++ ){
		temp[i] = (double**)malloc(sizeof(double*)*2);
		temp[i][0] = (double*)malloc(sizeof(double)*dim);
	}

	for(i = 0; i < size ; i++){ // fill the temp arry;
		temp[i][1] = spPointGetIndex(arr[i]);
		temp[i][0] = arr[i]->data; //TODO how to copy the data to the new array? do we need a new "geter"?
	}

	SPKDArray ans = (SPKDArray)malloc(sizeof(SPKDArray));

	ans->mat = (int**)malloc(sizeof(int*)*size); // making the matrix. neo
	for(i = 0;i<size;i++){
		ans->mat[i] = (int*)malloc(sizeof(int)*dim);
	}
	ans->col = size;
	ans->rows = dim;

	matrixBuild(ans->mat,ans->col,ans->rows,temp);
	ans->pointsarr = (SPPoint*)malloc(sizeof(SPPoint)*size);
	for(j = 0;j<size;j++){
		ans->pointsarr[j] = spPointCopy(arr[j]);
	}

	return ans;
}


