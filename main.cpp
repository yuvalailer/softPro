
#include <cstdio>
#include <cstdlib>
#include <cstdbool>
#include "SPConfig.h"

int main(int argc,char* argv[]){ //TODO finish insert [R] error messeges page 6 in the end.

	SPConfig config = (SPConfig)malloc(sizeof(SPConfig));
	if (config == NULL){//TODO check what happens in bad allocation what does main return?
		return NULL;
	}
	if (){ // TODO TODO check if inserted command line argument - ailer because its linux i didnt understand

	}
	else{
		SP_CONFIG_MSG msg; //TODO check what msg pointer do we need to insert
		config = spConfigCreate("spcbir.config",&msg); //TODO check what msg pointer do we need to insert
		if (config == NULL){
			if (msg == SP_CONFIG_CANNOT_OPEN_FILE){ //TODO where are the stored masseges stored to? splogger? ailer?
				printf("The default configuration file spcbir.config couldn’t be open");
				return NULL;
			}
		}
	}






	printf("all good");
	return 1;
}

