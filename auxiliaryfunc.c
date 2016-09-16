/*
 * auxiliaryfunc.c
 *
 *  Created on: 23 баев„ 2016
 *      Author: michael
 */


#include "auxiliaryfunc.h"



void writefeats(FILE* fw,SPPoint* temppoint,int numOfFeats){

	int dex = spPointGetIndex(temppoint[0]);//all the image features have the same index
	char* dexstring;
	fputs("i\n",fw);
	dexstring = itoa1(dex);
	fputs(dexstring,fw);
	fputs("\n",fw);

	int dim = spPointGetDimension(temppoint[0]); //all the image features have the same dimension
	char* dimstring;
	fputs("d\n",fw);
	dimstring = itoa1(dim);
	fputs(dimstring,fw);
	fputs("\n",fw);

	char* nofstring; //writing number of feats for this image
	fputs("nof\n",fw);
	nofstring = itoa1(numOfFeats);
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
	int dir;
	char templine[1024];

	fgets(templine,1024,fr);//read "i"
	fgets(templine,1024,fr);//read index of SPPoint
	index = atoi(templine);
	fgets(templine,1024,fr);//read "n"
	fgets(templine,1024,fr);//read dim of SPPoint
	dim = atoi(templine);
	fgets(templine,1024,fr);//read "nof"
	fgets(templine,1024,fr);//read total number of features
	dir = atoi(templine);
	*tempdir = dir;
	double arr[dim];

	SPPoint* ans = (SPPoint*)malloc(sizeof(SPPoint)*(dir));

	int i,j;
	for (j = 0; j < (dir); ++j) {
		for (i = 0; i < dim; ++i) { //fill arr
			fgets(templine,1024,fr);
			arr[i] = atof(templine);
		}
		ans[j] = spPointCreate(arr,dim,index);
	}
	return ans;
}

void calculatewinners(int* winners,int* hits,int hitssize,int winnerssize){
	int max;
	int maxindex;
	int i = 0 ,j = 0;
	for (i = 0; i < winnerssize; ++i) {
		max = -1;
		maxindex = -1;
		for (j = 0; j < hitssize; ++j) {
			if(hits[j]>max){
				max = hits[j];
				maxindex=j;
			}
		}
		hits[maxindex] = -1;
		winners[i] = maxindex;
	}
}

char* itoa1(int num){

	static char str[32] = {0};
	int i = 30;
	for(; num && i ; --i, num /= 10){
		str[i] = "0123456789abcdef"[num % 10];
	}
	return &str[i+1];

}

void DirectoryDestroy(SPPoint** arr,int* num,int rows){
	int i;
	for (i = 0; i < rows; ++i) {
		SPPointArrayDestroy(arr[i],num[i]);
	}
	free(arr);
}

/*int main(){
	int a;
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
	arr1 = getfeats(fr,&a);
	int i;
	for (i = 0; i < 3; ++i) {
		printf("point dex: %d\npoint dim: %d\n",spPointGetIndex(arr1[i]),spPointGetDimension(arr1[i]));
		double a = spPointGetAxisCoor(arr1[i],0);
		double b = spPointGetAxisCoor(arr1[i],1);
		double c = spPointGetAxisCoor(arr1[i],2);
		printf("%f %f %f\n",a,b,c);
	}
	int hits[4] = {5,4,80,2};
	int winners[7] = {-1,-1,-1,-1,-1,-1,-1};
	calculatewinners(winners,hits,4,7);
	for (a = 0; a < 7; ++a) {
		printf("%d ",winners[a]);
	}
	return 1;
}*/
