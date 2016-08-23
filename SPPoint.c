/*
 * SPPoint.c

 *
 *  Created on: 19 במאי 2016
 *      Author: michael
 */

#include "SPPoint.h"
#include <assert.h>
#include <stdlib.h>


struct sp_point_t {

	double* data;
	int dim;
	int index;

};

SPPoint spPointCreate(double* data, int dim, int index) {
	if((dim<=0)||(data == NULL)||(index<0)){ //TODO check if need to take back
		return NULL;
	}
	struct sp_point_t *point = (struct sp_point_t*) malloc(sizeof(struct sp_point_t));
	point->data = (double*) malloc(sizeof(double) * dim);
	if (point == NULL) {
		return NULL;
	}
	point->dim = dim;
	point->index = index;
	int i;
	for ( i = 0; i < dim; i++) {
		(point->data)[i] = data[i];
	}
	return point;
}

SPPoint spPointCopy(SPPoint source){
	assert(source != NULL);
	SPPoint newOne = spPointCreate(source->data,source->dim,source->index);
	return newOne;
}

void spPointDestroy(SPPoint point){
	if(point != NULL){
		free(point->data);
		free(point);
	}
}


int spPointGetDimension(SPPoint point){
	assert(point != NULL);
	return(point->dim);
}


int spPointGetIndex(SPPoint point){
	assert(point != NULL);
	return(point->index);
}

double spPointGetAxisCoor(SPPoint point, int axis){
	assert((point!=NULL) && (axis < point->dim));
	return point->data[axis];
}

double spPointL2SquaredDistance(SPPoint p, SPPoint q){
	assert((p!=NULL)&&(q!=NULL )&&( p->dim == q->dim));
	double sum = 0;
	double tmp;
	int i;
	for(i =0 ; i < p->dim ; i++){
		tmp = (spPointGetAxisCoor(p, i)-spPointGetAxisCoor(q, i));
		sum += (tmp*tmp);
	}
	return sum;
}

double* getDat(SPPoint point) { //TODO yuval: deacler header
	double* dat = point->data;
	return dat;
}


