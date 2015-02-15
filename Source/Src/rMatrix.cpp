#include <math.h>	
#include <random>
#include "rMatrix.h"	

rMatrix::rMatrix(int n){
	size = pow(2, n);
	matrix = vector<int>(size, 0);	

	// Generate random positions
	random_device rd;
	mt19937	gen(rd());
	uniform_int_distribution<> dis(0, size - 1);
	for (int i = 0; i < size; ++i){
		matrix[i] = dis(gen);
	}
}

rMatrix::rMatrix(vector<int>& positions){
	size = positions.size();
	matrix = vector<int>(size, 0);
	for (int i = 0; i < size; ++i){
		matrix[i] = positions[i];
	}
}

rMatrix::rMatrix(const rMatrix& copyFromMe){
	size = copyFromMe.size;
	matrix = vector<int>(size, 0);
	for (int i = 0; i < size; ++i){
		matrix[i] = copyFromMe.matrix[i];
	}
}

rMatrix& rMatrix::operator = (const rMatrix& rhs){
	if(this == &rhs) return *this;
	else{
		if(size != rhs.size){
			this ->~rMatrix();
			size = rhs.size;
			matrix.resize(size, 0);
		}
		for (int i = 0; i < size; ++i){
			matrix[i] = rhs.matrix[i];
		}
	}
	return *this;
}

rMatrix::~rMatrix(){
	matrix.clear();
}

int rMatrix::get(int i) const{
	return matrix[i];
}

void rMatrix::print(ostream& output){
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			if(i == matrix[j]) output << 1 << " ";
			else output << 0 << " ";
			if(j == size - 1) output << endl;
		}
	}
}

