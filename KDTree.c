/*
 * KDTree.c
 *
 *  Created on: 18 баев„ 2016
 *      Author: yuval ailer & michael ozeri
 */

#include "KDTree.h"
#include "SPConfig.h"
#define INVALID -1;

struct spTreeNode {
	int dim;
	int val;
	KDTreeNode left ;
	KDTreeNode right;
	SPPoint data;
};


int KDTreeGetDim(KDTreeNode node){
	int a = node->dim;
	return a;
}

int KDTreeGetVal(KDTreeNode node){
	int a = node->val;
	return a;
}

int maxSpred(SPKDArray array){
	int dim = Getrows(array);
	int size = Getcol(array);
	double max = 0;
	int maxcor = 0;
	int i;
	SPPoint* temparr = Getpointsarray(array);
	int** mat = GetMat(array);
	double data1;
	double data2;
	for(i = 0;i < dim;i++){ // O(d) to find max spread coordinate
		data1 = spPointGetAxisCoor((temparr[mat[i][0]]),i);
		data2 = spPointGetAxisCoor((temparr[mat[i][size-1]]),i);
		if((data2-data1)>max){
			max = data2-data1;
			maxcor = i;
		}
	}
	return maxcor;
}

int findmedian(SPKDArray array,int splitcord){
	int median;
	int size = Getcol(array);
	median = spPointGetAxisCoor((Getpointsarray(array))[(GetMat(array))[splitcord][size/2]],splitcord);
	return median;
}

KDTreeNode RecTree0(SPKDArray array){
	int splitcord = maxSpred(array); // O(d)
	KDTreeNode ans = (KDTreeNode)malloc(sizeof(KDTreeNode));
	if(Getcol(array) == 1){
		ans->dim = INVALID;
		ans->val = INVALID;
		ans->data = spPointCopy(Getpointsarray(array)[0]);
		ans->left = NULL;
		ans->right = NULL;
		return ans;
	}
	ans->dim = splitcord;
	ans->val = findmedian(array,splitcord);
//	ans->left = RecTree0(Split(array,splitcord)[0]);
//	ans->right = RecTree0(Split(array,splitcord)[1]);
//	ans->data = NULL;
	return ans;
}

KDTreeNode RecTree1(SPKDArray array){
	int splitcord = (rand()%Getrows(array));
	KDTreeNode ans = (KDTreeNode)malloc(sizeof(KDTreeNode));
	if(Getcol(array) == 1){
		ans->dim = INVALID;
		ans->val = INVALID;
		ans->data = spPointCopy(Getpointsarray(array)[0]);
		ans->left = NULL;
		ans->right = NULL;
		return ans;
	}
	ans->dim = splitcord;
	ans->val = findmedian(array,splitcord);
	ans->left = RecTree0(Split(array,splitcord)[0]);
	ans->right = RecTree0(Split(array,splitcord)[1]);
	ans->data = NULL;
	return ans;
}

KDTreeNode RecTree2(SPKDArray array,int i){
	int splitcord = (i%Getrows(array));
	KDTreeNode ans = (KDTreeNode)malloc(sizeof(KDTreeNode));
	if(Getcol(array) == 1){ // stopping criteria for the recursive function. node is a leaf
		ans->dim = INVALID;
		ans->val = INVALID;
		ans->data = spPointCopy(Getpointsarray(array)[0]);
		ans->left = NULL;
		ans->right = NULL;
		return ans;
	}
	ans->dim = splitcord;
	ans->val = findmedian(array,splitcord);
	ans->left = RecTree0(Split(array,splitcord +1)[0]);
	ans->right = RecTree0(Split(array,splitcord + 1)[1]);
	ans->data = NULL;
	return ans;
}

KDTreeNode InitTree(SPPoint* arr, int size, SPConfig config){ // initializing a Tree by points array;
	int splitmethod = spConfigGetMethod(config); // Splitting the arrays by the method in the config file;
	SPKDArray array = Init(arr,size); // building the KDArray
	//each split method decided calls another recursive function to compute the kdtree
	if(splitmethod == 0){ //MAX_SPREAD
		return RecTree0(array);
	}
	else if(splitmethod == 1){ //RANDOM
		return RecTree1(array);
	}
	else{//INCREMENTAL
		return RecTree2(array,0);
	}
}
// end of init


void kNearestNeighbors(KDTreeNode curr , SPBPQueue bpq, SPPoint P){
	if (curr == NULL) {
		return; //TODO? see PDF/
	}
	if(curr->dim != NULL){ //TODO yuval: is this a good leaf check
		int distance = spPointL2SquaredDistance(curr->data,P);
		SPListElement elm = spListElementCreate(spPointGetIndex(curr->data),distance);
		spBPQueueEnqueue(bpq,elm);
		return;
	}
	double* data = (double*)getDat(P); // TODO yuval: is this the right p[] ment in the pdf?
	if(data[curr->dim] <= KDTreeGetVal(curr)){
		kNearestNeighbors(curr->left,bpq,P);
		if(!(spBPQueueIsFull(bpq)) || abs((curr->val) - data[curr->dim]) < spBPQueueGetMaxSize(bpq)){
			kNearestNeighbors(curr->right,bpq,P);
		}
	} else {
		kNearestNeighbors(curr->right,bpq,P);
		if(!(spBPQueueIsFull(bpq)) || abs((curr->val) - data[curr->dim]) < spBPQueueGetMaxSize(bpq)){
			kNearestNeighbors(curr->left,bpq,P);
		}
	}
}

/*
* envalop fuction. ment to pass the K parameter to the function.
* returns a queue with the K -NEAREST NEIGHBORs.
*/

SPBPQueue KDTreeSearch(KDTreeNode head,SPPoint point, int num){
	SPBPQueue bpq;
	bpq = spBPQueueCreate(num); // TODO yuval: need to know the size - is this the config or the tree?
	kNearestNeighbors(head,bpq,point);
	return bpq;
}


void KDTreeDestroy(KDTreeNode head){
	if(head->val == -1){
		free(head);
	}
	else{
		KDTreeDestroy(head->left);
		KDTreeDestroy(head->right);
		free(head);
	}
}


int main(){
	int size = 5;
	int dim = 2;
	SPPoint* arr = (SPPoint*)malloc(sizeof(SPPoint)*size);
	double a1[2]= {1.0,2.0};
	double b1[2] = {123.0,70.0};
	double c1[2] = {2.0,7.0};
	double d1[2] = {9.0,11.0};
	double e1[2]= {3.0,4.0};
	arr[0] = (spPointCreate(a1,dim,0));
	arr[1] = (spPointCreate(b1,dim,1));
	arr[2] = (spPointCreate(c1,dim,2));
	arr[3] = (spPointCreate(d1,dim,3));
	arr[4] = (spPointCreate(e1,dim,4));
	SP_CONFIG_MSG msg;
	SPConfig config = spConfigCreate("config.config",&msg);
//	KDTreeNode head = InitTree(arr,5,config);
//	KDTreeDestroy(head);
	printf("chellooo!!!!!!");
	return 1;
}









