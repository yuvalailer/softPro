/*
 * SPBPriorityQueue.c
 *
 *  Created on: 19 במאי 2016
 *      Author: Michael ozeri & yuval ailer
 */

#include "SPBPriorityQueue.h"
#include "SPList.h"

struct sp_bp_queue_t {
	SPList list;
	int maxsize;
};

SP_BPQUEUE_MSG changeMSG(SP_LIST_MSG msg);

SP_BPQUEUE_MSG changeMSG(SP_LIST_MSG msg){
	switch(msg)
	{
	case (SP_LIST_SUCCESS): return SP_BPQUEUE_SUCCESS;
	break;
	case (SP_LIST_NULL_ARGUMENT): return SP_BPQUEUE_INVALID_ARGUMENT;
	break;
	case (SP_LIST_OUT_OF_MEMORY): return SP_BPQUEUE_OUT_OF_MEMORY;
	break;
	default : return SP_BPQUEUE_SUCCESS;
	}
}

SPBPQueue spBPQueueCreate(int maxSize){
	if(maxSize<=0){
		return NULL;
	}
	struct sp_bp_queue_t *queue = (struct sp_bp_queue_t*) malloc(sizeof(struct sp_bp_queue_t));
	SPList splist = spListCreate();
	queue->maxsize = maxSize;
	queue->list = splist;
	return queue;
}

SPBPQueue spBPQueueCopy(SPBPQueue source){

	if((source == NULL)||(source->list==NULL)){
		return NULL;
	}
	SPBPQueue newOne = spBPQueueCreate(source->maxsize);
	newOne->list = spListCopy(source->list);
	return newOne;
}

void spBPQueueDestroy(SPBPQueue source){
	if((source == NULL)){
		return;
	}
	spListDestroy(source->list);
	free(source);
}

void spBPQueueClear(SPBPQueue source){
	if((source == NULL)){
		return;
	}
	spListClear(source->list);
}

int spBPQueueSize(SPBPQueue source){
	if((source == NULL)){
		return -1;
	}
	return spListGetSize(source->list);
}

int spBPQueueGetMaxSize(SPBPQueue source){
	if((source == NULL)){
		return -1;
	}
	return source->maxsize;
}

SP_BPQUEUE_MSG spBPQueueEnqueue(SPBPQueue source, SPListElement element){
	if((source == NULL)||((source->list)==NULL)||element == NULL){
		return SP_BPQUEUE_INVALID_ARGUMENT;
	}
	double value = spListElementGetValue(element);
	int index =spListElementGetIndex(element);
	if ((index == -1.0)||(value == -1)){
		return SP_BPQUEUE_INVALID_ARGUMENT;
	}
	SP_LIST_MSG  msg;
	bool check = false;
	bool toobig = false;
	if (spBPQueueIsEmpty(source)){ //if queue is empty insert first
		msg = spListInsertFirst(source->list,element);
		return changeMSG(msg);
	}
	spListGetFirst(source->list); //start iterator at first place
	while(check == false){
		if (spListGetCurrent(source->list)==NULL){ // was spListGetLast(source->list) instead of NULL
			spListInsertLast(source->list,element);
			toobig = true;
			check=true;
		}
		else{
			if(value < spListElementGetValue(spListGetCurrent(source->list))){
				msg = spListInsertBeforeCurrent(source->list,element);
				check = true;
			}
			else if (value == spListElementGetValue(spListGetCurrent(source->list))){
				if (index <=spListElementGetIndex(spListGetCurrent(source->list))){
					msg = spListInsertBeforeCurrent(source->list,element);
					check = true;
				}
				else{
					spListGetNext(source->list);
				}
			}
			else{
				spListGetNext(source->list);
			}
		}
	}
	if((source->maxsize) < spListGetSize(source->list)){ //delete last node if too much
		spListGetLast(source->list);
		spListRemoveCurrent(source->list);
		if (toobig == true){
			return SP_BPQUEUE_FULL;
		}
	}
	return changeMSG(msg);
}

SP_BPQUEUE_MSG spBPQueueDequeue(SPBPQueue source){

	if ((source == NULL)||(spBPQueueSize(source)==-1)){
		return SP_BPQUEUE_INVALID_ARGUMENT;
	}
	SP_LIST_MSG  msg;
	if(spBPQueueSize(source)==0){ //if queue is empty return message that the list is empty
		return SP_BPQUEUE_EMPTY;
	}
	spListGetFirst(source->list);//restart iterator at first node
	msg = spListRemoveCurrent(source->list);//remove current = first node = lowest value
	return changeMSG(msg);
}

SPListElement spBPQueuePeek(SPBPQueue source){
	if(spBPQueueSize(source)== 0){ // if queue is empty return NULL
		return NULL;
	}
	return spListElementCopy(spListGetFirst(source->list));
	//return (spListGetFirst(source->list));
}

SPListElement spBPQueuePeekLast(SPBPQueue source){

	if((spBPQueueSize(source)== 0)){ // if queue is empty return NULL
		return NULL;
	}
	return spListElementCopy(spListGetLast(source->list));
	//return (spListGetLast(source->list));
}

double spBPQueueMinValue(SPBPQueue source){
	SPListElement element = spBPQueuePeek(source);
	float val = spListElementGetValue(element);
	spListElementDestroy(element);
	return val ;
}

double spBPQueueMaxValue(SPBPQueue source){
	SPListElement element = spBPQueuePeekLast(source);
	float val = spListElementGetValue(element);
	spListElementDestroy(element);
	return val;
}

bool spBPQueueIsEmpty(SPBPQueue source){
	if (source == NULL){
		return NULL;
	}
	if(spBPQueueSize(source) == 0){
		return true;
	}
	else{return false;}
}

bool spBPQueueIsFull(SPBPQueue source){
	if (source == NULL){
		return NULL;
	}
	if (source->maxsize == spBPQueueSize(source)){
		return true;
	}
	else{return false;}
}





