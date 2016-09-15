CC = gcc
CPP = g++
#put your object files here
OBJS = main.o SPImageProc.o SPPoint.o auxiliaryfunc.o SPBPriorityQueue.o SPConfig.o  SPList.o KDTree.o SPKDArray.o SPListElement.o SPLogger.o
#The executabel filename
EXEC = SPCBIR
INCLUDEPATH=/usr/local/lib/opencv-3.1.0/include/
LIBPATH=/usr/local/lib/opencv-3.1.0/lib/
LIBS=-lopencv_xfeatures2d -lopencv_features2d \
-lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_core


CPP_COMP_FLAG = -std=c++11 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

C_COMP_FLAG = -std=c99 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(CPP) $(OBJS) -L$(LIBPATH) $(LIBS) -o $@
main.o: main.cpp SPImageProc.h SPConfig.h SPLogger.h SPPoint.h \
 auxiliaryfunc.h KDTree.h SPKDArray.h SPBPriorityQueue.h SPListElement.h
	$(CPP) $(CPP_COMP_FLAG) -I$(INCLUDEPATH) -c $*.cpp
SPImageProc.o: SPImageProc.cpp SPImageProc.h SPConfig.h SPPoint.h SPLogger.h
	$(CPP) $(CPP_COMP_FLAG) -I$(INCLUDEPATH) -c $*.cpp
#a rule for building a simple c souorce file
#use gcc -MM SPPoint.c to see the dependencies
SPPoint.o: SPPoint.c SPPoint.h SPLogger.h
	$(CC) $(C_COMP_FLAG) -c $*.c
auxiliaryfunc.o: auxiliaryfunc.c auxiliaryfunc.h SPPoint.h SPLogger.h
	$(CC) $(C_COMP_FLAG) -c $*.c
SPBPriorityQueue.o: SPBPriorityQueue.c SPBPriorityQueue.h SPListElement.h \
 SPList.h
	$(CC) $(C_COMP_FLAG) -c $*.c
SPConfig.o: SPConfig.c SPConfig.h SPLogger.h
	$(CC) $(C_COMP_FLAG) -c $*.c
SPList.o: SPList.c SPList.h SPListElement.h
	$(CC) $(C_COMP_FLAG) -c $*.c
KDTree.o: KDTree.c KDTree.h SPPoint.h SPLogger.h SPKDArray.h SPConfig.h \
 SPBPriorityQueue.h SPListElement.h
	$(CC) $(C_COMP_FLAG) -c $*.c
SPKDArray.o: SPKDArray.c SPKDArray.h SPPoint.h SPLogger.h
	$(CC) $(C_COMP_FLAG) -c $*.c
SPListElement.o: SPListElement.c SPListElement.h
	$(CC) $(C_COMP_FLAG) -c $*.c
SPLogger.o: SPLogger.c SPLogger.h
	$(CC) $(C_COMP_FLAG) -c $*.c
clean:
	rm -f $(OBJS) $(EXEC)

# add Depeden to main.
# make a line like point to all .o and $.
# find depend with use gcc -MM SPPoint.c <---(file name).
# add all .o to OBJS.
## auxiliaryfunc.c   SPImageProc.cpp
## main.cpp  SPBPriorityQueue.c  SPConfig.c   SPList.c         SPPoint.c
## KDTree.c  SPKDArray.c      SPListElement.c  SPLogger.c

