/*
 * auxiliaryfunc.c
 *
 *  Created on: 23 баев„ 2016
 *      Author: michael
 */


#include "auxiliaryfunc.h"

void writefeats(FILE* fw,SPPoint* temppoint){

	int dex = spPointGetIndex(*temppoint);
	fputs("i\n",fw);
	fputs(dex,fw);
	int dim = spPointGetDimension(*temppoint);
	fputs("d\n",fw);
	fputs(dim,fw);




}
