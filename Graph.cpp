/*
 * Graph.cpp
 *
 *  Created on: 04.11.2014
 *      Author: jakob
 */

#include <iostream>
#include <stack>
#include <climits>
#include <cassert>

#include "Graph.h"

Graph::Graph() : firstVertex(NULL), mst(NULL), rootOfMst(NULL) {

}

Graph::~Graph() {
	// Ecken und Kanten loeschen
	Vertex* v = firstVertex;
	while (v) {

		// Kanten loeschen
		Edge* e = v->getFirstEdge();
		while (e) {
			Edge* next = e->getNextEdge();
			delete e;
			e = next;
		}

		// Ecke loeschen
		Vertex* next = v->getNextVertex();
		delete v;
		v = next;
	}

	if (mst) {
		delete mst;
	}
}

// Test function
void outputTree(ostream& outstream, Vertex* v, int depth) {
	// Gibt alle Knoten auf gleicher Ebene in verkehrter Reihenfolge aus!
	outstream << v->getName() << endl;
	Edge* e = v->getFirstEdge();
	while (e) {
		for (int i = 0; i <= depth; i++) outstream << " ";
		outstream << e->getWeight() << " ";
		outputTree(outstream, e->getTargetVertex(), depth + 1);
		e = e->getNextEdge();
	}
}

void Graph::prim() {
	set<Vertex*> markedVertices;
	markedVertices.insert(firstVertex);

	if (mst) {
		delete mst;
	}
	mst = new Graph();
	rootOfMst = mst->insertVertex(firstVertex->getName());

	while (1) {
		int minWeight = INT_MAX;
		Vertex* startVertex;
		Vertex* targetVertex;

		for (set<Vertex*>::iterator vit = markedVertices.begin(); vit != markedVertices.end(); ++vit) {
			Edge* e = (*vit)->getFirstEdge();
			while (e) {
				// kuerzesten Weg von p nach q, wobei q noch nicht markiert
				if (markedVertices.find(e->getTargetVertex()) == markedVertices.end() && e->getWeight() < minWeight) {
					startVertex = *vit;
					targetVertex = e->getTargetVertex();
					minWeight = e->getWeight();
				}
				e = e->getNextEdge();
			}
		}
		if (minWeight < INT_MAX) {
			markedVertices.insert(targetVertex);

			// MST erweitern
			startVertex = mst->findVertex(startVertex->getName());
			targetVertex = mst->insertVertex(targetVertex->getName());
			startVertex->insertEdge(targetVertex, minWeight);
		} else {
			break;
		}
	}
}

void Graph::cycle(ostream& outstream) {
	//outputTree(outstream, rootOfMst, 0); return; // Test
	// durch prim() erzeugten MST/Baum per NLR durchgehen und mit Entfernungen ausgeben
	outstream << rootOfMst->getName();
	Vertex* lastVertex = traverseChilds(rootOfMst, outstream);
	// Zyklus schliessen
	Edge* edgeBetween = findEdgeBetween(lastVertex->getName(), rootOfMst->getName());
	outstream << " - " << edgeBetween->getWeight() << " - " << rootOfMst->getName() << endl;
}

// Recursively traverse tree per NLR scheme; Return the last visited vertex.
Vertex* Graph::traverseChilds(Vertex* parentVertex, ostream& outstream) {
	// NLR Schema heisst: Weg zu Nachbarknoten ueber Elternknoten wird durch direkte Verbindung ersetzt.
	stack<Edge*> nodes;

	// Stack fuellen
	Edge* e = parentVertex->getFirstEdge();
	while (e) {
		nodes.push(e);
		e = e->getNextEdge();
	}

	Vertex* lastVisitedVertex = parentVertex;

	// Stack auslesen
	while (!nodes.empty()) {
		e = nodes.top();
		nodes.pop();

		Vertex* nextVertex = e->getTargetVertex();
		Edge* edgeBetween = findEdgeBetween(lastVisitedVertex->getName(), nextVertex->getName());
		outstream << " - " << edgeBetween->getWeight() << " - " << nextVertex->getName();
		lastVisitedVertex = traverseChilds(nextVertex, outstream);
	}

	return lastVisitedVertex;
}

Edge* Graph::findEdgeBetween(const Vertex* v1, const Vertex* v2) {
	Edge* e = v1->getFirstEdge();
	while (e) {
		if (e->getTargetVertex() == v2) {
			return e;
		}
		e = e->getNextEdge();
	}
	return NULL;
}

Edge* Graph::findEdgeBetween(const string& v1, const string& v2) {
	return findEdgeBetween(findVertex(v1), findVertex(v2));
}
