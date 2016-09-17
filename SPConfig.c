/*
 * SPConfig.c
 *
 *  Created on: 19 αιεμι 2016
 *      Author: michael ozeri & yuval ailer
 */


#include "SPConfig.h"


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
			*msg = SP_CONFIG_INVALID_ARGUMENT;
		} else {
			*msg = SP_CONFIG_SUCCESS;
		}
	}
	return ans; // Return an int. to be change if needed in the function.
}

void trim(char* s){
	if(Blank(s)){
		return;
	}
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
	for (i=0;i<len-cnt;i++){ // shift all left by cnt
		*(s+i) = *(s+i+cnt);;
	}
	*(s+len-cnt) = '\0';
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
			strcpy(config->spLoggerFilename,val);
			return true;
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
	SPConfig config = (SPConfig)malloc(sizeof(*config)); //allocating memory and setting default values
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
		if((strlen(line) == 1)&&(!strcmp(line,"\n"))){
			linenumber++;
			continue;
		}
		trim(line);
		if(*line == '#'){ // if a comment than continue to next line
			linenumber++;
			continue;
		}
		splitmid(line,param,val);
		if ((contains(param,' '))||(contains(val,' '))){
			printf("File: %s\nLine: %d\nMessage: Invalid configuration line\n",filename,linenumber);
			*msg = SP_CONFIG_INVALID_ARGUMENT;
			return NULL;
		}
		if(!(in = insertconfig(config,param,val))){
			printf("File: %s\nLine: %d\nMessage: Invalid value - constraint not met\n",filename,linenumber);
			*msg = SP_CONFIG_INVALID_ARGUMENT;
			return NULL;
		}
		linenumber++;
	}
	fclose(fp);
	if((strcmp(config->spImagesDirectory,"notset")==0)){
		printf("File: %s\nLine: %d\nMessage: Parameter %s is not set\n",filename,linenumber,"spImagesDirectory");
		*msg = SP_CONFIG_MISSING_DIR;
		return NULL;
	}
	if(strcmp(config->spImagesPrefix,"notset")==0){
		printf("File: %s\nLine: %d\nMessage: Parameter %s is not set\n",filename,linenumber,"spImagesPrefix");
		*msg = SP_CONFIG_MISSING_PREFIX;
		return NULL;
	}
	if(strcmp(config->spImagesSuffix,"notset")==0){
		printf("File: %s\nLine: %d\nMessage: Parameter %s is not set\n",filename,linenumber,"spImagesSuffix");
		*msg = SP_CONFIG_MISSING_SUFFIX;
		return NULL;
	}
	if(config->spNumOfImages == 0){
		printf("File: %s\nLine: %d\nMessage: Parameter %s is not set\n",filename,linenumber,"spNumOfImages");
		*msg = SP_CONFIG_MISSING_NUM_IMAGES;
		return NULL;
	}
	*msg = SP_CONFIG_SUCCESS;
	return config;
}

bool spConfigIsExtractionMode(const SPConfig config, SP_CONFIG_MSG* msg){
	*msg = SP_CONFIG_SUCCESS; //always filled because default value
	return config->spExtractionMode;
}

bool spConfigMinimalGui(const SPConfig config, SP_CONFIG_MSG* msg){
	*msg = SP_CONFIG_SUCCESS; //always filled because default value
	return config->spMinimalGUI;

}
int spConfigGetNumOfImages(const SPConfig config, SP_CONFIG_MSG* msg){
	int filed = (config->spNumOfImages); // enter the NumOfImages_mode as int.
	return configUtills(filed,config,msg);
}

int spConfigGetNumOfFeatures(const SPConfig config, SP_CONFIG_MSG* msg){
	*msg = SP_CONFIG_SUCCESS; //always filled because default value
	return config->spNumOfFeatures;
}

int spConfigGetPCADim(const SPConfig config, SP_CONFIG_MSG* msg){
	*msg = SP_CONFIG_SUCCESS; //always filled because default value
	return config->spPCADimension;
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
	//	if(strlen(pcaPath)<(strlen(config->spImagesDirectory)+strlen(config->spPCAFilename))){
	//		return SP_CONFIG_ALLOC_FAIL;
	//	} //TODO check if this is necessary at all (strlen checks until '\0' not array size
	if(pcaPath == NULL || config == NULL){
		return SP_CONFIG_INVALID_ARGUMENT;
	} else {
		sprintf(pcaPath, "%s%s",config->spImagesDirectory, config->spPCAFilename);
		return SP_CONFIG_SUCCESS;
	}
}

method spConfigGetMethod(const SPConfig config){
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

char* spConfigGetLoggerFilename(const SPConfig config){
	return config->spLoggerFilename;
}

SP_LOGGER_LEVEL spConfigGetLoggerLevel(const SPConfig config){
	switch (config->spLoggerLevel){
	case 0:
		return SP_LOGGER_ERROR_LEVEL;
	case 1:
		return SP_LOGGER_WARNING_ERROR_LEVEL;
	case 2:
		return SP_LOGGER_INFO_WARNING_ERROR_LEVEL;
	case 3:
		return SP_LOGGER_DEBUG_INFO_WARNING_ERROR_LEVEL;
	}
	return SP_LOGGER_DEBUG_INFO_WARNING_ERROR_LEVEL;
}

char* spConfigMsgToString(SP_CONFIG_MSG msg){
	switch(msg) {
	case SP_CONFIG_MISSING_DIR:
		return "SP_CONFIG_MISSING_DIR";
		break;
	case SP_CONFIG_MISSING_PREFIX:
		return "SP_CONFIG_MISSING_PREFIX";
		break;
	case SP_CONFIG_MISSING_SUFFIX:
		return "SP_CONFIG_MISSING_SUFFIX";
		break;
	case SP_CONFIG_MISSING_NUM_IMAGES:
		return "SP_CONFIG_MISSING_NUM_IMAGES";
		break;
	case SP_CONFIG_CANNOT_OPEN_FILE:
		return "SP_CONFIG_CANNOT_OPEN_FILE";
		break;
	case SP_CONFIG_ALLOC_FAIL:
		return "SP_CONFIG_ALLOC_FAIL";
		break;
	case SP_CONFIG_INVALID_INTEGER:
		return "SP_CONFIG_INVALID_INTEGER";
		break;
	case SP_CONFIG_INVALID_STRING:
		return "SP_CONFIG_INVALID_STRING";
		break;
	case SP_CONFIG_INVALID_ARGUMENT:
		return "SP_CONFIG_INVALID_ARGUMENT";
		break;
	case SP_CONFIG_INDEX_OUT_OF_RANGE:
		return "SP_CONFIG_INDEX_OUT_OF_RANGE";
		break;
	case SP_CONFIG_SUCCESS:
		return "SP_CONFIG_SUCCESS";
		break;
	}
	return "SP_CONFIG_SUCCESS";
}

bool Blank(char* s){
	char* t = s;
	while(*t != '\0'){
		if(*t != ' '){
			return false;
		}
		t = t+1;
	}
	return true;
}


/*int main(){

	SP_CONFIG_MSG msg;
	spConfigCreate("./configtest/badImagesconfig.config",&msg);
	spConfigMsgToString(msg);
	printf("\n");
	spConfigCreate("spcbir.config",&msg);
	spConfigMsgToString(msg);
	printf("\n");
	spConfigCreate("./configtest/badImagesconfig2.config",&msg);
	spConfigMsgToString(msg);
	printf("\n");
	spConfigCreate("./configtest/badSuffixconfig.config",&msg);
	spConfigMsgToString(msg);
	printf("\n");



	return 1;
}*/





