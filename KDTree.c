/*
 * KDTree.c
 *
 *  Created on: 12 בספט׳ 2016
 *      Author: NMR
 */

#include "KDTree.h"


struct spKDTreeNode{
	double val;
	int dim;
	KDTreeNode* left;
	KDTreeNode* right;
	SPPoint data;
};


int KDTreeGetDim(KDTreeNode* node){
	int a = node->dim;
	return a;
}

int KDTreeGetVal(KDTreeNode* node){
	int a = node->val;
	return a;
}

int maxSpred(SPKDArray* array){
	int dim = Getrows(array);
	int size = Getcol(array);
	if(size == 1){
		return 0;
	}
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
		if(abs(data2-data1)>max){
			max = abs(data2-data1);
			maxcor = i;
		}
	}
	return maxcor;
}

int findmedian(SPKDArray* array,int splitcord){
	int median;
	int size = Getcol(array);
	median = spPointGetAxisCoor((Getpointsarray(array))[(GetMat(array))[splitcord][size/2]],splitcord);
	return median;
}

KDTreeNode* RecTree0(SPKDArray* array){
	KDTreeNode* ans = (KDTreeNode*)malloc(sizeof(KDTreeNode));
	if(ans == NULL){
		return NULL;
	}
	if((Getcol(array) == 1)||(array == NULL)){
		ans->dim = INVALID;
		ans->val = INVALID;
		ans->data = spPointCopy(Getpointsarray(array)[0]);
		ans->left = NULL;
		ans->right = NULL;
		return ans;
	}
	int splitcord = maxSpred(array); // O(d)
	ans->dim = splitcord;
	ans->val = findmedian(array,splitcord);
	KDArrayTuple* splitarray = Split(array,splitcord);
	ans->left = RecTree0(kdtupgetleft(splitarray));
	ans->right = RecTree0(kdtupgetright(splitarray));
	ans->data = NULL;
	return ans;
}

KDTreeNode* RecTree1(SPKDArray* array){
	int splitcord = (rand()%Getrows(array));
	KDTreeNode* ans = (KDTreeNode*)malloc(sizeof(KDTreeNode));
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
	KDArrayTuple* splitarray = Split(array,splitcord);
	ans->left = RecTree1(kdtupgetleft(splitarray));
	ans->right = RecTree1(kdtupgetright(splitarray));
	ans->data = NULL;
	return ans;
}

KDTreeNode* RecTree2(SPKDArray* array,int i){
	int splitcord = (i%Getrows(array));
	KDTreeNode* ans = (KDTreeNode*)malloc(sizeof(KDTreeNode));
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
	KDArrayTuple* splitarray = Split(array,splitcord);
	ans->left = RecTree2(kdtupgetleft(splitarray),splitcord+1);
	ans->right = RecTree2(kdtupgetright(splitarray),splitcord+1);
	ans->data = NULL;
	return ans;
}

KDTreeNode* InitTree(SPPoint* arr, int size, SPConfig config){ // initializing a Tree by points array;
	method splitmethod = spConfigGetMethod(config); // Splitting the arrays by the method in the config file;
	SPKDArray* array = Init(arr,size); // building the KDArray
	if(array ==NULL){
		return NULL;
	}
	//each split method decided calls another recursive function to compute the KDTree
	switch(splitmethod){
	case MAX_SPREAD:
		return RecTree0(array);
		break;
	case RANDOM:
		return RecTree1(array);
		break;
	case INCREMENTAL:
		return RecTree2(array,0);
		break;
	default: //default to create tree by incremental
		return RecTree2(array,0);
	}
}



void kNearestNeighbors(KDTreeNode* curr , SPBPQueue bpq, SPPoint P){
	if (curr == NULL) {
		return; //TODO? see PDF/
	}
	if(curr->data != NULL){ // we are in a leaf
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
 * envelope function. meant to pass the K parameter to the function.
 * returns a queue with the K -NEAREST NEIGHBORs.
 */

SPBPQueue KDTreeSearch(KDTreeNode* head,SPPoint point, int num){
	SPBPQueue bpq;
	bpq = spBPQueueCreate(num);
	kNearestNeighbors(head,bpq,point);
	return bpq;
}


void KDTreeDestroy(KDTreeNode* head){
	if(head->val == -1){
		spPointDestroy(head->data);
		free(head);
	}
	else{
		if(head->left != NULL){KDTreeDestroy(head->left);}
		if(head->right != NULL){KDTreeDestroy(head->right);}
		free(head);
	}
}

void KDTreePrint(KDTreeNode* curr,int level){
	if(curr->val == -1){
		printf("reached a leaf!, index is: %d\n",spPointGetIndex(curr->data));
	}
	else{
		printf("reached Node, dim: %d, val: %f\n",curr->dim,curr->val);
		if(curr->left != NULL){KDTreePrint(curr->left,level+1);}
		if(curr->right != NULL){KDTreePrint(curr->right,level+1);}
	}
}

/*int main(){
	int size = 5;
	int dim = 2;
	SPPoint arr[size];
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
	SPConfig config = spConfigCreate("spcbir.config",&msg);
	KDTreeNode* head = InitTree(arr,size,config);
	KDTreePrint(head,0);
	KDTreeDestroy(head);
	spConfigDestroy(config);
	return 1;
}*/

