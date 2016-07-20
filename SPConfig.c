/*
 * SPConfig.c
 *
 *  Created on: 19 αιεμι 2016
 *      Author: michael ozeri & yuval ailer
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

};

/*
 * a utill function. made to avoid code copying in all the next
 * functions.
 * is an internal tool, makes asserts act.
 */

int configUtills (int filed, const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg != NULL);
	int ans; // used in configutills only.
		if (config == NULL){ // bad input;
			ans = 0;
			*msg = SP_CONFIG_INVALID_ARGUMENT;
		} else { // config is good.
			ans = filed;
			if(filed == 0){ // what is the EXtract mode?
				*msg = SP_CONFIG_INVALID_ARGUMENT; //TODO un-specified anser in this case.. send an email to moab.
			} else {
				*msg = SP_CONFIG_SUCCESS;
			}
		return ans; // retrun an int. to be change if needed in the function.
}

SPConfig spConfigCreate(const char* filename, SP_CONFIG_MSG* msg){

	assert(msg != NULL);
	FILE* fp = fopen(filename,"r");
	char temp;
	char* field;
	int fk = 0; //field current fill pointer
	char* value;
	int vk = 0; //value current fill pointer
	int mode = 0; // awaiting read mode for next char, new line(0), fieldname(1) , value(3), =(2),comment(4)
	SPConfig config = (SPConfig)malloc(sizeof(SPConfig));
	bool end = true;
	while((temp=fgetc(fp))!= EOF){
		if (mode == 4){ // reading a comment from file
			if (temp != "\n"){
				continue;
			}else{
				fk = 0;
				vk = 0;
				mode = 0;
			}
		}
		else if (mode == 0){
			if (temp == '#'){
				mode = 4;
				continue;
			}else if (temp == ' '){
				continue;
			}else if (temp != "\n"){
				*(field + fk) = temp;
				fk++;
				mode = 1;
			}else{
				continue;
			}

		}else if (mode==1){


		}else if(mode==2){

		}else{

		}
	}
	fclose(fp);
	return config;
}

bool spConfigIsExtractionMode(const SPConfig config, SP_CONFIG_MSG* msg){
	int filed = (int)(config->spExtractionMode); // enter the exc_mode as int.
	return (bool)configUtills(filed,config,msg);
}

bool spConfigMinimalGui(const SPConfig config, SP_CONFIG_MSG* msg){
	int filed = (int)(config->spMinimalGUI); // enter the MinimalGUI_mode as int.
	return (bool)configUtills(filed,config,msg);

}
int spConfigGetNumOfImages(const SPConfig config, SP_CONFIG_MSG* msg){
	int filed = (config->spNumOfImages); // enter the NumOfImages_mode as int.
	return configUtills(filed,config,msg);
}

int spConfigGetNumOfFeatures(const SPConfig config, SP_CONFIG_MSG* msg){
	int filed = (config->spNumOfFeatures); // enter the NumOfFeatures_mode as int.
	return configUtills(filed,config,msg);
}

int spConfigGetPCADim(const SPConfig config, SP_CONFIG_MSG* msg){

}

SP_CONFIG_MSG spConfigGetImagePath(char* imagePath, const SPConfig config,int index){
	char* path;
	if(imagePath == NULL || config == NULL){
		return SP_CONFIG_INVALID_ARGUMENT;
	} else if (index>=config->spNumOfImages) {
		return SP_CONFIG_INDEX_OUT_OF_RANGE;
	} else {
		sprintf(path, "%s%s%d%s",config->spImagesDirectory,config->spImagesPrefix,index,config->spImagesSuffix);
		if(sizeof(imagePath) >= sizeof(path )) { //TODO is the imagepath as big as the image?
			*imagePath = *path; //TODO add returns and act.
		}
	}


}

}

SP_CONFIG_MSG spConfigGetPCAPath(char* pcaPath, const SPConfig config){

}

void spConfigDestroy(SPConfig config){

}


