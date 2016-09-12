#ifndef SPBPRIORITYQUEUE_H_
#define SPBPRIORITYQUEUE_H_
#include "SPListElement.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
/**
 * SP Bounded Priority Queue summary
 *
 */


/** type used to define Bounded priority queue **/
typedef struct sp_bp_queue_t* SPBPQueue;

/** type for error reporting **/
typedef enum sp_bp_queue_msg_t {
	SP_BPQUEUE_OUT_OF_MEMORY,
	SP_BPQUEUE_FULL,
	SP_BPQUEUE_EMPTY,
	SP_BPQUEUE_INVALID_ARGUMENT,
	SP_BPQUEUE_SUCCESS
} SP_BPQUEUE_MSG;

/**
 * creates a new spBPQueue.
 * @param maxSize - the maximum size of the new spBPQueue.
 * @return
 * the new spBPQueue allocated.
 * if the maxSize inserted is <= o then return NULL
 */
SPBPQueue spBPQueueCreate(int maxSize);

/**
 * creates a NEW copy of a given queue.
 * @param source the spBPQueue that the function copies.
 * @return
 * the new spBPQueue copy.
 * if((source == NULL)||(source->list==NULL)) the function returns NULL
 */
SPBPQueue spBPQueueCopy(SPBPQueue source);

/**
 * frees all memory allocation associated with the queue, checks if source is NULL before
 * @param source the spBPQueue that the function destroys.
 * @return
 * no return - void.
 */
void spBPQueueDestroy(SPBPQueue source);

/**
 * removes all the elements in the queue (meaning removing all elements in the queue's SPlist)
 * @param source the spBPQueue that the function clears.
 * @return
 * no return - void.
 */
void spBPQueueClear(SPBPQueue source);

/**
 * returns the number of elements currently in the queue
 * @param source the spBPQueue.
 * @return
 * int - current size of the spBPQueue inserted.
 * if source is NULL or source->list is NULL the function return -1
 */
int spBPQueueSize(SPBPQueue source);

/**
 * returns the maximum capacity of the queue
 * @param source the spBPQueue.
 * @return
 * int - maximum size of the spBPQueue inserted (field "maxsize" in spBPQueue)
 * if source = NULL then the function returns -1
 */
int spBPQueueGetMaxSize(SPBPQueue source);

/**
 * Inserts a NEW COPY element to the queue
 * the function first iterates to check where should the element be inserted then inserts it.
 * @param source - the spBPQueue, element - the element to be inserted to the spBPQueue.
 * @return
 * SP_BPQUEUE_MSG - According to if the element was inserted into the source->list.
 * SP_BPQUEUE_INVALID_ARGUMENT - if source = NULL or source->list = NULL.
 */
SP_BPQUEUE_MSG spBPQueueEnqueue(SPBPQueue source, SPListElement element);

/**
 * removes the element with the lowest value
 * @param source - the spBPQueue.
 * @return
 * SP_BPQUEUE_MSG - According to if the element was removed from the spBPQueue.
 * if the SPBPQueue is empty - return SP_BPQUEUE_EMPTY message
 */
SP_BPQUEUE_MSG spBPQueueDequeue(SPBPQueue source);

/**
 * returns a NEW COPY of the element with the lowest value
 * @param source - the spBPQueue.
 * @return
 * the element with the lowest value
 * if the SPBPQueue is empty or NULL - return NULL
 */
SPListElement spBPQueuePeek(SPBPQueue source);

/**
 * returns a NEW COPY of the element with the highest value
 * @param source - the spBPQueue.
 * @return
 * the element with the highest value
 */
SPListElement spBPQueuePeekLast(SPBPQueue source);

/**
 * returns the minimum value in the queue
 * @param source - the spBPQueue.
 * @return
 * the minimum value of the queue.
 */
double spBPQueueMinValue(SPBPQueue source);

/**
 * returns the maximum value in the queue
 * @param source - the spBPQueue.
 * @return
 * the max value of the queue.
 * -1.0 if the source or the list insie the source is NULL
 */
double spBPQueueMaxValue(SPBPQueue source);

/**
 * checks if the Queue is empty by checking if the field "size" equals zero.
 * @param source the spBPQueue that the function checks if is empty.
 * @return
 * true if the queue is empty
 * false otherwise
 * NULL if the source is NULL
 */
bool spBPQueueIsEmpty(SPBPQueue source);

/**
 * checks if the Queue is full by comparing the max size to the list size inside the SPBPQueue.
 * @param source the spBPQueue that the function checks if is full.
 * @return
 * true if the queue is full
 * false otherwise
 * NULL if the source is NULL
 */
bool spBPQueueIsFull(SPBPQueue source);

#endif
