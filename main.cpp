
#include <string.h>
#include <cstdio>
#include <cstdlib>

#include "SPConfig.h"
#include "SPPoint.h"
#include "auxiliaryfunc.h"

using namespace sp;

//TODO where are the stored messages go into? SPLOGGER?

int main(int argc,char* argv[]){



	SPConfig config = (SPConfig)malloc(sizeof(SPConfig));
	if (config == NULL){return NULL;}//TODO check what happens in bad allocation what does main return?
	char* path = "";
	if((argv[1]!=NULL)||(argv[2]!=NULL)){ // if inserted command line arguments
		if ((argv[1] == "-c") && (argv[2] != NULL) ){ // check if a path was inserted in the correct format
			strcpy(path,argv[2]);
		}else{
			printf("Invalid command line : use -c <config_filename>\n");
			return NULL;
		}
	}

	if (!strcmp(path,"")){ //if no path was inserted
		path = "spcbir.config";
	}

	SP_CONFIG_MSG msg;
	config = spConfigCreate(path,&msg); //TODO check what msg pointer do we need to insert
	if (config == NULL){ // if there was an error
		if (msg == SP_CONFIG_CANNOT_OPEN_FILE){
			if(!strcmp(path,"spcbir.config")){
				printf("The default configuration file spcbir.config couldn’t be open\n");
				return NULL;
			}else{
				printf("The configuration file %s couldn’t be open\n",path);
				return NULL;
			}
		}
	}

	// finished creating config file

	int i;

	if (spConfigGetExtractionMode(config)){ // if we are in extraction mode

		SPPoint* temppoint;
		char* temppath;
		int tempnfeats = spConfigGetNumOfFeatures(config,&msg); //TODO check messege
		int tempnofimages = spConfigGetNumOfImages(config,&msg);//TODO where to store messages SPLogger
		FILE* fw;

		for (i = 0; i < tempnofimages; i++) { //for each image in image directory
			msg = spConfigGetImagePath (temppath,config,i); //TODO mssg to where
			temppoint = getImageFeatures(temppath,i,tempnfeats);
			msg = spConfigGetImagePathfeats(temppath,config,i); //get the file to write to
			fw = fopen(temppath,"w");//open file for writing



		}
		fclose(fw);
	}
	else{ // non - extraction mode



	}



	return 1;
}

