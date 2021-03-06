#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char **argv) {
	string name = argv[1];
	string run_codifier, run_decodifier, run_minisat, run_cycles;
	run_codifier   = "./codifier < puzzles/" + name + "> delta.txt";
	run_minisat    = "minisat delta.txt sol.txt";
	run_decodifier = "./decodifier " + name + " < sol.txt > solutions/sol_" + name;
	run_cycles = "./check_cycles < sol.txt";
	int system_answer = -1;
	
	system_answer = system(run_codifier.c_str());

	while (true) {

		system_answer = system(run_minisat.c_str());
		bool cycle = system(run_cycles.c_str());
		if (!cycle)
			break;
		
		ifstream delta("delta.txt"), cycles("cycles.txt");
		string _;
		int var, clauses, x;
		vector <int> clause;
		delta >> _ >> _ >> var >> clauses;
		vector <vector <int> > new_theory;
		
		for (int i = 0; i < clauses; i++) {
			clause.resize(0);
			while (delta >> x, x)
				clause.push_back(x);
			new_theory.push_back(clause);
		}

		int total_cycles, S = 0;
		cycles >> total_cycles;
		
		for (int i = 0; i < total_cycles; i++){
			clause.resize(0);
			cycles >> S;
			for (int j = 0; j < S; j++){
				cycles >> x;
				clause.push_back(x);
			}
			new_theory.push_back(clause);
		}


		delta.close();
		cycles.close();

		clauses += total_cycles;
		ofstream new_delta("delta.txt");
		new_delta << "p cnf " << var << ' ' << clauses << endl;
		for (int i = 0; i < clauses; i++){
			for (int j = 0; j < (int) new_theory[i].size(); j++)
				new_delta << new_theory[i][j] << ' ';
			new_delta << 0 << endl;
		}

	}
	
	system_answer = system(run_decodifier.c_str());
	// system_answer = system("make cleanData");
	if (system_answer != 0)
		exit(1);
}