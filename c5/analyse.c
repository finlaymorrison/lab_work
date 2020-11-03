/*
 *         File: analyse.c
 *       Author: Steve Gunn
 *      License: MIT License
 *         Date: 27th October 2018
 *  Description: Program to read in a netlist file of a circuit, perform modified nodal analysis and display the result.
 */

#include <stdio.h>
#include <stdlib.h>
//#include "circuit.h"
#include "vector.h"
#include "matrix.h"

int main(int argc, char *argv[])
{
	Matrix mat = createMatrixFromFile("example.mat");
	printMatrix(mat);
	/*
	Circuit c;	
	if (argc == 2)
	{
		
	} 
	else 
		printf("Syntax: %s <filename>\n", argv[0]);
	*/
	return EXIT_SUCCESS;
}



