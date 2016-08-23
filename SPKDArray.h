/*
 * KDArray.h
 *
 *  Created on: 15 баев„ 2016
 *      Author: NMR
 */

#ifndef SOFTPRO_SPKDARRAY_H_
#define SOFTPRO_SPKDARRAY_H_

#include<stdio.h>

#include<stdlib.h>

#include "SPPoint.h"

typedef struct sp_kdarray_t* SPKDArray;

/**
 * Allocates a new SPKDArray from given data in arr and size.
 *
 * TODO complete documentation of both functions
 *
 * @param
 * @assert
 * @return
 *
 */

SPKDArray Init(SPPoint* arr, int size);

/**
 * splits the SPKDArray given into two SPKDArrays with respect to the
 * coor coordinate at each point
 *
 *returns an array of 2 SPKDArray-s. left & right.
 *
 * TODO complete documentation
 *
 * @param
 * @assert
 * @return - array of two pointers
 *
 */

SPKDArray* Split(SPKDArray kdArr, int coor);

int Getcol(SPKDArray kdArr);

int Getrows(SPKDArray kdArr);

SPPoint* Getpoints(SPKDArray kdArr);

#endif /* SOFTPRO_SPKDARRAY_H_ */
