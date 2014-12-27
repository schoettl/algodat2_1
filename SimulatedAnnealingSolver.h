/*
 * SimulatedAnnealingSolver.h
 *
 *  Created on: 26.12.2014
 *      Author: jakob
 */

#ifndef SIMULATEDANNEALINGSOLVER_H_
#define SIMULATEDANNEALINGSOLVER_H_

#include <vector>

class SimulatedAnnealingSolver;

#include "Graph.h"

class SimulatedAnnealingSolver {
	Graph& graph;
	vector<Vertex*> cycle;
	int cycleLength;
	double lambda;

	void initializeCycleRandomly();
	int calculateLengthDifference(const Vertex* v1, const Vertex* v2, const Vertex* v3, const Vertex* v4);
	double sweep(int numberOfIterations);
public:
	SimulatedAnnealingSolver(Graph& graph);
	void calculateSolution();
	ostream& outputResult(ostream& outstream);
};

#endif /* SIMULATEDANNEALINGSOLVER_H_ */
