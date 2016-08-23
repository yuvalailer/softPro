/*
 * auxiliaryfunc.h
 *
 *  Created on: 23 баев„ 2016
 *      Author: michael
 */

#ifndef SOFTPRO_AUXILIARYFUNC_H_
#define SOFTPRO_AUXILIARYFUNC_H_

#include <stdio.h>

#include "SPPoint.h"

/*
 * the functions gets SPPoint and a file writer and writes the img5.feats file from the feats.
 * relevant only to extraction mode in main function
 * @param  fw - a file writer, temppoint - a SPPoint containing the feats to be written into fw.
 *
 */

void writefeats(FILE* fw,SPPoint* temppoint);


#endif /* SOFTPRO_AUXILIARYFUNC_H_ */
