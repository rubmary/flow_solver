#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include <fstream>
using namespace std;


map<char, int>colors;
vector <string> B;
vector <vector <vector <int> > > c, d;
vector < vector <int> > cnf;
int N, M, R, K, K1;
int total_var = 0;

int dirx0[] = { 0,  0,  0,  0,  0,  0, -1, 0, 1,  0};
int diry0[] = { 0,  0,  0,  0,  0,  0,  0, 1, 0, -1};

int dirx1[] = {-1, -1, -1,  0,  0,  1};
int diry1[] = { 0,  0,  0,  1,  1,  0};
int dirx2[] = { 0,  1,  0,  1,  0,  0};
int diry2[] = { 1,  0, -1,  0, -1, -1};

int valid0[][4] =
	{
		{}, {}, {}, {}, {}, {},
		{1, 3, 5, 8},
		{2, 4, 5, 9},
		{0, 1, 2, 6},
		{0, 3, 4, 7}
	};
int valid1[][4] = 
	{
		{1, 3, 5, 8},
		{1, 3, 5, 8},
		{1, 3, 5, 8},
		{2, 4, 5, 9},
		{2, 4, 5, 9},
		{0, 1, 2, 6},
	};

int valid2[][4] =
	{
		{2, 4, 5, 9},
		{0, 1, 2, 6},
		{0, 3, 4, 7},
		{0, 1, 2, 6},
		{0, 3, 4, 7},
		{0, 3, 4, 7}
	};

void read_board() {
	string s;
	while (cin >> s)
		B.push_back(s);
}

void map_colors() {
	N = B.size();
	M = B[0].size();
	R = 0;
	K = 10;
	K1 = 6;

	map <string, int>::iterator it;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++){
			char c = B[i][j];
			if (c != '.' && colors.find(c) == colors.end())
				colors[c] = R++;
		}
	}
}

void make_variables() {

	c = vector<vector <vector <int> > >
		(N, vector <vector <int> > (M, vector <int>(R)));
	d = vector<vector <vector <int> > >
		(N, vector <vector <int> > (M, vector <int>(K)));

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			for (int r = 0; r < R; r++)
				c[i][j][r] = ++total_var;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			for (int k = 0; k < K; k++)
				d[i][j][k] = ++total_var;
}

bool valid_cell(int r, int c) {
	return 0 <= r && r < N && 0 <= c && c < M;
}
void make_clauses() {

	vector <int> clause;
	int x0, y0, x1, y1, x2, y2;

	// Cada casilla tiene un color
	clause.resize(R);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++){
			for (int r = 0; r < R; r++)
				clause[r] = c[i][j][r];
			cnf.push_back(clause);
		}
	}

	// No hay una casillas con mas de un color
	clause.resize(2);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			for (int r1 = 0; r1 < R; r1++) {
				for (int r2 = r1 + 1; r2 < R; r2++) {
					clause[0] = -c[i][j][r1];
					clause[1] = -c[i][j][r2];
					cnf.push_back(clause);
				}
			}
		}
	}

	// Cada casilla tiene una direccion
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			clause.resize(0);
			for (int k = 0; k < K1; k++){
				x1 = i + dirx1[k];
				y1 = j + diry1[k];
				x2 = i + dirx2[k];
				y2 = j + diry2[k];
				if (valid_cell(x1, y1) && valid_cell(x2, y2))
					clause.push_back(d[i][j][k]);
			}
			for (int k = K1; k < K; k++) {
				x0 = i + dirx0[k];
				y0 = j + diry0[k];
				if (valid_cell(x0, y0))
					clause.push_back(d[i][j][k]);
			}			
			cnf.push_back(clause);
		}
	}

	// No hay una casillas con mas de una direccion
	clause.resize(2);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			for (int k1 = 0; k1 < K; k1++){
				for (int k2 = k1 + 1; k2 < K; k2++) {
					clause[0] = -d[i][j][k1];
					clause[1] = -d[i][j][k2];
					cnf.push_back(clause);
				}
			}			
		}
	}

	// Consistencia de colores de casillas en los caminos
	clause.resize(3);
	for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
		for (int r = 0; r < R; r++){
			clause[1] = -c[i][j][r];
			for (int k = K1; k < K; k++){
				clause[0] = -d[i][j][k];
				x0 = i + dirx0[k];
				y0 = j + diry0[k];
				if (valid_cell(x0, y0)) {
					clause[2] = c[x0][y0][r];
					cnf.push_back(clause);
				}
			}
			for (int k = 0; k < K1; k++) {
				clause[0] = -d[i][j][k];
				x1 = i + dirx1[k];
				y1 = j + diry1[k];
				if (valid_cell(x1, y1)) {
					clause[2] = c[x1][y1][r];
					cnf.push_back(clause);	
				}
				x2 = i + dirx2[k];
				y2 = j + diry2[k];
				if (valid_cell(x2, y2)) {
					clause[2] = c[x2][y2][r];
					cnf.push_back(clause);
				}
			}
		}
	}

	// Consistencia en la forma del camino
	for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
		for (int k = 0; k < K1; k++) {
				x1 = i + dirx1[k];
				y1 = j + diry1[k];
				x2 = i + dirx2[k];
				y2 = j + diry2[k];

				if (valid_cell(x1, y1) && valid_cell(x2, y2)) {
					clause.resize(1);
					clause[0] = -d[i][j][k];
					for (int s = 0; s < 4; s++)
						clause.push_back(d[x1][y1][valid1[k][s]]);
					
					cnf.push_back(clause);
					clause.resize(1);
					clause[0] = -d[i][j][k];
					for (int s = 0; s < 4; s++)
						clause.push_back(d[x2][y2][valid2[k][s]]);
					cnf.push_back(clause);
				}

		}
		for (int k = K1; k < K; k++) {
			clause.resize(1);
			clause[0] = -d[i][j][k];
			x0 = i + dirx0[k];
			y0 = j + diry0[k];
			if (valid_cell(x0, y0)) {
				for (int s = 0; s < 4; s++)
					clause.push_back(d[x0][y0][valid0[k][s]]);
			}
			cnf.push_back(clause);
		}
	}

	// Restricciones del tablero particular
	for (int i = 0; i < N; i++) for (int j = 0; j < M; j++){
		if (B[i][j] == '.')  for (int k = K1; k < K; k++)
			cnf.push_back(vector<int>(1, -d[i][j][k]));
		else {
			for (int k = 0; k < K1; k++)
				cnf.push_back(vector<int>(1, -d[i][j][k]));
			cnf.push_back(vector<int>(1, c[i][j][colors[B[i][j]]]));
		}
	}
}
int main() {
	read_board();
	map_colors();
	make_variables();
	make_clauses();
	int total_clauses = cnf.size();

	ofstream file("variables.txt");
	file << N << ' ' << M << ' ' << R;
	
	cout << "p cnf " << total_var << ' ' << total_clauses << endl;
	for (int i = 0; i < total_clauses; i++) {
		int size = cnf[i].size();
		for (int j = 0; j < size; j++)
			cout << cnf[i][j] << ' ';
		cout << 0 << endl;
	}
}