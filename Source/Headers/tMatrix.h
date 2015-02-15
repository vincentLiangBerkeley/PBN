/**
 * @file tMatrix.h
 * 
 * @brief This file contains declaration of transition matrix class.
 *
 * The class tMatrix is defined in this file, it represents the transition
 * matrix whose solumn sums are one.
 *
 * @author Liang RuoChen
 * @version 2.1 09/04/2014
 * 
 */
#ifndef TMATRIX_H
#define TMATRIX_H 
#include <map>
#include <iomanip>
#include "rMatrix.h"


/**
 * \ingroup matrix
 * 
 * @class tMatrix
 * 
 * @brief Internal data structure representing a matrix that has constant column
 * sums.		
 *
 * This matrix inherit the "print" method from AbstractMatrix to print the matrix
 * as \f$n\times n\f$ matrix to an output stream. 
 *
 */

class tMatrix : public AbstractMatrix
{
public:
	tMatrix(int n = 1);

	/**
	 * Construct a tMatrix using an rMatrix instance. The matrices are the same, but
	 * this instance supports tMatrix operations.
	 *
	 * @note Typical usage : tMatrix transition(R);
	 */
	tMatrix(const rMatrix& base);

	/**
	 * Calculates the Frobinous module of the matrix as :
	 * \f$ \sqrt{\sum_{i, j}{a_{ij}^2}}\f$.
	 * 
	 * @return The module of the matrix
	 */
	double module();

	/**
	 * Set the ith row jth column entry to the given value.
	 * @param i  Row number;
	 * @param j  Column number;
	 * @param value  The value to set.
	 */
	void set(int i, int j, double value);

	/**
	 * Get the colth column of the matrix.
	 * @param col  Column number;
	 * @return The colth column as a map from int to double
	 */
	map<int, double> get(int col) const;

	/**
	 * Defines scalar multiplication on boolean matrix.
	 * @param  lhs  The boolean matrix to multiply on;
	 * @param  k  The scalar;
	 * @return A tMatrix instance as the result of the scalar multiplication
	 *
	 * @note Typical usage : @code tMatrix transition = tMatrix::times(R, k); @endcode
	 */
	static tMatrix times(rMatrix lhs, const double k);

	/**
	 * Defines addition between transition matrices.
	 *
	 * @note Typical usage : @code transition += anotherTransition; @endcode
	 */
	tMatrix& operator +=(const tMatrix& rhs);


	virtual void print(ostream& output);

	tMatrix(const tMatrix& copyFromMe);

	tMatrix& operator=(const tMatrix& rhs);

	~tMatrix();

private:
	/**
	 * A vector of map<int, double> storing the entries of the matrix.
	 * The matrix[j][i] represents the (i, j)th entry of the matrix.
	 *
	 * @note Only non-zero entries are stored, zero entries cannot be 
	 * found in any of the maps.
	 */
	vector<map<int, double> > matrix;
};

#endif