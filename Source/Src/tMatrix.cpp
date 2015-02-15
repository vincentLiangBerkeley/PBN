/*
 * File: tMatrix.cpp
 * ----------------
 * This file implements the tMatrix.h interface.
 */

#include "tMatrix.h"
#include <math.h>
static const double THRESHOLD = 0.0001;

tMatrix::tMatrix(int n){
	size = pow(2, n);
	matrix = vector<map<int, double> >(size);	
}

tMatrix::tMatrix(const tMatrix& copyFromMe){
	size = copyFromMe.size;
	matrix = vector<map<int, double> >(size);
	for (int i = 0; i < size; ++i){
		matrix[i] = copyFromMe.matrix[i];
	}
}

tMatrix::tMatrix(const rMatrix& base){
	size = base.getSize();
	matrix = vector<map<int, double> >(size);
	for (int i = 0; i < size; ++i){
		int position = base.get(i);
		matrix[i].insert(pair<int, double>(position, double(1)));
	}
}

tMatrix& tMatrix::operator = (const tMatrix& rhs){
	if(this == &rhs) return *this;
	else{
		if(size != rhs.size){
			this ->~tMatrix();
			size = rhs.size;
			matrix.resize(size);
		}
		for (int i = 0; i < size; ++i){
			matrix[i] = rhs.matrix[i];
		}
	}
	return *this;
}

tMatrix::~tMatrix(){
	matrix.clear();
}

map<int, double> tMatrix::get(int col) const{
	return matrix[col];
}

void tMatrix::set(int i, int j, double value){
	//If matrix[j] contains value at row i, replace it
	if(matrix[j].find(i) != matrix[j].end()) matrix[j][i] = value;
	
	//Else insert the key - value pair into the matrix
	else matrix[j].insert(pair<int, double>(i, value));
}

double tMatrix::module(){
	double module = 0;
	for (int col = 0; col < size; ++col){
		map<int, double> column = matrix[col];
		for (map<int, double>::iterator i = column.begin(); i != column.end(); ++i)
		{
			module += (i->second * i ->second);
		}
	}
	return sqrt(module);
}

void tMatrix::print(ostream& output){
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			output.width(6);
			output.precision(4);
			output.setf(ios::fixed);
			if(matrix[j].find(i) != matrix[j].end()) output << matrix[j][i] << "\t";
			else output << double(0) << "\t";
			if(j == size - 1) output << endl;
		}
	}
}

tMatrix tMatrix::times(rMatrix lhs, const double k){
	tMatrix tm = tMatrix(lhs);
	for (int col = 0; col < lhs.getSize(); ++col){
		int row = lhs.get(col);
		
		// Set the row, col value of the matrix to k
		tm.set(row, col, k);
	}
	return tm;
}


tMatrix& tMatrix::operator += (const tMatrix& rhs){
	for (int col = 0; col < rhs.getSize(); ++col){
		map<int, double> column = rhs.get(col);
		for (std::map<int, double>::iterator i = column.begin(); i != column.end(); ++i)
		{
			int row = i ->first;

			// Whether the position is zero or not
			if(matrix[col].find(row) != matrix[col].end()){
				matrix[col][row] += i ->second;
				if (matrix[col][row] <= THRESHOLD)
					matrix[col].erase(row);
			} 
			else matrix[col].insert(pair<int, double>(row, i ->second));
		}
	}
	return *this;
}