/** 
 * @file rMatrix.h
 * @brief This is the boolean matrix class
 *  
 * @author Liang RuoChen
 * @version 2.1 09/04/2014
 */

#ifndef RMATRIX_H
#define RMATRIX_H 
#include "AbstractMatrix.h"
#include <vector>

/**
 * \ingroup matrix
 * 
 * @class rMatrix
 * @brief This class holds the data needed for representing a boolean matrix.
 *
 * The instances of this class can be initiated with number of genes, and a 
 * vector of rows. It also implements the print method.
 * 
 */
class rMatrix : public AbstractMatrix
{
public: 
	/**
	 * Default constructor, creates an instance with random positions of 
	 * ones. 
	 */
	rMatrix(int n = 1);
	
	/**
	 * This constructor takes in a vector<int> as an input and generate 
	 * and instance of boolean matrix with the corresponding row positions
	 * being one.
	 */
	rMatrix(vector<int>& positions);

	//Copy constructor
	rMatrix(const rMatrix& copyFromMe);
	//Copy assignment
	rMatrix& operator=(const rMatrix& rhs);
	~rMatrix();

	int get(int i) const;
	virtual void print(ostream& output);
	/* data */

private:
	/// A vector<int> storing the positions of ones in each column
	vector<int> matrix;
};

#endif // RMATRIX_H