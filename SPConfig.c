/*
 * SPConfig.c
 *
 *  Created on: 19 αιεμι 2016
 *      Author: michael ozeri & yuval ailer
 */

#include <stdlib.h>
#include "SPConfig.h"
#include <assert.h>
#include <ctype.h>

struct sp_config_t{ //already a pointer!!!! SPConfig
	char spImagesDirectory[1024];
	char spImagesPrefix[1024];
	char spImagesSuffix[1024];
	int spNumOfImages;
	int spPCADimension;
	char spPCAFilename[1024];
	int spNumOfFeatures;
	bool spExtractionMode;
	int spNumOfSimilarImages;
	method spKDTreeSplitMethod;
	int spKNN;
	bool spMinimalGUI;
	int spLoggerLevel;
	char spLoggerFilename[1024];
};

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
			//TODO change this part of the function according to the main function
		} else {
			*msg = SP_CONFIG_SUCCESS;
		}
	}
	return ans; // Return an int. to be change if needed in the function.
}

void trim(char*s){
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
	*(s+len-cnt) = '\0';
}


bool contains(char* s,char c){
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
	while(*(s+i) != '='){ //fill left
		*(left+i) = *(s+i);
		i++;
	}
	*(left+i) = '\0'; //end left
	trim(left);
	i++; //skip # to fill right
	int j = 0;
	while (*(s+i)!='\0'){
		if((*(s+i)=='\n')){
			break;
		}
		*(right+j) = *(s+i);
		i++;
		j++;
	}
	*(right+j) = '\0'; //end right
	trim(right);
}

bool allnum(char* s){
	int i=0;
	int len = strlen(s);
	char tmp;
	for(i=0;i<len;i++){
		tmp = *(s+i);
		if(!isdigit(tmp)){
			return false;
		}
	}
	return true;
}

bool insertconfig(SPConfig config,char* param,char* val){
	if(strcmp(param,"spImagesDirectory")==0){
		strcpy(config->spImagesDirectory,val);
		return true;
	}
	if(strcmp(param,"spImagesPrefix")==0){
		strcpy(config->spImagesPrefix,val);
		return true;
	}
	if(strcmp(param,"spImagesSuffix")==0){
		if ((!strcmp(val,".jpg"))&&(!strcmp(val,".png"))&&(!strcmp(val,".bmp"))&&(!strcmp(val,".gif"))){
			return false;
		}
		strcpy(config->spImagesSuffix,val);
		return true;
	}
	if(strcmp(param,"spNumOfImages")==0){
		if(!allnum(val)){//if val is not a string containing only numbers
			return false;
		}
		int num = atoi(val);
		if (num>0){
			config->spNumOfImages = num;
			return true;
		}
		return false;
	}
	if(strcmp(param,"spPCADimension")==0){
		if(!allnum(val)){//if val is not a string containing only numbers
			return false;
		}
		int num = atoi(val);
		if ((10<=num)&&(num<=128)){
			config->spPCADimension = num;
			return true;
		}
		return false;
	}
	if(strcmp(param,"spPCAFilename")==0){
		strcpy(config->spPCAFilename,val);
		return true;
	}
	if(strcmp(param,"spNumOfFeatures")==0){
		if(!allnum(val)){//if val is not a string containing only numbers
			return false;
		}
		int num = atoi(val);
		if (0<num){
			config->spNumOfFeatures = num;
			return true;
		}
		return false;
	}
	if(strcmp(param,"spExtractionMode")==0){
		if(strcmp(val,"true")==0){
			config->spExtractionMode = true;
			return true;
		}
		else if(strcmp(val,"false")==0){
			config->spExtractionMode = false;
			return true;
		}
		return false;
	}
	if(strcmp(param,"spNumOfSimilarImages")==0){
		if(!allnum(val)){//if val is not a string containing only numbers
			return false;
		}
		int num = atoi(val);
		if (0<num){
			config->spNumOfSimilarImages = num;
			return true;
		}
		return false;
	}
	if(strcmp(param,"spKDTreeSplitMethod")==0){
		if(strcmp(val,"RANDOM")==0){
			config->spKDTreeSplitMethod = RANDOM;
			return true;
		}
		else if(strcmp(val,"MAX_SPREAD")==0){
			config->spKDTreeSplitMethod = MAX_SPREAD;
			return true;
		}
		else if(strcmp(val,"INCREMENTAL")==0){
			config->spKDTreeSplitMethod = INCREMENTAL;
			return true;
		}
		return false;
	}
	if(strcmp(param,"spKNN")==0){
		if(!allnum(val)){//if val is not a string containing only numbers
			return false;
		}
		int num = atoi(val);
		if (0<num){
			config->spKNN = num;
			return true;
		}
		return false;
	}
	if(strcmp(param,"spMinimalGUI")==0){
		if(strcmp(val,"true")==0){
			config->spMinimalGUI = true;
			return true;
		}
		else if(strcmp(val,"false")==0){
			config->spMinimalGUI = false;
			return true;
		}
		return false;
	}
	if(strcmp(param,"spLoggerLevel")==0){
		if(!allnum(val)){//if val is not a string containing only numbers
			return false;
		}
		int num = atoi(val);
		if ((0<num)&&(num<5)){
			config->spLoggerLevel = num;
			return true;
		}
		return false;
	}
	if(strcmp(param,"spLoggerFilename")==0){
		if(strcmp(val,"stdout")==0){
			strcpy(config->spLoggerFilename,val);
			return true;
		}
		else{
			strcpy(config->spLoggerFilename,"notstdout"); //TODO check meaning of what happens if value is not stdout.
			return true;
		}
	}
	return false;
}


