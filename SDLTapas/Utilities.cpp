/*
* Utilities.cpp
*
* See header for more information
*
*/



//-----------------------------------------------------------------------------------------------------------
// We'll need these
//-----------------------------------------------------------------------------------------------------------
#include "Utilities.h"



//-----------------------------------------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------------------------------------
int Utilities::cycle(int* pValue, int lower, int upper, int delta) {

	// Cycles a value in the given range (modular arithmetic increment)
	// Updates the value pointed to by the first argument and returns it

	// The value is restricted to the half-open interval [lower, upper); the upper bound is exclusive.

	// TODO: Useful overloads

	// Are all these parentheses really needed?
	// I'll have to look up the precedence rules
	(*pValue) = (((*pValue) + delta) % (upper-lower)) + lower;

	return (*pValue);

}