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
#include <assert.h>

typedef enum {RANDOM, MAX_SPREAD,INCREMENTAL} method;


struct sp_config_t{ //already a pointer!!!! SPConfig
	char* spImagesDirectory;
	char* spImagesPrefix;
	char* spImagesSuffix;
	int spNumOfImages;
	int spPCADimension;
	char* spPCAFilename;
	int spNumOfFeatures;
	bool spExtractionMode;
	int spNumOfSimilarImages;
	method spKDTreeSplitMethod;
	int spKNN;
	bool spMinimalGUI;
	int spLoggerLevel;
	char* spLoggerFilename;
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
			*msg = SP_CONFIG_INVALID_ARGUMENT; //TODO un-specified answer in this case.. send an email to moab.
		} else {
			*msg = SP_CONFIG_SUCCESS;
		}
		return ans; // retrun an int. to be change if needed in the function.
	}
}

void trim(char*s){ //TODO add description and check if it is o.k. changes string in-place
	int len = strlen(s);
	int i=0;
	int cnt = 0;
	char temp = ' ';
	while(temp == ' '){
		temp = *(s+i);
		if (temp == ' '){
			cnt++;
			i++;
		}
	}
	for (i=0;i<len;i++){ // shift all left by cnt
		*(s+i)=*(s+i+cnt);
	}
	len = strlen(s);
	i=0;
	cnt = 0;
	temp = ' ';
	while(temp == ' '){
		temp = *(s+len-1 -i);
		if (temp == ' '){
			cnt++;
			i++;
		}
	}
	*(s+len-cnt) = '\0'; //trim from the right
}

bool contains(char* s,char c){ // TODO func description?
	int len = strlen(s);
	int i=0;
	for (i=0;i<len;i++){
		if (*(s+i)== c){
			return true;
		}
	}
	return false;
}

void splitmid(char* s,char* left,char* right){ // return  left and right strings after trimming
	int i=0;
	while(*(s+i) != '#'){ //fill left
		*(left+i) = *(s+i);
		i++;
	}
	*(left+i+1) = '\0'; //end left
	trim(left);
	i++; //skip # to fill right
	int j = 0;
	while (*(s+i)!='\0'){
		*(right+j) = *(s+i);
		i++;
		j++;
	}
	*(right+j+1) = '\0'; //end right
	trim(right);
}

bool insertconfig(SPConfig config,char* param,char* val){
	if(strcmp(param,"spImagesDirectory")){
		config->spImagesDirectory = val; //TODO how to check that image directory is ok?
		return true;
	}
	else if(strcmp(param,"spImagesPrefix")){
		config->spImagesPrefix = val;
		return true;
	}
	else if(strcmp(param,"spImagesSuffix")){
		if ((!strcmp(val,".jpg"))&&(!strcmp(val,".png"))&&(!strcmp(val,".bmp"))&&(!strcmp(val,".gif"))){
			return false;
		}
		config->spImagesSuffix = val;
		return true;
	}
	else if(strcmp(param,"spNumOfImages")){
		int num = atoi(val);//TODO check if needed to check suffix of "556asd" because would result in 556.
		if (num>0){
			config->spNumOfImages = num;
			return true;
		}
		return false;
	}
	else if(strcmp(param,"spPCADimension")){
		int num = atoi(val);//TODO check if needed to check suffix of "556asd" because would result in 556.
		if ((10<=num)&&(num<=128)){
			config->spPCADimension = num;
			return true;
		}
		return false;
	}
	else if(strcmp(param,"spPCAFilename")){
		config->spPCAFilename = val;
		return true;
	}
	else if(strcmp(param,"spNumOfFeatures")){
		int num = atoi(val);//TODO check if needed to check suffix of "556asd" because would result in 556.
		if (0<num){
			config->spNumOfFeatures = num;
			return true;
		}
		return false;
	}
	else if(strcmp(param,"spExtractionMode")){
		if(strcmp(val,"true")){
			config->spExtractionMode = true;
			return true;
		}
		else if(strcmp(val,"false")){
			config->spExtractionMode = false;
			return true;
		}
		return false;
	}
	else if(strcmp(param,"spNumOfSimilarImages")){
		int num = atoi(val);//TODO check if needed to check suffix of "556asd" because would result in 556.
		if (0<num){
			config->spNumOfSimilarImages = num;
			return true;
		}
		return false;
	}
	else if(strcmp(param,"spKDTreeSplitMethod")){
		if(strcmp(val,"RANDOM")){
			config->spKDTreeSplitMethod = RANDOM;
			return true;
		}
		else if(strcmp(val,"MAX_SPREAD")){
			config->spKDTreeSplitMethod = MAX_SPREAD;
			return true;
		}
		else if(strcmp(val,"INCREMENTAL")){
			config->spKDTreeSplitMethod = INCREMENTAL;
			return true;
		}
		return false;
	}
	else if(strcmp(param,"spKNN")){
		int num = atoi(val);//TODO check if needed to check suffix of "556asd" because would result in 556.
		if (0<num){
			config->spKNN = num;
			return true;
		}
		return false;
	}
	else if(strcmp(param,"spMinimalGUI")){
		if(strcmp(val,"true")){
			config->spMinimalGUI = true;
			return true;
		}
		else if(strcmp(val,"false")){
			config->spMinimalGUI = false;
			return true;
		}
		return false;
	}
	else if(strcmp(param,"spLoggerLevel")){
		int num = atoi(val);//TODO check if needed to check suffix of "556asd" because would result in 556.
		if ((0<num)&&(num<5)){
			config->spLoggerLevel = num;
			return true;
		}
		return false;
	}
	else if(strcmp(param,"spLoggerFilename")){
		if(strcmp(val,"stdout")){
			config->spLoggerFilename = val;
			return true;
		}
		else{
			config->spLoggerFilename = "notstdout"; //TODO check meaning of what happens if value is not stdout.
			return true;
		}
	}
	return false;
}


