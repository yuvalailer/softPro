
#include <cstdbool>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "SPImageProc.h"

extern "C"{
#include "auxiliaryfunc.h"
#include "SPConfig.h"
#include "SPPoint.h"
#include "KDTree.h"
}


using namespace sp;

//TODO where are the stored messages go into? SPLOGGER?

int main(int argc,char* argv[]){

	SPConfig config;
	char configpath[1024] = ""; // asked moab can assume that not more than 1024 char

	if(argc > 1){ // if inserted command line arguments
		if ((argc == 3)&&(!(strcmp(argv[1],"-c")))){ // check if a path was inserted in the correct format
			strcpy(configpath,argv[2]);
		}else{
			printf("Invalid command line : use -c <config_filename>\n"); //TODO understand in what to change <config_filename>
			return 0;
		}
	}
	if (!strcmp(configpath,"")){ //if no path was inserted
		strcpy(configpath,"spcbir.config");
	}

	SP_CONFIG_MSG msg;
	config = spConfigCreate(configpath,&msg); //TODO check what msg pointer do we need to insert
	if (config == NULL){ // if there was an error
		if (msg == SP_CONFIG_CANNOT_OPEN_FILE){
			if(!strcmp(configpath,"spcbir.config")){
				printf("The default configuration file spcbir.config couldn’t be open\n");
				return 0;
			}else{
				printf("The configuration file %s couldn’t be open\n",configpath);
				return 0;
			}
		}
	}

	// finished creating configuration file

	spLoggerCreate(spConfigGetLoggerFilename(config),spConfigGetLoggerLevel(config));

	//finished creating SPLogger filename

	ImageProc proc = ImageProc(config);

	// finished creating image processing instance

	int i,j,k;
	int n=0;

	int numofimages = spConfigGetNumOfImages(config,&msg);
	//	int numoffeatures = spConfigGetNumOfFeatures(config,&msg);
	int* tempdir = (int*)malloc(sizeof(int)*numofimages);
	//	int tempdir[numofimages];
	char* temppath = (char*)malloc(sizeof(char)*1024); //TODO release + can asuume 1024 at most?
	int tempnumOfFeatsextracted;

	SPPoint** directory = (SPPoint**)malloc(sizeof(SPPoint*)*numofimages); // allocating matrix of feats per image

	SPPoint* finaldir;

	if (spConfigGetExtractionMode(config)){ // if we are in extraction mode

		FILE* fw;

		for (i = 0; i < numofimages; i++) { //for each image in image directory
			msg = spConfigGetImagePath (temppath,config,i); //TODO mssg to where
			directory[i] = proc.getImageFeatures(temppath,i,&tempnumOfFeatsextracted);
			n+=tempnumOfFeatsextracted;
			tempdir[i] = tempnumOfFeatsextracted;
			msg = spConfigGetImagePathfeats(temppath,config,i); //get the file to write to
			fw = fopen(temppath,"w");//open file for writing
			writefeats(fw,directory[i],tempnumOfFeatsextracted);
		}

		fclose(fw);

		finaldir = (SPPoint*)malloc(sizeof(SPPoint)*n); //making final dir
		k=0;
		for (i = 0; i < numofimages; ++i){
			for (j = 0; j < tempdir[i]; ++j) {
				finaldir[k] = spPointCopy(directory[i][j]);
				k++;
			}
		}
		free(directory);
	}
	else{ // non - extraction mode
		FILE* fr;

		for (i = 0; i < numofimages; i++){
			msg = spConfigGetImagePathfeats(temppath,config,i); //get path to feats file to read from
			fr = fopen(temppath,"r");
			directory[i] = getfeats(fr,(tempdir+i));
			n+=tempdir[i];
		}
		fclose(fr);
		finaldir = (SPPoint*)malloc(sizeof(SPPoint)*n); //making final dir
		k=0;
		for (i = 0; i < numofimages; ++i){
			for (j = 0; j < tempdir[i]; ++j) {
				finaldir[k] = spPointCopy(directory[i][j]);
				k++;
			}
		}
		free(directory);
	}

	//after extraction / non - extraction and we have our finaldir containing all the feats(SPPoints)!

	bool out = false;
	int numofsimilarimages = spConfigGetNumSimilarImages(config);

	while(!out){
		printf("Please enter an image path:\n");
		fflush(stdout);
		char* quarypath = (char*)malloc(sizeof(char)*1024); //moab said can assume quary path is at most 1024
		scanf("%s",quarypath);
		if(!strcmp(quarypath,"<>")){ //if chose to exit the program
			printf("Exiting…\n");
			free(quarypath);
			out = true;
			break;
		}

		KDTreeNode* head = InitTree(finaldir,n,config); //initialization of KDTree complexity: O(d X nlogn)

		//		int hits[numofimages];
		int* hits = (int*)malloc(sizeof(int)*numofimages);
		for(i=0;i<numofimages;i++){//initialize to -1 hits per image
			hits[i] = -1;
		}
		//an array to keep track of how many times an image feature was selected to be k-nearest feature

		//		int winners[numofsimilarimages];
		int* winners = (int*)malloc(sizeof(int)*numofsimilarimages);

		//an array contains indexes of winners ordered by numbered of hits example: winner[0] - the index of the most closest image

		SPPoint* quaryfeatures = proc.getImageFeatures(quarypath,numofimages,&tempnumOfFeatsextracted);

		SPBPQueue tempbpq;

		for (i = 0; i < tempnumOfFeatsextracted; ++i) { //count hits per image
			tempbpq = KDTreeSearch(head,quaryfeatures[i],numofsimilarimages);
			while(!spBPQueueIsEmpty(tempbpq)){
				hits[spListElementGetIndex(spBPQueuePeek(tempbpq))]++;
				spBPQueueDequeue(tempbpq);

			}
			spBPQueueClear(tempbpq);
		}

		calculatewinners(winners,hits,numofimages,numofsimilarimages);

		free(quaryfeatures);

		//showing results

		if(spConfigMinimalGui(config,&msg)){ // if we are in minimal-GUI mode
			for (i = 0; i <numofsimilarimages ; ++i) {
				spConfigGetImagePath(temppath,config,winners[i]);
				proc.showImage(temppath);
			}
			free(hits);
			free(winners);
			KDTreeDestroy(head);
		}
		else{ // not in minimal-GUI mode
			printf("Best candidates for - %s - are:\n",quarypath);
			for (i = 0; i < numofsimilarimages; ++i) {
				spConfigGetImagePath(temppath,config,winners[i]);
				printf("%s\n",temppath);
			}
			free(hits);
			free(winners);
			KDTreeDestroy(head);
		}
	}
	spConfigDestroy(config);
	free(tempdir);
	return 1;
}



