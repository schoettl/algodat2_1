/*
 * Edge.cpp
 *
 *  Created on: 28.10.2014
 *      Author: jakob
 */

#include "Edge.h"

Edge::Edge(Vertex* targetVertex, Edge* nextEdge, int weight) :
		Base(nextEdge, targetVertex), weight(weight) {

}

Edge::~Edge() {

}

