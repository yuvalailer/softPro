/*
 * auxiliaryfunc.h
 *
 *  Created on: 23 баев„ 2016
 *      Author: michael
 */

#ifndef SOFTPRO_AUXILIARYFUNC_H_
#define SOFTPRO_AUXILIARYFUNC_H_

#include <stdio.h>
#include <stdlib.h>

#include "SPPoint.h"

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



#endif /* SOFTPRO_AUXILIARYFUNC_H_ */
