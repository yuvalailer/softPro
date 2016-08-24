/*
 * auxiliaryfunc.c
 *
 *  Created on: 23 баев„ 2016
 *      Author: michael
 */


#include "auxiliaryfunc.h"

#include <stdio.h>
#include <stdlib.h>

#include "SPPoint.h"


void writefeats(FILE* fw,SPPoint* temppoint,int numOfFeats){

	int dex = spPointGetIndex(temppoint[0]);//all the image features have the same index
	char dexstring[1024]; //TODO check if needed more than that or less or doesn't matter
	fputs("i\n",fw);
	itoa(dex,dexstring,10);
	fputs(dexstring,fw);
	fputs("\n",fw);

	int dim = spPointGetDimension(temppoint[0]); //all the image features have the same dimension
	char dimstring[1024];
	fputs("d\n",fw);
	itoa(dim,dimstring,10);
	fputs(dimstring,fw);
	fputs("\n",fw);

	char nofstring[1024]; //writing number of feats for this image
	fputs("nof\n",fw);
	itoa(numOfFeats,nofstring,10);
	fputs(nofstring,fw);
	fputs("\n",fw);


	int i,j;

	for (j = 0; j < numOfFeats ; ++j) { //feature = SPPoint, then for each SPPoint
		for (i = 0; i < dim; ++i) {
			char numstring[1024];
			sprintf(numstring,"%f",spPointGetAxisCoor(temppoint[j],i));
			fputs(numstring,fw);
			fputs("\n",fw);
		}
	}
}

SPPoint* getfeats(FILE* fr,int* tempdir){
	int dim;
	int index;
	char templine[1024];

	fgets(templine,1024,fr);//read "i"
	fgets(templine,1024,fr);//read index of SPPoint
	index = atoi(templine);
	fgets(templine,1024,fr);//read "n"
	fgets(templine,1024,fr);//read dim of SPPoint
	dim = atoi(templine);
	fgets(templine,1024,fr);//read "nof"
	fgets(templine,1024,fr);//read total number of features
	*tempdir = atoi(templine);
	double arr[dim];

	SPPoint* ans = (SPPoint*)malloc(sizeof(SPPoint)*(*tempdir));

	int i,j;
	for (j = 0; j < (*tempdir); ++j) {
		for (i = 0; i < dim; ++i) { //fill arr
			fgets(templine,1024,fr);
			arr[i] = atof(templine);
		}
		ans[j] = spPointCreate(arr,dim,index);
	}
	return ans;
}

/*
 * tester for auxilary functions - working!!!!
 *
 * int main(){

	FILE* fw = fopen("checkingwritefeats.txt","w");
	double data[3] = {15.5,16.2,17.3};
	double data1[3] = {5.5,100.6,13.2};
	double data2[3] = {1.0,5.6,30.0};
	int numoffeats = 3;
	SPPoint arr[3];
	SPPoint* arr1;
	arr[0] = spPointCreate(data,3,5);
	arr[1] = spPointCreate(data1,3,5);
	arr[2] = spPointCreate(data2,3,5);
	writefeats(fw,arr,numoffeats);
	FILE* fr = fopen("checkingreadfeats.txt","r");
	arr1 = getfeats(fr,3);
	int i;
	for (i = 0; i < 3; ++i) {
		printf("point dex: %d\npoint dim: %d\n",spPointGetIndex(arr1[i]),spPointGetDimension(arr1[i]));
		double a = spPointGetAxisCoor(arr1[i],0);
		double b = spPointGetAxisCoor(arr1[i],1);
		double c = spPointGetAxisCoor(arr1[i],2);
		printf("%f %f %f\n",a,b,c);
	}
	return 1;
}*/
