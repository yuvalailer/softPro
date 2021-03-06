/*
 * KDTree.c
 *
 *  Created on: 12 ����� 2016
 *      Author: michael ozeri & yuval ailer
 */

#include "KDTree.h"

struct spKDTreeNode{
	double val;
	int dim;
	KDTreeNode* left;
	KDTreeNode* right;
	SPPoint data;
};

int maxSpred(SPKDArray* array){
	int dim = SPKDArrayGetrows(array);
	int size = SPKDArrayGetcol(array);
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

int FindMedian(SPKDArray* array,int splitcord){
	int median;
	int size = SPKDArrayGetcol(array);
	median = spPointGetAxisCoor((Getpointsarray(array))[(GetMat(array))[splitcord][size/2]],splitcord);
	return median;
}

KDTreeNode* RecTreeBuild(SPKDArray* array,int i,method splitm){

	KDTreeNode* ans = (KDTreeNode*)malloc(sizeof(KDTreeNode));

	if(ans == NULL){
		spLoggerPrintError("could not malloc leaf!",__FILE__,__func__,__LINE__);
		return NULL;
	}

	if((SPKDArrayGetcol(array) == 1)){
		ans->dim = INVALID;
		ans->val = INVALID;
		ans->data = spPointCopy(Getpointsarray(array)[0]);
		ans->left = NULL;
		ans->right = NULL;
		return ans;
	}

	int splitcord = SplitDecide(splitm,i,array); // O(d)

	ans->dim = splitcord;
	ans->val = FindMedian(array,splitcord);

	KDArrayTuple* splitarray = Split(array,splitcord);

	ans->left = RecTreeBuild(KDArrayTupleGetleft(splitarray),splitcord+1,splitm);
	ans->right = RecTreeBuild(KDArrayTupleGetright(splitarray),splitcord+1,splitm);
	ans->data = NULL;

	KDArrayTupleDestroy(splitarray);

	return ans;
}


KDTreeNode* InitTree(SPPoint* arr, int size, SPConfig config){ // initializing a Tree by points array;
	method splitmethod = spConfigGetMethod(config); // Splitting the arrays by the method in the config file;
	SPKDArray* kdarr = Init(arr,size); // building the KDArray
	if(kdarr ==NULL){
		return NULL;
	}
	KDTreeNode* ans = RecTreeBuild(kdarr,0,splitmethod);
	KDArrayDestroy(kdarr); //free kdarr malloc'ed
	SPPointArrayDestroy(arr,size);
	return ans;
}



void kNearestNeighbors(KDTreeNode* curr , SPBPQueue bpq, SPPoint querypoint){
	if (curr == NULL) {
		return;
	}
	if(curr->data != NULL){ // we are in a leaf
		int distance = spPointL2SquaredDistance(curr->data,querypoint);
		SPListElement elm = spListElementCreate(spPointGetIndex(curr->data),distance);
		spBPQueueEnqueue(bpq,elm);
		spListElementDestroy(elm);
		return;
	}

	double* data = (double*)spPointGetData(querypoint);

	if(data[curr->dim] <= KDTreeGetVal(curr)){
		kNearestNeighbors(curr->left,bpq,querypoint);
		if(!(spBPQueueIsFull(bpq)) || (((curr->val) - data[curr->dim])*((curr->val) - data[curr->dim])) < (spListElementGetValue(spBPQueuePeekLast(bpq))) ){
			kNearestNeighbors(curr->right,bpq,querypoint);
		}
	}
	else{
		kNearestNeighbors(curr->right,bpq,querypoint);
		if(!(spBPQueueIsFull(bpq)) || (((curr->val) - data[curr->dim])*((curr->val) - data[curr->dim])) < (spListElementGetValue(spBPQueuePeekLast(bpq))) ){
			kNearestNeighbors(curr->left,bpq,querypoint);
		}
	}
}

SPBPQueue KDTreeSearch(KDTreeNode* head,SPPoint point, int size){
	SPBPQueue bpq;
	bpq = spBPQueueCreate(size);
	kNearestNeighbors(head,bpq,point);
	return bpq;
}


void KDTreeDestroy(KDTreeNode* head){
	if(head->data != NULL){
		spPointDestroy(head->data);
		free(head->left);
		free(head->right);
		free(head);
	} else {
		if(head->left != NULL){KDTreeDestroy(head->left);}
		if(head->right != NULL){KDTreeDestroy(head->right);}
		free(head->data);
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

void PrintQueue(SPBPQueue queue){
	int i = 0;
	while(!spBPQueueIsEmpty(queue)){
		printf("%d. %d \n",i,spListElementGetIndex(spBPQueuePeek(queue)));
		spBPQueueDequeue(queue);
		i++;
	}
}

int KDTreeGetDim(KDTreeNode* node){
	return node->dim;
}

int KDTreeGetVal(KDTreeNode* node){
	return node->val;
}

int SplitDecide(method splitm,int i,SPKDArray* arr){
	switch(splitm){
	case MAX_SPREAD:
		return maxSpred(arr);
	case RANDOM:
		return (rand()%SPKDArrayGetrows(arr));
	case INCREMENTAL:
		return (i%SPKDArrayGetrows(arr));
	default:
		return maxSpred(arr); //default returns MAX_SPREAD
	}
}



/*


int main(){

	//working with no leaks!! print tree has leak!!
	int size = 5;
	int dim = 2;
	SPPoint* sppointarr = (SPPoint*)malloc(sizeof(SPPoint)*size);

	double a1[2]= {1.0,2.0};
	double b1[2] = {123.0,70.0};
	double c1[2] = {2.0,7.0};
	double d1[2] = {9.0,11.0};
	double e1[2]= {3.0,4.0};

	sppointarr[0] = (spPointCreate(a1,dim,0));
	sppointarr[1] = (spPointCreate(b1,dim,1));
	sppointarr[2] = (spPointCreate(c1,dim,2));
	sppointarr[3] = (spPointCreate(d1,dim,3));
	sppointarr[4] = (spPointCreate(e1,dim,4));


	SP_CONFIG_MSG msg;
	SPConfig config = spConfigCreate("spcbir.config",&msg);

	KDTreeNode* head = InitTree(sppointarr,size,config);

	SPPointArrayDestroy(sppointarr,size);

	KDTreePrint(head,0);

	SPBPQueue queue = KDTreeSearch(head,sppointarr[0],4);
//	PrintQueue(queue); //has leaks because of peek

	spBPQueueDestroy(queue);
	KDTreeDestroy(head);
	spConfigDestroy(config);


	return 1;
}
 */

