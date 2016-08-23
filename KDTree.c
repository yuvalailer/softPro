/*
 * KDTree.c
 *
 *  Created on: 18 баев„ 2016
 *      Author: yuval
 */

#include "KDTree.h"
#include <time.h>
#include <stdlib.h>

#define INVALID -1;
// making a Tree Node struct

struct spTreeNode {
	int dim; // The splitting dimension
	int val; // The median value of the splitting dimension
	KDTreeNode left; // Pointer to the left subtree
	KDTreeNode right; // Pointer to the right subtree
	SPPoint* data; // Pointer to a point (only if the current node is a leaf) otherwise this field value is NULL
};

int maxSpred(SPKDArray array){

	int size = Getrows(array);
	int* temp = (int*)malloc(sizeof(int)*size); // making a temp array for sorting.
	int ans;
	int i; // counter

	for(i = 0;i<size;i++){

	}
	return ans;
}

int chooseRec(SPKDArray array,int mune, int cor){
	switch (mune) {
	case 0: // MAX_SPREAD
		return maxSpred(array);
		break;
	case 1: // RANDOM
		srand(time(NULL)); // TODO yuval: do we need to call this only once?
		return rand()%Getcol(array);
		break;
	case 2: // INCREMENTAL
		return (cor+1)%Getcol(array); // TODO yuval: is modulo syntax correct?
		break;

	default:
		break;
	}
}
KDTreeNode RecTree(SPKDArray array, int mune, int i){
	KDTreeNode ans;
	int cord; // the cordinate to split by.
	cord = chooseRec(array,mune,i); // choose the cordinate with the coreect enum;
	if(Getcol(array) == 1){ // stopping criteria for the recursive function. node is a leaf
		ans->dim = 0;
		ans->val = INVALID;
		ans->data = Getpoints(array); //TODO yvual: isnt * the right definition?
		ans->left = NULL;
		ans->right = NULL;
		return ans;
	} // recursive call

	ans->left = RecTree((Split((array),cord))[0],mune,cord);
	ans->left = RecTree((Split((array),cord))[1],mune,cord);
	return ans;
}


KDTreeNode InitTree(SPPoint* arr, int size, SPConfig config){ // initing a Tree by points array;
	int cord = 0;
	int mune = spConfigGetMethud(config); // Spiting the arrays by the method in the config file;
	KDTreeNode ans = (KDTreeNode)malloc(sizeof(KDTreeNode));
	SPKDArray array = Init(arr,size);

	ans = RecTree(array,mune,cord);
	return ans;
}





