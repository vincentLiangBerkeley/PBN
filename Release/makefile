OBJS = Menu.o Interactor.o Analyzer.o Iterator.o Simulator.o rMatrix.o tMatrix.o
CC = g++ 
DEBUG = -g -Weffc++ -std=c++11
INCPATH = ../Source/Headers/
CFLAGS = -Wall -c $(DEBUG) -I$(INCPATH)
LFLAGS = -Wall


PROGRAM = Analyzer

$(PROGRAM) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(PROGRAM)

##### Dependencies
Menu.o : ../Source/Headers/Menu.h ../Source/Src/Menu.cpp \
	../Source/Headers/Interactor.h ../Source/Headers/Displayer.h
	$(CC) $(CFLAGS) ../Source/Src/Menu.cpp

Interactor.o : ../Source/Headers/Interactor.h ../Source/Src/Interactor.cpp \
	../Source/Headers/Simulator.h ../Source/Headers/Iterator.h
	$(CC) $(CFLAGS) ../Source/Src/Interactor.cpp

Analyzer.o : ../Source/Src/Analyzer.cpp \
	../Source/Headers/Menu.h
	$(CC) $(CFLAGS) ../Source/Src/Analyzer.cpp

Simulator.o :../Source/Headers/Simulator.h ../Source/Src/Simulator.cpp \
	../Source/Headers/fileCoordinator.h ../Source/Headers/randomHelper.h
	$(CC) $(CFLAGS) ../Source/Src/Simulator.cpp

Iterator.o :../Source/Headers/Iterator.h ../Source/Src/Iterator.cpp \
	../Source/Headers/fileCoordinator.h 
	$(CC) $(CFLAGS) ../Source/Src/Iterator.cpp

rMatrix.o :../Source/Headers/rMatrix.h ../Source/Src/rMatrix.cpp \
	../Source/Headers/AbstractMatrix.h
	$(CC) $(CFLAGS) ../Source/Src/rMatrix.cpp

tMatrix.o :../Source/Headers/tMatrix.h ../Source/Src/tMatrix.cpp \
	../Source/Headers/rMatrix.h
	$(CC) $(CFLAGS) ../Source/Src/tMatrix.cpp

##### Other Commands
clean:
	\rm *.o $(PROGRAM)
cleanInput:
	cd ../Input/Simulated/; \rm *.txt
	
cleanSimulatedOutput:
	cd ../Output/Simulated/Entropies/; \rm *.txt
	cd ../Output/Simulated/Iterations/; \rm *.txt
	cd ../Output/Simulated/Weights/; \rm *.txt
	cd ../Output/Simulated/Time/; \rm *.txt
cleanProvidedOutput:
	cd ../Output/Provided/Entropies/; \rm *.txt
	cd ../Output/Provided/Iterations/; \rm *.txt
	cd ../Output/Provided/Weights/; \rm *.txt
	cd ../Output/Provided/Time/; \rm *.txt
cleanPlots:
	cd ../Output/Graphs/Entropies/; \rm *.eps
	cd ../Output/Graphs/Weights/; \rm *.eps

tar:
	cd ..; tar -cvf Analyzer.tar Source Input Output Release