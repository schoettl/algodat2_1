/*
 * Vertex.h
 *
 *  Created on: 28.10.2014
 *      Author: jakob
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include <string>

class Edge;

#include "Base.h"
#include "Edge.h"

using namespace std;

class Vertex: public Base {
	string name;
public:
	Vertex(const string& name, Vertex* nextVertex);
	virtual ~Vertex();

	string getName() const {
		return name;
	}

	Vertex* getNextVertex() const {
		return dynamic_cast<Vertex*>(pointer1);
	}

	Edge* getFirstEdge() const {
		return (Edge*) pointer2;
	}

	Edge* insertEdge(Vertex* targetVertex, int weight);
};

#endif /* VERTEX_H_ */
