/*
 * SPKDArray.c
 *
 *  Created on: 15 баев„ 2016
 *      Author: NMR
 */

#include "SPKDArray.h"

struct sp_kdarray_t {

	SPPoint* pointsarr;
	int size;

};

SPKDArray Init(SPPoint* arr, int size){

	SPKDArray ans = (SPKDArray)malloc(sizeof(SPKDArray));


	return ans;
}
