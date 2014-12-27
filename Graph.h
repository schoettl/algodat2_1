/*
 * Graph.h
 *
 *  Created on: 04.11.2014
 *      Author: jakob
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <iostream>
#include <set>

class Graph;

#include "Vertex.h"
#include "SimulatedAnnealingSolver.h"

using namespace std;

class Graph {
	Vertex* firstVertex;
	Graph* mst;
	Vertex* rootOfMst;
	Vertex* traverseChilds(Vertex* currentVertex, ostream& outstream); // fuer cycle()
	// start- and targetVertex must exist.
	Edge* findEdgeBetween(const Vertex* v1, const Vertex* v2);
	Edge* findEdgeBetween(const string& v1, const string& v2);
	int getVertexCount() {
		int n = 0;
		Vertex* v = firstVertex;
		while (v) {
			v = v->getNextVertex();
			n++;
		}
		return n;
	}
public:
	friend SimulatedAnnealingSolver;

	Graph();
	virtual ~Graph();

	Vertex* insertVertex(const string& name) {
		return (firstVertex = new Vertex(name, firstVertex));
	}

	Vertex* findVertex(const string& name) const {
		Vertex* v = firstVertex;
		while (v && v->getName() != name) {
			v = v->getNextVertex();
		}
		return v;
	}

	void insertEdge(Vertex* v1, Vertex* v2, int weight) {
		v2->insertEdge(v1, weight);
		v1->insertEdge(v2, weight);
	}

	void prim();

	void cycle(ostream& outstream);

};

#endif /* GRAPH_H_ */
