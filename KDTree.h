/*
 * KDTree.h
 *
 *  Created on: 12 בספט׳ 2016
 *      Author: NMR
 */

#ifndef KDTREE_H_
#define KDTREE_H_
#define INVALID -1

#include "SPPoint.h"
#include "SPKDArray.h"
#include "SPConfig.h"
#include "SPBPriorityQueue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


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

typedef struct spKDTreeNode KDTreeNode;


/*
 *builds KDTree from SPPoints (feats) array. accoarding to the system configuration.
 *@param arr - the SPPoint array used to build the KDArray and with that the KDTree
 *@param size - the number of elements in arr
 *@param config - the system configuration file
 *@return a pointer to KDTree head node.
 */

KDTreeNode* InitTree(SPPoint* arr, int size, SPConfig config);

/*
 * finds the max spread coordinate according to the SPKDArray given
 * @param array - the SPKDArray given to find the max spread coordinate
 * @return the max spread coordinate
 */

int maxSpred(SPKDArray* array);

/*
 * builds recursively the KDTree by MAX_SPREAD split method
 * @param array - the SPKDArray from which it builds the tree and nodes
 * @return KDTreeNode
 */

KDTreeNode* RecTreeBuild(SPKDArray* array,int i,method splitm);


/*
 * finding median value with respect to the splitcord in the SPKDArray
 * @param array - the SPKDArray from which to find the median
 * @param splitcord - the coordinate which to find the median in array
 * @return the value of the median value with respect to the splitcord in the SPKDArray
 */

int findmedian(SPKDArray* array,int splitcord);

/*
 * frees all allocation of memory
 */

void KDTreeDestroy(KDTreeNode* head);

/*
 * Recursive function. meant to use the Tree structure to effectively
 * find the closets neighbors and fill the Queue.
 * works as dicribed in the pdf file added to the project
 * finfing a feature (SPPoint) k - Nearest Neighbors (closest in distance from the point).
 * @param curr - the head of the tree to search the point P k nearest neighbors.
 * @param P the query point
 * @param bpq - the SPBPQueue used to store the k nearest points.
 */

void kNearestNeighbors(KDTreeNode* curr , SPBPQueue bpq, SPPoint P);

SPBPQueue KDTreeSearch(KDTreeNode* head,SPPoint point, int num);

void KDTreePrint(KDTreeNode* curr,int level);

int KDTreeGetDim(KDTreeNode* node);

int KDTreeGetVal(KDTreeNode* node);

int SplitDecide(method splitm,int i,SPKDArray* arr);


#endif /* KDTREE_H_ */
