/*
 * KDTree.c
 *
 *  Created on: 18 баев„ 2016
 *      Author: yuval
 */

#include "KDTree.h"
#include "SPKDArray.h"
#include "SPPoint.h"

// making a Tree Node struct

typedef struct spTreeNode spTreeNode;
struct spTreeNode {
	int Dim; // The splitting dimension
	int Val; // The median value of the splitting dimension
	spTreeNode * Left; // Pointer to the left subtree
	spTreeNode * Right; // Pointer to the right subtree
	SPPoint* Data; // Pointer to a point (only if the current node is a leaf) otherwise this field value is NULL
};

spKdTreeNode Init(SPPoint* arr, int size){
	spKdTreeNode ans = (spKdTreeNode)malloc(sizeof(spKdTreeNode));
	SPKDArray array = init(arr,size);

}





