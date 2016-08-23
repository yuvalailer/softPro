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
/*chooseing the correct cordinate
 to split acording to the max_sperde method in the insraction file;
 */
int maxSpred(SPKDArray array){

	int size = Getrows(array);
	double max;
	int ans = 0;
	int i; // counter
	SPPoint* arr = Getpoints(array);
	int** mat = GetMat(array);
	double* data1;
	double* data2;

	for(i = 0;i<size;i++){ // filling temp with the values of max point - min point in all fetuars;
		data1 = getDat(arr[mat[i][size-1]]);
		data2 = getDat(arr[mat[i][0]]);

		if((data1[i] - data2[i]) < max){
			ans = i;
			max = (data1[i] - data2[i]);
		}
	}
	return ans;
}

/*
choose wich cor to aplit by acording to the
method given in config file.
 */

int chooseRec(SPKDArray array,int mune, int cor){
	return 1; // TODO yuval: change
//	switch (mune) {
//	case 1: // MAX_SPREAD //TODO yvual: change back to 0, and define the defult of the config create to 0.
//		return maxSpred(array);
//		break;
//	case 0: // RANDOM
//#define MAX_SPREAD = getcopl(array);
//		srand(time(NULL)); // TODO yuval: do we need to call this only once?
//		return rand();
//		break;
//	case 2: // INCREMENTAL
//		return (cor+1)%Getcol(array); // TODO yuval: is modulo syntax correct?
//		break;
//
//	default:
//		return 1; // TODO yuval: remove
//		break;
//	}
}
KDTreeNode RecTree(SPKDArray array, int mune, int i){
	KDTreeNode ans = (KDTreeNode)malloc(sizeof(KDTreeNode));
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
	ans->right = RecTree((Split((array),cord))[1],mune,cord);
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

int main(){

	int size = 5;
	int dim = 2;

	SPPoint* arr = (SPPoint*)malloc(sizeof(SPPoint)*size);

	double a1[2]= {1,2};
	double b1[2] = {123,70};
	double c1[2] = {2,7};
	double d1[2] = {9,11};
	double e1[2]= {3,4};

	arr[0] = (spPointCreate(a1,dim,0));
	arr[1] = (spPointCreate(b1,dim,1));
	arr[2] = (spPointCreate(c1,dim,2));
	arr[3] = (spPointCreate(d1,dim,3));
	arr[4] = (spPointCreate(e1,dim,4));
	SP_CONFIG_MSG msg;
	SPConfig config = spConfigCreate("config.config",&msg);
	//SPKDArray kdarr = Init(arr,size);
	KDTreeNode source = InitTree(arr,5,config);
	printf(" a - ok !! \n");

	int printer(KDTreeNode node){
		if(node == NULL){
			printf("--null--");
			return 0;

		} else {

			printf("node is: %d\n",getDat(node->data);
			return printf("--left node is: %d\n",printer(node->left));
			return printf("--right node is: %d\n",printer(node->right));

		}
	}

	printer(source);
	return 0;
}








