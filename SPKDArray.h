/*
 * KDArray.h
 *
 *  Created on: 15 баев„ 2016
 *      Author: NMR
 */

#ifndef SOFTPRO_SPKDARRAY_H_
#define SOFTPRO_SPKDARRAY_H_

#include "SPPoint.h"

struct sp_kdarray_t;

typedef struct sp_kdarray_t* SPKDArray;

/**
 * Allocates a new SPKDArray from given data in arr and size.
 *
 * TODO complete documentation of both functions
 *
 * @param arr - an array of SPPoints & size - its size
 * @assert //TODO - needed?
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
 * @param kdArr the kdarray to be splitted
 * @param coor - the coordinate from which to split the array to left or right
 * @return - array of two pointers to the left KDarray and right kdarray
 *
 */

SPKDArray* Split(SPKDArray kdArr, int coor);

/*
 * returns the number of cols of the SPKDArray
 * @param kdArr - the SPKDArray to return the #cols value
 * @return int - the number of cols
 */

int Getcol(SPKDArray kdArr);

/*
 * returns the number of rows of the SPKDArray matrix
 * @param kdArr - the SPKDArray to return the #rows value
 * @return int - the number of rows
 *
 */

int Getrows(SPKDArray kdArr);

/*
 * returns the SPPoint array of the SPKDArray
 * @param kdArr - the SPKDArray to return its SPPoint array
 * @return SPPoint* the copy of the SPPoint array of the SPKDArray
 *
 */

SPPoint* Getpointsarray(SPKDArray kdArr);



int** GetMat(SPKDArray kdArr);

#endif /* SOFTPRO_SPKDARRAY_H_ */
