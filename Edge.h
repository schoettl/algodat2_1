/*
 * Edge.h
 *
 *  Created on: 28.10.2014
 *      Author: jakob
 */

#ifndef EDGE_H_
#define EDGE_H_

class Vertex;

#include "Base.h"
#include "Vertex.h"

class Edge: public Base {
	int weight;
public:
	Edge(Vertex* targetVertex, Edge* nextEdge, int weight);
	virtual ~Edge();

	int getWeight() const {
		return weight;
	}

	Vertex* getTargetVertex() const {
		return (Vertex*) pointer2;
	}

	Edge* getNextEdge() const {
		return (Edge*) pointer1;
	}
};

#endif /* EDGE_H_ */
