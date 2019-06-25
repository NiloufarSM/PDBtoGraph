//============================================================================
// Name        : Main.cpp
// Author      : Niloufar Seyed Majidi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <cmath>
#include "Parser.h"
#include "PDB.h"
#include "Graph.h"
#include <time.h>
using namespace std;

#define DEBUG_MODE 1
#define THRESHOLD 8
vector<string> splitstr(const string& str, const string& delim);

float dist(float x1, float y1, float z1, float x2, float y2, float z2);

int main(int argc, const char * argv[]) {
	clock_t tStart = clock();
	string file_path = argv[1];
	string file_name = file_path;
//	(file_name.erase(0, 16)).erase(4, 4);

//(file_name.erase(0, 47)).erase(4, 4);
	//file_name.erase(5, 4);
	cout << "filename: " << file_name << endl;
	ofstream protein;
	ofstream subprotein;
	//170,192,193,259,261
	protein.open("graphs/" + file_name + ".grf");
	//subprotein.open(file_name + ".sub.grf");
	/*cout << "Please enter the PDB file address: ";
	 cin >> PDBFileName;*/
	//parsing the PDB file
	//string CompletePDBFileName = PDBFileName;
	cout << file_path;
	Parser myParser(file_path);

	if ( DEBUG_MODE == 1) {
		cout << "--we have created the parser object with pdb file" + file_path
				<< endl;
		//myParser.printResult();
	}

	PDB myPDB(myParser);
	
	/*
	 cout << "Please select the residues you want from the PDB (comma separated)"
	 << endl;
	 string selectedResidues;
	 cin >> selectedResidues;
	 vector<string> subString = splitstr(selectedResidues, ",");
	 vector<int> selected_residues;
	 for (string i : subString) {
	 selected_residues.push_back(myPDB.getRealNumber(stoi(i)));
	 }
	 if ( DEBUG_MODE == 1) {

	 for (int b = 0; b < selected_residues.size(); b++) {
	 cout << "here";
	 cout << selected_residues.at(b) << endl;
	 cout << "tohere";
	 }
	 }
	 if (DEBUG_MODE == 1) {
	 for (string i : subString) {
	 cout << i << endl;
	 int index = stoi(i);
	 //cout
	 //<< myParser.models.at(0).chains.at(0).aminos.at(index).numberOfAtoms;
	 }
	 }
	 */
	//construction of graph from PDB file
	Graph mygraph(0);
	float x1, y1, z1;
	float x2, y2, z2;
	float d;
	protein << myPDB.getNumberOfAminos() << "\n";
	cout << "number of aminos: " << myPDB.getNumberOfAminos();
	for (int i = 0; i < myPDB.getNumberOfAminos(); i++) {
		string amino = myPDB.getAllAminos(i);
		protein << i << " " << amino << " " << myPDB.aminosNumber.at(i) 
			<< myPDB.aminosChain.at(i)<< "\n";
		mygraph.addNode(amino);
	}
	for (int i = 0; i < myPDB.getNumberOfAminos(); i++) {
		myPDB.getXYZOfAmino(i, &x1, &y1, &z1);
		vector<int> end;
		vector<float> dists;
		for (int j = 0; j < myPDB.getNumberOfAminos(); j++) {
			if (i != j) {
				myPDB.getXYZOfAmino(j, &x2, &y2, &z2);
				d = dist(x1, y1, z1, x2, y2, z2);
				if (d < THRESHOLD) {
					//if (myPDB.getAllAminos(i) > myPDB.getAllAminos(j)) {
					mygraph.addEdge(myPDB.getAllAminos(i),
							myPDB.getAllAminos(j));
					/*else {
					 cout << myPDB.getAllAminos(j) << " > "
					 << myPDB.getAllAminos(i) << " ";
					 mygraph.addEdge(myPDB.getAllAminos(j),
					 myPDB.getAllAminos(i));
					 }*/
					end.push_back(j);
					dists.push_back(d);

				}
				if ( DEBUG_MODE == 1) {

					//cout << i << "and" << j << "Distance: " << d << endl;
					//}
				}
			}
		}
		protein << end.size() << "\n";
		for (int j = 0; j < end.size(); j++) {
			protein << i << " " << end.at(j) << " " << dists.at(j) << "\n";
		}

	}
	protein.close();

	//mygraph.connectedComponents();
	/*
	 Graph mySubgraph(0);
	 float sx1, sy1, sz1;
	 float sx2, sy2, sz2;
	 float sd;
	 //vector<string> selectedAminos;
	 //130,131,132,127,128,126,129,133,134
	 subprotein << selected_residues.size() << endl;
	 for (int i = 0; i < selected_residues.size(); i++) {
	 string amino = myPDB.getAllAminos(selected_residues.at(i));
	 subprotein << i << " " << amino << " " << i << endl;
	 }
	 for (int i = 0; i < selected_residues.size(); i++) {
	 vector<int> end;
	 string amino = myPDB.getAllAminos(selected_residues.at(i));
	 mySubgraph.addNode(amino);
	 for (int j = 0; j < selected_residues.size(); j++) {
	 if (i != j) {
	 myPDB.getXYZOfAmino(selected_residues.at(i), &sx1, &sy1, &sz1);
	 myPDB.getXYZOfAmino(selected_residues.at(j), &sx2, &sy2, &sz2);
	 d = dist(sx1, sy1, sz1, sx2, sy2, sz2);
	 if (d < THRESHOLD) {
	 if (myPDB.getAllAminos(selected_residues.at(i))
	 > myPDB.getAllAminos(selected_residues.at(j))) {
	 cout << myPDB.getAllAminos(selected_residues.at(i))
	 << " > "
	 << myPDB.getAllAminos(selected_residues.at(j))
	 << " ";
	 mySubgraph.addEdge(
	 myPDB.getAllAminos(selected_residues.at(i)),
	 myPDB.getAllAminos(selected_residues.at(j)));
	 *else {
	 cout << myPDB.getAllAminos(selected_residues.at(j))
	 << " > "
	 << myPDB.getAllAminos(selected_residues.at(i))
	 << " ";
	 mySubgraph.addEdge(
	 myPDB.getAllAminos(selected_residues.at(j)),
	 myPDB.getAllAminos(selected_residues.at(i)));}*
	 end.push_back(j);
	 }
	 }
	 if ( DEBUG_MODE == 0) {

	 cout << i << "and" << j << "Distance: " << d << endl;
	 }
	 }
	 }
	 subprotein << end.size() << endl;
	 for (int j : end) {
	 subprotein << i << " " << j << endl;

	 }
	 }*/
	printf("Time taken: %.2fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
	return 0;
}
//Computing Euclidean Distance
float dist(float x1, float y1, float z1, float x2, float y2, float z2) {

	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2)));
}
//split the input string(index of selected residues)
vector<string> splitstr(const string& str, const string& delim) {
	vector<string> tokens;
	size_t prev = 0, pos = 0;
	do {
		pos = str.find(delim, prev);
		if (pos == string::npos)
			pos = str.length();
		string token = str.substr(prev, pos - prev);
		if (!token.empty())
			tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}
