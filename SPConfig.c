/*
 * SPConfig.c
 *
 *  Created on: 19 αιεμι 2016
 *      Author: michael
 */

#include <stdio.h>
#include <stdlib.h>
#include "SPConfig.h"
#include <stdbool.h>
#include <string.h>



struct sp_config_t{

	char* spImagesDirectory;
	char* spImagesPrefix;
	char* spImagesSuffix;
	int spNumOfImages;
	int spPCADimension;
	char* spPCAFilename;
	int spNumOfFeatures;
	bool spExtractionMode;
	int spNumOfSimilarImages;
	enum spKDTreeSplitMethod;
	int spKNN;
	bool spMinimalGUI;
	int spLoggerLevel;
	char* spLoggerFilename;
};



SPConfig spConfigCreate(const char* filename, SP_CONFIG_MSG* msg){
	assert(msg != NULL);



}

bool spConfigIsExtractionMode(const SPConfig config, SP_CONFIG_MSG* msg){

}

bool spConfigMinimalGui(const SPConfig config, SP_CONFIG_MSG* msg){

}

int spConfigGetNumOfFeatures(const SPConfig config, SP_CONFIG_MSG* msg){

}

int spConfigGetPCADim(const SPConfig config, SP_CONFIG_MSG* msg){

}

SP_CONFIG_MSG spConfigGetImagePath(char* imagePath, const SPConfig config,int index){

}

SP_CONFIG_MSG spConfigGetPCAPath(char* pcaPath, const SPConfig config){

}

void spConfigDestroy(SPConfig config){

}


