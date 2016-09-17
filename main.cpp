
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



int main(int argc,char* argv[]){

	SPConfig config;
	char configpath[1024] = ""; // asked moab can assume that not more than 1024 char
	if(argc > 1){ // if inserted command line arguments
		if ((argc == 3)&&(!(strcmp(argv[1],"-c")))){ // checks if a path was inserted in the correct format
			strcpy(configpath,argv[2]);
		}else{
			printf("Invalid command line : use -c <config_filename>\n");
			return 0;
		}
	}
	if (!strcmp(configpath,"")){ //if no path was inserted
		strcpy(configpath,"spcbir.config");
	}
	SP_CONFIG_MSG msg;
	config = spConfigCreate(configpath,&msg);
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
	//finished creating SPLogger

	ImageProc proc = ImageProc(config);
	spLoggerPrintInfo("Creating imageproc success");
	// finished creating image processing instance

	int i,j,k;
	int n=0;
	int numofimages = spConfigGetNumOfImages(config,&msg);
	int* tempdir = (int*)malloc(sizeof(int)*numofimages);
	if(tempdir == NULL){spLoggerPrintError("tempdir is null!",__FILE__,__func__,__LINE__);}
	else{spLoggerPrintDebug("tempdir allocation is success!!",__FILE__,__func__,__LINE__);}
	char temppath[1024];
	int tempnumOfFeatsextracted;
	SPPoint** directory = (SPPoint**)malloc(sizeof(SPPoint*)*numofimages); // allocating matrix of feats per image
	if(directory == NULL){spLoggerPrintError("directory is null!",__FILE__,__func__,__LINE__);return 0;}
	else{spLoggerPrintDebug("directory allocation is success!!",__FILE__,__func__,__LINE__);}
	SPPoint* finaldir;

	if (spConfigGetExtractionMode(config)){ // if we are in extraction mode
		FILE* fw;
		for (i = 0; i < numofimages; i++) { //for each image in image directory
			msg = spConfigGetImagePath (temppath,config,i);
			if(msg != SP_CONFIG_SUCCESS){spLoggerPrintError(spConfigMsgToString(msg),__FILE__,__func__,__LINE__);return 0;}
			else{spLoggerPrintDebug(spConfigMsgToString(msg),__FILE__,__func__,__LINE__);}
			directory[i] = proc.getImageFeatures(temppath,i,&tempnumOfFeatsextracted);
			if(directory[i]==NULL){spLoggerPrintError("error extracting image features",__FILE__,__func__,__LINE__);return 0;}
			else{spLoggerPrintDebug("extracted features from image successfully",__FILE__,__func__,__LINE__);}
			n+=tempnumOfFeatsextracted;
			tempdir[i] = tempnumOfFeatsextracted;
			msg = spConfigGetImagePathfeats(temppath,config,i); //get the file to write to
			if(msg != SP_CONFIG_SUCCESS){spLoggerPrintError(spConfigMsgToString(msg),__FILE__,__func__,__LINE__);return 0;}
			else{spLoggerPrintDebug("successfully extracted image path to write to",__FILE__,__func__,__LINE__);}
			fw = fopen(temppath,"w");//open file for writing
			writefeats(fw,directory[i],tempnumOfFeatsextracted);
		}
		fclose(fw);
		finaldir = (SPPoint*)malloc(sizeof(SPPoint)*n); //making final dir
		if (finaldir == NULL){spLoggerPrintError("error initializing finaldir in extraction mode",__FILE__,__func__,__LINE__);return 0;}
		else{spLoggerPrintDebug("initialized finaldir successfully",__FILE__,__func__,__LINE__);}
		k=0;
		for (i = 0; i < numofimages; ++i){
			for (j = 0; j < tempdir[i]; ++j) {
				finaldir[k] = spPointCopy(directory[i][j]);
				k++;
			}
		}
		DirectoryDestroy(directory,tempdir,numofimages);
	}
	else{ // non - extraction mode

		FILE* fr;
		for (i = 0; i < numofimages; i++){
			msg = spConfigGetImagePathfeats(temppath,config,i); //get path to feats file to read from
			if (msg !=SP_CONFIG_SUCCESS){spLoggerPrintError("error extracting feats path from config",__FILE__,__func__,__LINE__);return 0;}
			else{spLoggerPrintDebug("successfully extracted feats path from config",__FILE__,__func__,__LINE__);}
			fr = fopen(temppath,"r");
			if(fr ==NULL){spLoggerPrintError("error opening .feats file to extract",__FILE__,__func__,__LINE__);return 0;}
			else{spLoggerPrintDebug("opend .feats file successfully",__FILE__,__func__,__LINE__);}
			directory[i] = getfeats(fr,(tempdir+i));
			n+=tempdir[i];
		}
		fclose(fr);
		finaldir = (SPPoint*)malloc(sizeof(SPPoint)*n); //making final dir
		if (finaldir == NULL){spLoggerPrintError("error initializing finaldir in extraction mode",__FILE__,__func__,__LINE__);return 0;}
		else{spLoggerPrintDebug("initialized finaldir successfully",__FILE__,__func__,__LINE__);}
		k=0;
		for (i = 0; i < numofimages; ++i){
			for (j = 0; j < tempdir[i]; ++j) {
				finaldir[k] = spPointCopy(directory[i][j]);
				k++;
			}
		}
		DirectoryDestroy(directory,tempdir,numofimages);
	}

	//after extraction / non - extraction and we have our finaldir containing all the feats(SPPoints)!
	spLoggerPrintInfo("success after extraction / non - extraction phase");

	bool out = false;
	int numofsimilarimages = spConfigGetNumSimilarImages(config);
	KDTreeNode* head = InitTree(finaldir,n,config);
	if(head ==NULL){spLoggerPrintError("failure building tree",__FILE__,__func__,__LINE__);return 0;}
	else{spLoggerPrintDebug("tree build complete successfully",__FILE__,__func__,__LINE__);}
	/*initialization of KDTree & free of finaldir complexity: O(d X nlogn)*/
	while(!out){
		printf("Please enter an image path:\n");
		fflush(stdout);
		char quarypath[1024]; //= (char*)malloc(sizeof(char)*1024); //moab said can assume quary path is at most 1024
		scanf("%s",quarypath);
		if(!strcmp(quarypath,"<>")){ //if chose to exit the program
			printf("Exiting…\n");
			out = true;
			break;
		}

		int* hits = (int*)malloc(sizeof(int)*numofimages);
		for(i=0;i<numofimages;i++){//initialize to -1 hits per image
			hits[i] = -1;
		}
		//an array to keep track of how many times an image feature was selected to be k-nearest feature
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
			spBPQueueDestroy(tempbpq);
		}
		calculatewinners(winners,hits,numofimages,numofsimilarimages);
		free(quaryfeatures);

		//showing results
		spLoggerPrintInfo("showing results");

		if(spConfigMinimalGui(config,&msg)){ // if we are in minimal-GUI mode
			for (i = 0; i <numofsimilarimages ; ++i) {
				spConfigGetImagePath(temppath,config,winners[i]);
				proc.showImage(temppath);
			}
			free(hits);
			free(winners);
		}
		else{ // not in minimal-GUI mode
			printf("Best candidates for - %s - are:\n",quarypath);
			for (i = 0; i < numofsimilarimages; ++i) {
				spConfigGetImagePath(temppath,config,winners[i]);
				printf("%s\n",temppath);
			}
			free(hits);
			free(winners);
		}
	}
	KDTreeDestroy(head);
	spConfigDestroy(config);
	free(tempdir);
	spLoggerDestroy();
	spLoggerPrintInfo("finished free of all memory successfully");
	return 1;
}

