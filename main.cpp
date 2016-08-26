
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

	SPConfig config = (SPConfig)malloc(sizeof(SPConfig));
	if (config == NULL){return NULL;}//TODO check what happens in bad allocation what does main return?
	char* path = "";
	if((argv[1]!=NULL)||(argv[2]!=NULL)){ // if inserted command line arguments
		if ((argv[1] == "-c") && (argv[2] != NULL) ){ // check if a path was inserted in the correct format
			strcpy(path,argv[2]);
		}else{
			printf("Invalid command line : use -c <config_filename>\n"); //TODO understand in what to change <config_filename>
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

	ImageProc proc = ImageProc(config);

	// finished creating image processing instance

	int i,j,k;
	int n=0;

	int numofimages = spConfigGetNumOfImages(config,&msg);
	int numoffeatures = spConfigGetNumOfFeatures(config,&msg);
	int tempdir[numofimages];
	char* temppath;

	SPPoint** directory = (SPPoint**)malloc(sizeof(SPPoint*)*numofimages); // allocating matrix of feats per image

	SPPoint* finaldir;

	if (spConfigGetExtractionMode(config)){ // if we are in extraction mode

		int tempnumOfFeatsextracted;
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
		char* quarypath;
		scanf("%s",quarypath);
		if(!strcmp(quarypath,"<>")){ //if chose to exit the program
			printf("Exiting…\n");
			out = true;
		}

		KDTreeNode head = InitTree(finaldir,n,config); //initialization of KDTree complexity: O(d X nlogn)
		int hits[numofimages];
		/* an array to keep track of how many times
		 *an image feature was selected to be k-nearest feature*/
		int winners[numofsimilarimages];
		/* an array contains indexes of winners ordered by numbered of hits
		 * example: winner[0] - the index of the most closest image*/




		//showing resaults

		if(spConfigMinimalGui(config,&msg)){ // if we are in minimal gui mode
			for (i = 0; i <numofsimilarimages ; ++i) {
				spConfigGetImagePath(temppath,config,winners[i]);
				proc.showImage(temppath);
			}
		}
		else{ // not in minimal gui mode
			printf("Best candidates for - %s - are:\n",quarypath);
			for (i = 0; i < numofsimilarimages; ++i) {
				spConfigGetImagePath(temppath,config,winners[i]);
				printf("%s\n",temppath);
			}
		}
	}
	free(config);
	return 1;
}

