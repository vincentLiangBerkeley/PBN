#include "Simulator.h"

int main(){
	Simulator mySimulator(3, 1);
	mySimulator.setFileSuffix("testOnly");
	mySimulator.simulate();
	mySimulator.getMatrix()->print(cout);
	return 0;
}