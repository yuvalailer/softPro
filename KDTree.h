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
 has the next fields:
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
 *builds KDTree from SPPoints (feats) array. according to the system configuration.
 *builds free's at the end not needed arr because we make a copy
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

int FindMedian(SPKDArray* array,int splitcord);

/*
 * frees all allocation of memory recursivly
 * at reaching a leaf frees its sppoint also
 * @param - head- the current node to free
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

/*
 * envelope function.
 * the function returns a SPBPQueue containing the indexes of the 'num' closest SPPoints found in the KDTreeNode head.
 * @param - head - the KDTree head node whice we search
 * @param - point - the SPPoint we want to find the 'num' closest SPPoints
 * @param - num - how many closest SPPoints do we want to find + maxsize of SPBPQueue returned
 * @return - SPBPQueue containing the indexes of the 'num' closest SPPoints found in the KDTreeNode head.
 */

SPBPQueue KDTreeSearch(KDTreeNode* head,SPPoint point, int num);

/*
 * prints the Kdtree inserted: nodes + at what level, leafs + level + indexes at in-order
 * recursive function
 * @param - curr - the current node visiting to print
 * @param - level - our current depth in the tree
 */

void KDTreePrint(KDTreeNode* curr,int level);

/*
 * getter function to dim field at KDTreeNode
 * @param - node - the node from which to obtain the field dim
 * @return - int - the dim of the KDTreeNode node.
 */

int KDTreeGetDim(KDTreeNode* node);

/*
 * getter function to val field at KDTreeNode
 * @param - node - the node from which to obtain the field val
 * @return - double - the val of the KDTreeNode node.
 */

int KDTreeGetVal(KDTreeNode* node);

/*
 * a function which decides at each recursive call of func RecTreeBuild, which coordinate
 * do we split with the SPKDArray given
 * @param - splitm - the split method enum of config decided at boot of program
 * @param - i - in case of INCREMENTAL build, our current split coordinate
 * @param - arr - the SPKDArray to which in case of MAX_SPREAD mode we get our max spred.
 * @return - int - our splitting coordinate- in range (0,arr->rows), default: MAX_SPREAD
 */

int SplitDecide(method splitm,int i,SPKDArray* arr);


#endif /* KDTREE_H_ */
