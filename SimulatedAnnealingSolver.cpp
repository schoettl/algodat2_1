/*
 * SimulatedAnnealingSolver.cpp
 *
 *  Created on: 26.12.2014
 *      Author: jakob
 */

#include <algorithm>
#include <utility>
#include <cstdlib>
#include <cmath>

using namespace std;

#define SWAP_AND_UPDATE \
	swap(v2, v3);\
	cycleLength += diff;\
	numberOfAccepted++;

#include "SimulatedAnnealingSolver.h"

SimulatedAnnealingSolver::SimulatedAnnealingSolver(Graph& graph) :
	graph(graph), cycleLength(0) {
	cycle.reserve(graph.getVertexCount());
}

void SimulatedAnnealingSolver::calculateSolution() {
	initializeCycleRandomly();

	double accepted = 0;
	int sweepCounter;

	// Warm-up
	lambda = 10;
	const int maxNumberOfInitSweeps = 100;
	const int initSweepIterations = 100;
	for (sweepCounter = 0; sweepCounter < maxNumberOfInitSweeps; sweepCounter++) {
		accepted = sweep(initSweepIterations);
		if (accepted > 0.8) {
			break;
		}
		lambda /= 1.5;
	}
	if (sweepCounter == maxNumberOfInitSweeps) {
		cerr << "warning: max number of init sweeps reached" << endl;
	}

	// Annealing
	const int maxNumberOfRunSweeps = 10000;
	const int runSweepIterations = 10000;
	for (sweepCounter = 0; sweepCounter < maxNumberOfRunSweeps; sweepCounter++) {
		accepted = sweep(runSweepIterations);
		if (accepted < 0.001) {
			break;
		}
		lambda *= 1.01;
	}
	if (sweepCounter == maxNumberOfRunSweeps) {
		cerr << "warning: max number of run sweeps reached" << endl;
	}
}

double SimulatedAnnealingSolver::sweep(int numberOfIterations) {
	int numberOfAccepted = 0;
	for (int i = 0; i < numberOfIterations; i++) {
		const int n = cycle.size();
		int r = rand() % n;
		const Vertex* const & v1 = cycle[r];
		Vertex*& v2 = cycle[++r % n];
		Vertex*& v3 = cycle[++r % n];
		const Vertex* const & v4 = cycle[++r % n];
		int diff = calculateLengthDifference(v1, v2, v3, v4);
		if (diff < 0) {
			SWAP_AND_UPDATE;
		} else {
			double propability = exp(-lambda * diff) * RAND_MAX;
			if (rand() < propability) {
				SWAP_AND_UPDATE;
			}
		}
	}
	return (double) numberOfAccepted / numberOfIterations;
}

ostream& SimulatedAnnealingSolver::outputResult(ostream& outstream) {
	vector<Vertex*>::iterator it = cycle.begin();
	Vertex* first = *it;
	Vertex* prev = first;
	for (++it; it != cycle.end(); ++it) {
		Edge* edgeBetween = graph.findEdgeBetween(prev, *it);
		outstream << prev->getName() << " - " << edgeBetween->getWeight() << " - ";

		prev = *it;
	}
	// Zyklus schliessen
	Edge* edgeBetween = graph.findEdgeBetween(prev, first);
	outstream << prev->getName() << " - " << edgeBetween->getWeight() << " - " << first->getName() << endl;
	return outstream;
}

void SimulatedAnnealingSolver::initializeCycleRandomly() {
	// Zyklus erstellen
	Vertex* v = graph.firstVertex;
	while (v) {
		cycle.push_back(v);
		v = v->getNextVertex();
	}

	// Gewichte aufaddieren
	vector<Vertex*>::iterator it = cycle.begin();
	Vertex* first = *it;
	Vertex* prev = first;
	for (++it; it != cycle.end(); ++it) {
		cycleLength += graph.findEdgeBetween(prev, *it)->getWeight();
		prev = *it;
	}
	cycleLength += graph.findEdgeBetween(prev, first)->getWeight();

	// Zyklus verwürfeln
	random_shuffle(cycle.begin(), cycle.end());
}

int SimulatedAnnealingSolver::calculateLengthDifference(const Vertex* v1, const Vertex* v2, const Vertex* v3, const Vertex* v4) {
	int difference = 0;
	difference -= graph.findEdgeBetween(v1, v2)->getWeight() + graph.findEdgeBetween(v3, v4)->getWeight();
	difference += graph.findEdgeBetween(v1, v3)->getWeight() + graph.findEdgeBetween(v2, v4)->getWeight();
	return difference;
}
