/** 
 * @file AbstractMatrix.h
 * @brief This is an abstract class/interface for matrix.
 *
 * \defgroup matrix Basic Matrices
 * @brief This group is the basic internal data structure of this application.
 * 
 * This group is the fundamental data structures used to save/load matrices
 * and perform necessary computations.
 *
 */
#ifndef ABSTRACT_MATRIX_H
#define ABSTRACT_MATRIX_H 


#include <iostream>
using namespace std;

/**
 *
 * \ingroup matrix
 * @class AbstractMatrix
 * 
 * @brief This class defines some of the basic operations we need for
 * our matrix.
 *
 * This is the basic abstract square matrix class, and all Boolean Network 
 * matrix and transition matrix should inherit from this class.
 *
 */
class AbstractMatrix
{
public:
	/**
	 * Simple getter for the matrix, suppose the matrix is constructed with
	 * \f$n\f$ genes, then the size is \f$2^n\f$.
	 * @return The number of rows for the matrix
	 */
	virtual int getSize() const {return size;}

	/**
	 * Print the matrix in a n by n matrix form to the output stream
	 * @param output The stream for output
	 */
	virtual void print(ostream& output) = 0;
	
	virtual ~AbstractMatrix(){};
	
protected:
	/**
	 * The size of the square matrix, inherited by its children.
	 */
	int size;
};

#endif // ABSTRACT_MATRIX_H