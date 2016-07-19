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

	string spImagesDirectory;
	string spImagesPrefix;
	string spImagesSuffix;
	int spNumOfImages;
	int spPCADimension;
	string spPCAFilename = "pca.yml";
	int spNumOfFeatures = 100;
	bool spExtractionMode = true;
	int spNumOfSimilarImages = 1;
	enum spKDTreeSplitMethod;
	int spKNN = 1;
	bool spMinimalGUI = false;
	int spLoggerLevel;
	string spLoggerFilename;
	spPCADimension = 20;
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