SPConfig spConfigCreate(const char* filename,SP_CONFIG_MSG* msg){

	//TODO add [R] error messeges SP_CONFIG_INVALID_STRING \ INTEGER and check how to

	bool in;
	if(filename == NULL){
		*msg = SP_CONFIG_INVALID_ARGUMENT;
		return NULL;
	}
	FILE* fp = fopen(filename,"r");
	if(fp == NULL){
		*msg = SP_CONFIG_CANNOT_OPEN_FILE;
		return NULL;
	}
	SPConfig config = (SPConfig)malloc(sizeof(SPConfig)); //allocating memory and setting default values
	if(config == NULL){
		*msg = SP_CONFIG_ALLOC_FAIL;
		return NULL;
	}

	strcpy(config->spImagesDirectory,"notset");
	strcpy(config->spImagesPrefix,"notset");
	strcpy(config->spImagesSuffix,"notset");
	config->spNumOfImages = 0;
	config->spPCADimension = 20;
	strcpy(config->spPCAFilename,"pca.yml");
	config->spNumOfFeatures = 100;
	config->spExtractionMode = true;
	config->spMinimalGUI = false;
	config->spNumOfSimilarImages = 1;
	config->spKNN = 1;
	config->spKDTreeSplitMethod = MAX_SPREAD;
	config->spLoggerLevel = 3;
	strcpy(config->spLoggerFilename,"stdout");
	char line[1024];
	char param[1024];
	char val[1024];
	int linenumber = 1;
	while(fgets(line,1024,fp)!= NULL){ //each time read a line only each line is at most 1024 (moab)
		trim(line);
		if(*line == '#'){ // if a comment than continue to next line
			linenumber++;
			continue;
		}
		splitmid(line,param,val);
		if ((contains(param,' '))||(contains(val,' '))){
			printf("File: %s\nLine: %d\nMessage: Invalid configuration line",filename,linenumber);
			return NULL;
		}
		if(!(in = insertconfig(config,param,val))){
			printf("File: %s\nLine: %d\nMessage: Invalid value - constraint not met",filename,linenumber);
			return NULL;
		}
		linenumber++;
	}
	fclose(fp);
	if((strcmp(config->spImagesDirectory,"notset")==0)){
		printf("File: %s\nLine: %d\nMessage: Parameter %s is not set",filename,linenumber,"spImagesDirectory");
		*msg = SP_CONFIG_MISSING_DIR;
		return NULL;
	}
	if(strcmp(config->spImagesPrefix,"notset")==0){
		printf("File: %s\nLine: %d\nMessage: Parameter %s is not set",filename,linenumber,"spImagesPrefix");
		*msg = SP_CONFIG_MISSING_PREFIX;
		return NULL;
	}
	if(strcmp(config->spImagesSuffix,"notset")==0){
		printf("File: %s\nLine: %d\nMessage: Parameter %s is not set",filename,linenumber,"spImagesSuffix");
		*msg = SP_CONFIG_MISSING_SUFFIX;
		return NULL;
	}
	if(config->spNumOfImages == 0){
		printf("File: %s\nLine: %d\nMessage: Parameter %s is not set",filename,linenumber,"spNumOfImages");
		*msg = SP_CONFIG_MISSING_NUM_IMAGES;
		return NULL;
	}
	*msg = SP_CONFIG_SUCCESS;
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
		return ans;
	}
}
SP_CONFIG_MSG spConfigGetImagePath(char* imagePath, const SPConfig config,int index){

	if(imagePath == NULL || config == NULL){
		return SP_CONFIG_INVALID_ARGUMENT;
	} else if (index>=config->spNumOfImages) {
		return SP_CONFIG_INDEX_OUT_OF_RANGE;
	} else {
		sprintf(imagePath, "%s%s%d%s",config->spImagesDirectory,config->spImagesPrefix,index,config->spImagesSuffix);
		return SP_CONFIG_SUCCESS;
	}
}


SP_CONFIG_MSG spConfigGetPCAPath(char* pcaPath, const SPConfig config){
	if(strlen(pcaPath)<(strlen(config->spImagesDirectory)+strlen(config->spPCAFilename))){
		return SP_CONFIG_ALLOC_FAIL;
	}
	if(pcaPath == NULL || config == NULL){
		return SP_CONFIG_INVALID_ARGUMENT;
	} else {
		sprintf(pcaPath, "%s%s",config->spImagesDirectory, config->spPCAFilename);
		return SP_CONFIG_SUCCESS;
	}
}

int spConfigGetMethod(const SPConfig config){
	switch (config->spKDTreeSplitMethod) {
		case MAX_SPREAD:
			return 0;
			break;
		case RANDOM:
			return 1;
			break;
		case INCREMENTAL:
			return 2;
			break;
		default:
			return 0;
			break;
	}
	return  config->spKDTreeSplitMethod;
}

bool spConfigGetExtractionMode(const SPConfig config){
	return config->spExtractionMode;
}

SP_CONFIG_MSG spConfigGetImagePathfeats(char* imagePath, const SPConfig config,int index){

	if(imagePath == NULL || config == NULL){
		return SP_CONFIG_INVALID_ARGUMENT;
	} else if (index>=config->spNumOfImages) {
		return SP_CONFIG_INDEX_OUT_OF_RANGE;
	} else {
		sprintf(imagePath, "%s%s%d%s",config->spImagesDirectory,config->spImagesPrefix,index,".feats");
		return SP_CONFIG_SUCCESS;
	}
}

int spConfigGetNumSimilarImages(const SPConfig config){
	return config->spNumOfSimilarImages;
}


void spConfigDestroy(SPConfig config){
	if (config != NULL) {
		free (config);
	}
}





