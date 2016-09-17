/*
 * auxiliaryfunc.h
 *
 *  Created on: 23 ����� 2016
 *      Author: michael
 */

#ifndef AUXILIARYFUNC_H_
#define AUXILIARYFUNC_H_

#include "SPPoint.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
/*
 * the functions gets SPPoint array and a file writer and writes the img5.feats file from the feats.
 * relevant only to extraction mode in main function
 * @param  fw - a file writer, temppoint - a SPPoint array containing the feats to be written into fw.
 *
 */

void writefeats(FILE* fw,SPPoint* temppoint,int numOfFeats);

/*
 * the function reads *.feats file given by fr and returns the feats (SPPoint array)
 * that the file represents.
 * relevant only to non - extraction mode in main function
 * @param  fr - a file reader, size - number of feats to extract
 * tempdir - a pointer to where number of features extracted will be saved
 * @return - SPPoint* - the array of features for the image
 *
 */

SPPoint* getfeats(FILE* fr,int* tempdir);

/*
 * the function orders indexes of most hit images into winners all other places in winners not filled are -1;
 * @param - hits an array containing in index i the number of hits for image i
 * @param winners an array containing indexes of images by order of most hits
 * @param hitssize size of hits array
 * @param winnerssize size of winners array
 */

void calculatewinners(int* winners,int* hits,int hitssize,int winnerssize);

char* itoa1(int num);

void DirectoryDestroy(SPPoint** arr,int* num,int rows);

char* LoggerMSGtoString(SP_LOGGER_MSG msg);


#endif /* SOFTPRO_AUXILIARYFUNC_H_ */
