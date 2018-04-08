#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

string dir[] = {"└", "│", "┘", "┌", "─", "┐", "c", "c", "c", "c", "c"};
char color[] = {'R', 'B', 'Y', 'G', 'O', 'C', 'M', 'm', 'P', 'A', 'W', 'g', 'T', 'b', 'c', 'p' };

vector < vector <int> > D, C;
int main() {

	string s;
	cin >> s;
	int val;
	int N = -1, M = -1, R = -1;
	ifstream file("variables.txt");
	file >> N >> M >> R;

	D = vector< vector <int> > (N, vector<int> (M));
	C = vector< vector <int> > (N, vector<int> (M));
	
	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++) {
			for (int r = 0; r < R; r++){
				cin >> val;
				if (val > 0)
					C[i][j] = r;
			}
		}
	}

	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++) {
			for (int k = 0; k < 10; k++) {
				cin >> val;
				if (val > 0)
					D[i][j] = k;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			if (D[i][j] >= 6)
				cout << color[C[i][j]];
			else
				cout << dir[D[i][j]];
		cout << endl;
	}
}