SPConfig spConfigCreate(const char* filename, SP_CONFIG_MSG* msg){

	assert(msg != NULL);
	bool in;
	FILE* fp = fopen(filename,"r");
	SPConfig config = (SPConfig)malloc(sizeof(SPConfig)); //allocating memory and setting default values
	config->spImagesDirectory = "notset";
	config->spImagesPrefix = "notset";
	config->spImagesSuffix = "notset";
	config->spNumOfImages = 0;
	config->spPCADimension = 20;
	config->spPCAFilename = "pca.yml";
	config->spNumOfFeatures = 100;
	config->spExtractionMode = true;
	config->spMinimalGUI = false;
	config->spNumOfSimilarImages = 1;
	config->spKNN = 1;
	config->spKDTreeSplitMethod = MAX_SPREAD;
	config->spLoggerLevel = 3;
	config->spLoggerFilename = "stdout";
	char* line = (char*)malloc(sizeof(char)*1024);
	char param[1024];
	char val[1024];
	while(fgets(line,1024,fp)!= NULL){ //each time read a line only each line is at most 1024 (moab)
		trim(line);
		if(*line == '#'){ // if a comment than continue to next line
			continue;
		}
		splitmid(line,param,val);
		if ((contains(param,' '))||(contains(val,' '))){
			//TODO complete error message
			return NULL;
		}
		if(!(in = insertconfig(config,param,val))){
			//TODO complete error messege config fail
			return NULL;
		}
	}
	fclose(fp);
	if((strcmp(config->spImagesDirectory,"notset"))
			||(strcmp(config->spImagesPrefix,"notset"))
			||(strcmp(config->spImagesSuffix,"notset"))
			||(config->spNumOfImages == 0)){
		//TODO change mesege
		return NULL;
	}
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
	int ans;
	int filed = (config->spPCADimension); // enter the spPCADimension as int.
	ans = configUtills(filed,config,msg); // return value needs to be negative int. thus the additional if loop.
	if (ans == 0){
		return -1;
	} else {
		return ans; // TODO free ans?
	}
}
SP_CONFIG_MSG spConfigGetImagePath(char* imagePath, const SPConfig config,int index){
	//char* path;
	if(imagePath == NULL || config == NULL){
		return SP_CONFIG_INVALID_ARGUMENT;
	} else if (index>=config->spNumOfImages) {
		return SP_CONFIG_INDEX_OUT_OF_RANGE;
	} else {
		sprintf(imagePath, "%s%s%d%s",config->spImagesDirectory,config->spImagesPrefix,index,config->spImagesSuffix);
		//*imagePath = *path;
		return SP_CONFIG_SUCCESS;
		//TODO do we need to check the size of the file in this point?
	}
}


SP_CONFIG_MSG spConfigGetPCAPath(char* pcaPath, const SPConfig config){
	//char* path;
	if(pcaPath == NULL || config == NULL){
		return SP_CONFIG_INVALID_ARGUMENT;
	} else {
		sprintf(pcaPath, "%s%s",config->spImagesDirectory, config->spPCAFilename);
		//*pcaPath = *path;
		return SP_CONFIG_SUCCESS;
		//TODO do we need to check the size of the file in this point?
	}
}

void spConfigDestroy(SPConfig config){
	if (config != NULL) {
		free (config);
		// TODO - is this enugth? michael, what addishional filleds do you set in make?
	}
}



