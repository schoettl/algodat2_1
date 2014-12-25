/*
 * Algorithmen und Datenstrukturen II
 * Praktikum -- Uebung 1
 *
 * Jakob Schoettl <jschoett@hm.edu>
 * 
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>

#include "Graph.h"

using namespace std;

void operationComplete(const string& message);
Vertex* findOrInsertVertex(Graph& g, const string& vertexName);
void readGraphFromFile(Graph& graph, const string& filename);
void insertVertex(Graph& g);
Vertex* promptForExistingVertex(const Graph& g);
void insertEdge(Graph& g);
void showMenu();
void testGraph(Graph& graph);


int main(int argc, char** argv) {
	cout << "Algorithmen und Datenstrukturen II" << endl
	     << "Praktikum -- Uebung 1" << endl
	     << "Jakob Schoettl <jschoett@hm.edu>" << endl << endl
	     << "Usage: algraph [GRAPH_DESCRIPTION_FILE]" << endl << endl;

	Graph graph;

	if (argc > 1) {
		readGraphFromFile(graph, argv[1]);
	} //else testGraph(graph);

	showMenu();

	while (1) {
		cout << "Coose an option: ";
		char option;
		cin >> option;
		switch (option) {
		case 'm':
			showMenu();
			break;
		case 'v':
			insertVertex(graph);
			break;
		case 'e':
			insertEdge(graph);
			break;
		case 'c':
			graph.prim();
			graph.cycle(cout);
			operationComplete("Ready.");
			break;
		case 'q':
			return 0;
		default:
			operationComplete("Invalid option.");
			break;
		}
	}
}


void operationComplete(const string& message) {
	cout << message << endl << endl;
}

Vertex* findOrInsertVertex(Graph& g, const string& vertexName) {
	Vertex* v = g.findVertex(vertexName);
	if (!v) {
		v = g.insertVertex(vertexName);
	}
	return v;
}

void readGraphFromFile(Graph& graph, const string& filename) {
	ifstream infile(filename.c_str());
	string line;
	while (getline(infile, line)) {
		istringstream lineStream(line);
		string name1, name2;
		int weight;
		lineStream >> name1 >> weight >> name2;
		Vertex* a = findOrInsertVertex(graph, name1);
		Vertex* b = findOrInsertVertex(graph, name2);
		graph.insertEdge(a, b, weight);
	}
	operationComplete("Read graph description file.");
}

void insertVertex(Graph& g) {
	string name;
	cout << "Choose a name: ";
	cin >> name;
	while (g.findVertex(name)) {
		cout << "A vertex with this name already exists." << endl
		     << "Try again: ";
		cin >> name;
	}

	g.insertVertex(name);
	operationComplete("Inserted vertex.");
}

// Prompt for an existing vertex. Return NULL when no name is entered.
Vertex* promptForExistingVertex(const Graph& g) {
	string name;
	cout << "Name a vertex: ";
	cin >> name;
	Vertex* v = NULL;
	while (!(v = g.findVertex(name))) {
		cout << "This vertex does not exist." << endl
			 << "Try again: ";
		cin >> name;
	}
	return v;
}

void insertEdge(Graph& g) {
	Vertex* v1 = promptForExistingVertex(g);
	Vertex* v2 = promptForExistingVertex(g);
	while (v1 == v2 && v2 != NULL) {
		cout << "Second vertex must differ from first one." << endl;
		v2 = promptForExistingVertex(g);
	}
	if (v1 == NULL || v2 == NULL) {
		operationComplete("Aborted.");
		return;
	}

	int weight;
	cout << "Specify the weight: ";
	cin >> weight;

	g.insertEdge(v1, v2, weight);
	operationComplete("Inserted edge.");
}

void showMenu() {
	cout << "Interactive menu:" << endl
	     << "m Show this menu" << endl
	     << "v Insert vertex" << endl
	     << "e Insert edge" << endl
	     << "c Calculate solution for the" << endl
	     << "  traveling salesman problem" << endl
	     << "q Quit" << endl << endl;
}

void testGraph(Graph& graph) {
	graph.insertVertex("v1");
	graph.insertVertex("v2");
	graph.insertVertex("v3");

	Vertex* v1 = graph.findVertex("v1");
	Vertex* v2 = graph.findVertex("v2");
	Vertex* v3 = graph.findVertex("v3");

	graph.insertEdge(v1, v2, 10);
	graph.insertEdge(v1, v3, 20);
	graph.insertEdge(v2, v3, 30);

	//assert(graph.findEdgeBetween(v1, v2)->getWeight() == 10);
	//assert(graph.findEdgeBetween(v1, v3)->getWeight() == 20);
	//assert(graph.findEdgeBetween(v2, v3)->getWeight() == 30);

	graph.prim();
	graph.cycle(cout);
}
