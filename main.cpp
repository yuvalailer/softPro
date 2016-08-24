/*

#include <string.h>
#include <cstdio>
#include <cstdlib>

#include "auxiliaryfunc.h"
#include "SPConfig.h"
#include "SPPoint.h"
#include "KDTree.h"

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

	int i,j,k;
	int n=0;

	int tempnofimages = spConfigGetNumOfImages(config,&msg);
	int tempnoffeatures = spConfigGetNumOfFeatures(config,&msg);
	int tempdir[tempnofimages];

	SPPoint** directory = (SPPoint**)malloc(sizeof(SPPoint*)*tempnofimages); // allocating matrix of feats per image

	SPPoint* finaldir;

	if (spConfigGetExtractionMode(config)){ // if we are in extraction mode
		char* temppath;
		int numOfFeats;
		FILE* fw;

		for (i = 0; i < tempnofimages; i++) { //for each image in image directory
			msg = spConfigGetImagePath (temppath,config,i); //TODO mssg to where
			directory[i] = getImageFeatures(temppath,i,&numOfFeats);
			n+=numOfFeats;
			tempdir[i] = numOfFeats;
			msg = spConfigGetImagePathfeats(temppath,config,i); //get the file to write to
			fw = fopen(temppath,"w");//open file for writing
			writefeats(fw,directory[i],numOfFeats);
		}
		fclose(fw);

		finaldir = (SPPoint*)malloc(sizeof(SPPoint)*n); //making final dir
		k=0;
		for (i = 0; i < tempnofimages; ++i){
			for (j = 0; j < tempdir[i]; ++j) {
				finaldir[k] = spPointCopy(directory[i][j]);
				k++;
			}
		}
		free(directory);
	}
	else{ // non - extraction mode
		char* temppath;
		FILE* fr;

		for (i = 0; i < tempnofimages; i++){
			msg = spConfigGetImagePathfeats(temppath,config,i); //get path to feats file to read from
			fr = fopen(temppath,"r");
			directory[i] = getfeats(fr,(tempdir+i));
			n+=tempdir[i];
		}
		fclose(fr);
		finaldir = (SPPoint*)malloc(sizeof(SPPoint)*n); //making final dir
		k=0;
		for (i = 0; i < tempnofimages; ++i){
			for (j = 0; j < tempdir[i]; ++j) {
				finaldir[k] = spPointCopy(directory[i][j]);
				k++;
			}
		}
		free(directory);
	}

	//after extraction / non - extraction and we have our finaldir containing all the feats(SPPoints)!

	bool out = false;

	while(!out){
		printf("Please enter an image path:\n");
		char* imagePath;
		scanf("%s",imagePath);
		if(!strcmp(imagePath,"<>")){ //if chose to exit the program
			printf("Exiting…\n");
			out = true;
		}

		KDTreeNode head = InitTree(finaldir,n,config); //initialization of KDTree complexity: O(d X nlogn)




	}



	free(config);
	return 1;
}

*/
