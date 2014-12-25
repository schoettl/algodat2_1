/*
 * Vertex.cpp
 *
 *  Created on: 28.10.2014
 *      Author: jakob
 */

#include "Vertex.h"

Vertex::Vertex(const string& name, Vertex* nextVertex) : Base(nextVertex, NULL), name(name) {

}

Vertex::~Vertex() {

}

Edge* Vertex::insertEdge(Vertex* targetVertex, int weight) {
	Edge* nextEdge = dynamic_cast<Edge*>(pointer2);
	pointer2 = new Edge(targetVertex, nextEdge, weight);
	return dynamic_cast<Edge*>(pointer2);
}
