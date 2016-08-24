/*
 * KDTree.h
 *
 *  Created on: 18 баев„ 2016
 *      Author: yuval
 */

#ifndef SOFTPRO_KDTREE_H_
#define SOFTPRO_KDTREE_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "SPPoint.h"
#include "SPKDArray.h"
#include "SPConfig.h"

/*
 * A Kd-tree struct. used for sorting and matching the picturs to one
 another.
 has the next fileds:
 1- Dim = The splitting dimension
 2- Val = The median value of the splitting dimension
 3- Left = Pointer to the left subtree
 4- Right = Pointer to the right subtree
 5- Data = Pointer to a point (only if the current node is a leaf) otherwise this field value is NULL
 To initialize the kd-tree takes o(d * nLog(n)) time.

 based on the lecture on kd-trees.
 */

typedef struct spTreeNode* KDTreeNode;

/*
 *builds KDTree from SPPoints (feats) array. accoarding to the system configuration.
 *@param arr - the SPPoint array used to build the KDArray and with that the KDTree
 *@param size - the number of elements in arr
 *@param config - the system configuration file
 *@return a pointer to KDTree head node.
 */

KDTreeNode InitTree(SPPoint* arr, int size, SPConfig config);

/*
 * finds the max spread coordinate according to the SPKDArray given
 * @param array - the SPKDArray given to find the max spread coordinate
 * @return the max spread coordinate
 */

int maxSpred(SPKDArray array);

/*
 * builds recursively the KDTree by MAX_SPREAD split method
 * @param array - the SPKDArray from which it builds the tree and nodes
 * @return KDTreeNode
 */

KDTreeNode RecTree0(SPKDArray array);

/*
 * builds recursively the KDTree by RANDOM split method
 * @param array - the SPKDArray from which it builds the tree and nodes
 * @return KDTreeNode
 */

KDTreeNode RecTree1(SPKDArray array);

/*
 * builds recursively the KDTree by INCREMENTAL split method
 * @param array - the SPKDArray from which it builds the tree and nodes
 * @param i - the next coordinate which to split to next level of the tree
 * @return KDTreeNode
 */

KDTreeNode RecTree2(SPKDArray array,int i);

/*
 * finding median value with respect to the splitcord in the SPKDArray
 * @param array - the SPKDArray from which to find the median
 * @param splitcord - the coordinate which to find the median in array
 * @return the value of the median value with respect to the splitcord in the SPKDArray
 */

int findmedian(SPKDArray array,int splitcord);

/*
 * frees all allocation of memory
 */

void KDTreeDestroy(KDTreeNode head);

#endif /* SOFTPRO_KDTREE_H_ */






