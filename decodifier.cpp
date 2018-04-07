#include <iostream>
using namespace std;

int main() {

	string s;
	cin >> s;

	int N = 14, M = 14, R = 15;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++) {
			for (int r = 0; r < R; r++){
				int x;
				cin >> x;
				if (x > 0){
					if (r < 10)
						cout << 0;
					cout << r << ' ';
				}
			}
		}
		cout << endl;
	}
	cout << endl;
}