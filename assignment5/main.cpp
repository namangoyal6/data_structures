#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <cctype>
#include <algorithm>

#include "Graph.h"

using namespace std;

string removeStartEndWhiteSpace(const string& s);

template <typename T>
void parseInput(Graph<T>& G);

int main(){
	Graph<string> G;

	parseInput(G);

	G.print();

	return 0;
}

string removeStartEndWhiteSpace(const string& s){

	int i,j;
	for (i = 0; i< s.size() && isspace(s[i]); i++) {}
	for (j = s.size() -1; j > i && isspace(s[j]); j--) {}

	return s.substr(i, j-i+1);
}

template <typename T>
void parseInput(Graph<T>& G){
	ifstream input;
	input.open("countries.dat");

	string line;
	string country_name;
	string neighbour_profile;
	string neighbour_name;
	double border;

	while(getline(input,line)){		
		stringstream input_stream(line);

		bool isRead = (getline(input_stream, country_name, '>'));
		if (isRead){

			input_stream.get();
			country_name = removeStartEndWhiteSpace(country_name);
			bool countryExist = (country_name.size() > 0) ? true : false;

			if (countryExist){

				bool hasANeighbour = false;

				while(getline(input_stream, neighbour_profile, ';')){

					neighbour_profile = removeStartEndWhiteSpace(neighbour_profile);
					bool neighbourExist = (neighbour_profile.size() > 0) ? true : false;

					if (neighbourExist){
						
						hasANeighbour = true;

						int indexDist;
						for (indexDist=0; indexDist< neighbour_profile.size() && neighbour_profile[indexDist] != ':'; indexDist++){}

						neighbour_name = neighbour_profile.substr(0,indexDist);
						neighbour_name = removeStartEndWhiteSpace(neighbour_name);

						bool hasBorder = false;
						border = 0;

						if (neighbour_name.size() < neighbour_profile.size()){
							string Distance = neighbour_profile.substr(indexDist+1, string::npos);
							Distance = removeStartEndWhiteSpace(Distance);

							if (Distance.size() > 2){
								Distance = Distance.substr(0,Distance.size()-2);
								Distance = removeStartEndWhiteSpace(Distance);
								Distance.erase(remove(Distance.begin(), Distance.end(), ','), Distance.end());

								if (Distance.size()){
									hasBorder = true;
									border = atof(Distance.c_str());								
								}
							}
						}

						G.addEdge(country_name, neighbour_name, border);
						
					}
				}

				if (!hasANeighbour){
					G.addVertex(country_name);
				}

			}

		}

	}
	input.close();
}