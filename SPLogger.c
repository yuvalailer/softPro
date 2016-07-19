/*

 * SPLogger.c
 *
 *  Created on: 19 αιεμι 2016
 *      Author: michael
 */


#include "SPLogger.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
//File open mode
#define SP_LOGGER_OPEN_MODE "w"

// Global variable holding the logger
SPLogger logger = NULL;

struct sp_logger_t {
	FILE* outputChannel; //The logger file
	bool isStdOut; //Indicates if the logger is stdout
	SP_LOGGER_LEVEL level; //Indicates the level
};

SP_LOGGER_MSG spLoggerCreate(const char* filename, SP_LOGGER_LEVEL level) {
	if (logger != NULL) { //Already defined
		return SP_LOGGER_DEFINED;
	}
	logger = (SPLogger) malloc(sizeof(*logger));
	if (logger == NULL) { //Allocation failure
		return SP_LOGGER_OUT_OF_MEMORY;
	}
	logger->level = level; //Set the level of the logger
	if (filename == NULL) { //In case the filename is not set use stdout
		logger->outputChannel = stdout;
		logger->isStdOut = true;
	} else { //Otherwise open the file in write mode
		logger->outputChannel = fopen(filename, SP_LOGGER_OPEN_MODE);
		if (logger->outputChannel == NULL) { //Open failed
			free(logger);
			logger = NULL;
			return SP_LOGGER_CANNOT_OPEN_FILE;
		}
		logger->isStdOut = false;
	}
	return SP_LOGGER_SUCCESS;
}

void spLoggerDestroy() {
	if (!logger) {
		return;
	}
	if (!logger->isStdOut) { //Close file only if not stdout
		fclose(logger->outputChannel);
	}
	free(logger); //free allocation
	logger = NULL;
}
/**
 * a utility function, making tests for arguments correctness.
 * used to avoid code copying in all the different printing setups.
 */
SP_LOGGER_MSG returnMaker(const char* msg, const char* file,
		const char* function, const int line) { // made to avoid code copying;

	if (logger == NULL) {
		return SP_LOGGER_UNDIFINED;

	} else if (msg == NULL || file == NULL || function == NULL || line <= -1) {
		return SP_LOGGER_INVAlID_ARGUMENT;

	} else if (logger->isStdOut != false) {
		return SP_LOGGER_WRITE_FAIL;

	}
	return SP_LOGGER_SUCCESS; // all good


}

SP_LOGGER_MSG spLoggerPrintError(const char* msg, const char* file,
		const char* function, const int line) {

	SP_LOGGER_MSG ans = returnMaker(msg, file, function, line);
	if (ans != SP_LOGGER_SUCCESS) {
		return ans;

	} else {
		if (spLoggerLevelMaker(logger->level) <= 4) {

			fprintf(logger->outputChannel,
					"---ERROR---\n- file: %s\n- function: %s\n- line: %d\n- message: %s\n",
					file, function, line, msg);
		}
		return ans;
	}}
SP_LOGGER_MSG spLoggerPrintWarning(const char* msg, const char* file,
		const char* function, const int line) {
	SP_LOGGER_MSG ans = returnMaker(msg, file, function, line);
	if (ans != SP_LOGGER_SUCCESS) {
		return ans;

	} else {
		if (spLoggerLevelMaker(logger->level) <= 3) {

			fprintf(logger->outputChannel,"---WARNING---\n- file: %s\n- function: %s\n- line: %d\n- message: %s\n",
					file, function, line, msg);
		}}
	return ans;
}

SP_LOGGER_MSG spLoggerPrintInfo(const char* msg) {
	SP_LOGGER_MSG ans = returnMaker(msg, __FILE__, __func__, __LINE__);
	if (ans != SP_LOGGER_SUCCESS) {
		return ans;

	} else {

		if (spLoggerLevelMaker(logger->level) <= 2) {

			fprintf(logger->outputChannel,"---INFO---\n- message: %s\n", msg);
		}}
	return ans; //TODO is this the right input for the testing?
}

SP_LOGGER_MSG spLoggerPrintDebug(const char* msg, const char* file,
		const char* function, const int line) {
	SP_LOGGER_MSG ans = returnMaker(msg, file, function, line);
	if (ans != SP_LOGGER_SUCCESS) {
		return ans;
	} else {

		if (spLoggerLevelMaker(logger->level) == 1) {

			fprintf(logger->outputChannel,
					"---DEBUG---\n- file: %s\n- function: %s\n- line: %d\n- message: %s\n",
					file, function, line, msg);
		}
	}
	return ans;
}

SP_LOGGER_MSG spLoggerPrintMsg(const char* msg) {

	SP_LOGGER_MSG ans = returnMaker(msg, __FILE__, __func__, __LINE__);
	if (ans != SP_LOGGER_SUCCESS) {
		return ans;
	} else {

		if (spLoggerLevelMaker(logger->level) <= 4) {

			fprintf(logger->outputChannel,"%s\n",msg);
		}}
	return ans;
}
/**
 * level maker is a simple function, used to determine if
 * a logging level is hair or lower then required.
 *
 * it works by mapping every level to an integer,
 * by numerical order.
 */


int spLoggerLevelMaker(SP_LOGGER_LEVEL level){
	switch (level) {
	case SP_LOGGER_DEBUG_INFO_WARNING_ERROR_LEVEL :
		return 1;
		break;

	case SP_LOGGER_INFO_WARNING_ERROR_LEVEL :
		return 2;
		break;

	case SP_LOGGER_WARNING_ERROR_LEVEL :

		return 3;
		break;

	case SP_LOGGER_ERROR_LEVEL :
		return 4;
		break;

	}
	return 5; // since all level are enums, their must be an int for it. this is for future maintenance and testing.
}




