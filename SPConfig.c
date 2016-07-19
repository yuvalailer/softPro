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


