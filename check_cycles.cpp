#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int dirx0[] = { 0,  0,  0,  0,  0,  0, -1, 0, 1,  0};
int diry0[] = { 0,  0,  0,  0,  0,  0,  0, 1, 0, -1};

int dirx1[] = {-1, -1, -1,  0,  0,  1};
int diry1[] = { 0,  0,  0,  1,  1,  0};
int dirx2[] = { 0,  1,  0,  1,  0,  0};
int diry2[] = { 1,  0, -1,  0, -1, -1};

vector <vector <bool> > vis;
vector <vector <int>  > D;
vector <vector <int>  > valSol;
int R, N, M, K1 = 6, K = 10;
vector <int> cycle;
vector <vector <int> > cycles(0);

bool valid_cell(int r, int c) {
	return 0 <= r && r < N && 0<= c && c < M;
}
void dfs(int i, int j) {
	if (!valid_cell(i, j))
		return;
	
	if (vis[i][j])
		return;

	vis[i][j] = true;
	int x0, y0, x1, y1, x2, y2;
	int k = D[i][j];
	if (k < K1) {		
		x1 = i + dirx1[k];
		y1 = j + diry1[k];
		x2 = i + dirx2[k];
		y2 = j + diry2[k];
		dfs(x1, y1);
		dfs(x2, y2);
	}else {
		x0 = i + dirx0[k];
		y0 = j + diry0[k];
		dfs(x0, y0);
	}
}

void make_cycles(int i, int j) {
	if (!valid_cell(i, j))
		return;
	if (vis[i][j])
		return;

	cycle.push_back(valSol[i][j]);
	vis[i][j] = true;
	int x1, y1, x2, y2;
	int k = D[i][j];
	x1 = i + dirx1[k];
	y1 = j + diry1[k];
	x2 = i + dirx2[k];
	y2 = j + diry2[k];
	make_cycles(x1, y1);
	make_cycles(x2, y2);
}
bool solve(){
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (D[i][j] >= K1 && !vis[i][j])
				dfs(i, j);
	bool answer = false;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++)
			if (!vis[i][j]){
				answer = true;
				cycle.resize(0);
				make_cycles(i, j);
				cycles.push_back(cycle);
			}
	}
			
	return answer;
}

int main(int argc, char **argv){
	ifstream file("variables.txt");
	ofstream f_cycles("cycles.txt");
	file >> N >> M >> R;
	string _;
	cin >> _;
	D = vector< vector <int> > (N, vector<int> (M));
	valSol = vector< vector <int> > (N, vector<int> (M));
	vis = vector< vector <bool> > (N, vector<bool> (M, false));
	int val;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++) {
			for (int r = 0; r < R; r++){
				cin >> val;
			}
		}
	}

	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++) {
			for (int k = 0; k < K; k++) {
				cin >> val;
				if (val > 0){
					D[i][j] = k;
					valSol[i][j] = -val;
				}
			}
		}
	}

	bool sol = solve();
	int total_cycles = cycles.size();
	f_cycles << total_cycles << endl;
	for (int i = 0; i < total_cycles; i++) {
		int S = cycles[i].size();
		f_cycles << S << ' ';
		for (int j = 0; j < S; j++)
			f_cycles << cycles[i][j] << ' ';
		f_cycles << endl;
	}
	return sol;
}