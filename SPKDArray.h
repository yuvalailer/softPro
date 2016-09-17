/*
 * KDArray.h
 *
 *  Created on: 15 баев„ 2016
 *      Author: NMR
 */

#ifndef SPKDARRAY_H_
#define SPKDARRAY_H_

#include "SPPoint.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>

struct sp_kdarray_t;

typedef struct sp_kdarray_t SPKDArray;

typedef struct splitkdarrtuple KDArrayTuple;

typedef struct sort_tuple SortTuple;

/**
 * Allocates a new SPKDArray from given data in arr and size.
 * the function creates a copy of the SPPoint* arr given at size of int size.
 * @param arr - an array of SPPoints.
 * @param - size - the size of arr.
 * @return - SPKDArray* - a pointer to the SPKDArray.
 */

SPKDArray* Init(SPPoint* arr, int size);

/**
 * splits the SPKDArray given into two SPKDArrays contained in KDArrayTuple*, with respect to the
 * coor coordinate at each SPPoint.
 * @param kdArr the SPKDArray to be split
 * @param coor - the coordinate from which to split the array to left or right
 * @return - KDArrayTuple* - a pointer to KDArrayTuple containing the left and right split.
 */

KDArrayTuple* Split(SPKDArray* kdArr, int coor);

/*
 * returns the number of cols of the SPKDArray*
 * @param kdArr - the SPKDArray* to return the number of cols value
 * @return int - the number of cols
 */

int SPKDArrayGetcol(SPKDArray* kdArr);

/*
 * returns the number of rows of the SPKDArray* matrix
 * or dimension of each SPPoint in the pointsarr of SPKDArray (same value representing 2 things)
 * @param kdArr - the SPKDArray to return the number of rows value
 * @return int - the number of rows
 */

int SPKDArrayGetrows(SPKDArray* kdArr);

/*
 * returns the SPPoint array of the SPKDArray*
 * @param kdArr - the SPKDArray to return its SPPoint array
 * @return SPPoint* the SPPoint array of the SPKDArray
 */

SPPoint* Getpointsarray(SPKDArray* kdArr);

/*
 * returns the mat field of the SPKDArray*
 * @param kdArr - the SPKDArray* to return its mat field
 * @return int** the mat field of the SPKDArray*
 */

int** GetMat(SPKDArray* kdArr);

/*
 * returns the left pointer of the KDArrayTuple (pointer to a SPKDArray)
 * @param tup - the KDArrayTuple* to return its left SPKDArray*
 * @return SPKDArray* the pointer to the left SPKDArray
 */

SPKDArray* KDArrayTupleGetleft(KDArrayTuple* tup);

/*
 * returns the right pointer of the KDArrayTuple (pointer to a SPKDArray)
 * @param tup - the KDArrayTuple* to return its right SPKDArray*
 * @return SPKDArray* the pointer to the right SPKDArray
 */

SPKDArray* KDArrayTupleGetright(KDArrayTuple* tup);

/*
 * Destroys the tuples used to create the SPKDArray in function init
 * SortTuple is a temporary object created inside init of SPKDArray
 * @param - tup - a SortTuple* array containing SortTuple's to Destroy
 * @param - size - the array size
 */

void SortTupleDestroy(SortTuple* tup,int size);

/*
 * Destroys SPKDArray
 * @param - arr - SPKDArray pointer to be freed.
 */

void KDArrayDestroy(SPKDArray* arr);

/*
 * Destroys the KDArrayTuple and its two SPKDArray's inside using
 * KDArrayDestroy on both left and right
 * @param -  tup - a pointer to KDArrayTuple which to destroy its values
 */

void KDArrayTupleDestroy(KDArrayTuple* tup);

#endif /* SPKDARRAY_H_ */
