/*
 * KDTree.h
 *
 *  Created on: 18 баев„ 2016
 *      Author: yuval
 */

#ifndef SOFTPRO_KDTREE_H_
#define SOFTPRO_KDTREE_H_

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "SPLogger.h"
#include "SPConfig.h"

/*A Kd-tree struct. used for sorting and matching the picturs to one
 another.
 has the next fileds:
 1- Dim = The splitting dimension
 2- Val = The median value of the splitting dimension
 3- Left = Pointer to the left subtree
 4- Right = Pointer to the right subtree
 5- Data = Pointer to a point (only if the current node is a leaf) otherwise this field value is NULL
 To initialize the kd-tree takes o(d * nLog(n)) time.

 based on the lecture on kd-trees.
 */

typedef struct spKdTreeNode spKdTreeNode;


#endif /* SOFTPRO_KDTREE_H_ */






