/*
 * auxiliaryfunc.c
 *
 *  Created on: 23 баев„ 2016
 *      Author: michael
 */


#include "auxiliaryfunc.h"


void writefeats(FILE* fw,SPPoint temppoint){

	int dex = spPointGetIndex(temppoint);//insert index line
	char dexstring[1024]; //TODO check if needed more than that or less or doesn't matter
	fputs("i\n",fw);
	itoa(dex,dexstring,10);
	fputs(dexstring,fw);
	fputs("\n",fw);

	int dim = spPointGetDimension(temppoint);
	char dimstring[1024];
	fputs("d\n",fw);
	itoa(dim,dimstring,10);
	fputs(dimstring,fw);
	fputs("\n",fw);

	int i;

	for (i = 0; i < dim; ++i) {

		fputc(temppoint->data[i],fw);
	}


}
