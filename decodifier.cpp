#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int L = 60;
int l = L/3;
string dir[] = {"└", "│", "┘", "┌", "─", "┐", "c", "c", "c", "c", "c"};
char color[] = {'R', 'B', 'Y', 'G', 'O', 'C', 'M', 'm', 'P', 'A', 'W', 'g', 'T', 'b', 'c', 'p' };
ofstream image;
vector < vector <int> > D, C;
int N = -1, M = -1, R = -1, K1 = 6;
string color_svg [] = {
	"red",
	"blue",
	"yellow",
	"green",
	"orange",
	"cyan",
	"magenta",
	"maroon",
	"purple",
	"gray",
	"white",
	"limegreen",
	"tan",
	"darkblue",
	"darkcyan",
	"pink"
};

string back_color [] = {

	"723939",
	"393972",
	"6e6e39",
	"395539",
	"725539",
	"397272",
	"723972",
	"5f4242",
	"553955",
	"5f5e5f",
	"727272",
	"397239",
	"646251",
	"393958",
	"395555",
	"72415a",
};

int dx[] = {-1, 0, 1,  0};
int dy[] = { 0, 1, 0, -1};

int type[][2] =
{
	{0, 1},
	{0, 2},
	{0, 3},
	{1, 2},
	{1, 3},
	{2, 3},
	{0},
	{1},
	{2},
	{3}
};


void draw_line(int x1, int y1, int x2, int y2, string color) {
	image	<< "<line"
			<< " x1=" << '"' << x1 << '"' << " y1=" << '"' << y1 << '"'
			<< " x2=" << '"' << x2 << '"' << " y2=" << '"' << y2 << '"'
			<< " stroke=" << '"' << color << '"'
			<< " stroke-width=" << '"' << l << '"'
			<< "/>" << endl;
}

void draw_circle(int cx, int cy, int r, string color) {
	image	<< "<circle"
			<< " cx=" << '"' << cx << '"' << " cy=" << '"' << cy << '"'
			<< " r=" << '"' << r << '"'
			<< " fill=" << '"' << color << '"'
			<< "/>" << endl;
}

void draw_square(int x, int y, int L, string color) {
	image	<< "<rect"
			<< " x=" << '"' << x << '"' << " y=" << '"' << y << '"'
			<< " width=" << '"' << L << '"' << " height=" << '"' << L << '"'
			<< " style=" << "\"fill: #"<< color << ";\""
			<< "/>" << endl;
}

void make_square(int i, int j) {
	int x = i*L, y = j*L;
	string cur_color = back_color[C[i][j]];
	draw_square(x, y, L, cur_color);
}

void make_line(int i, int j, int k) {
	int x0 = i*L + L/2, y0 = j*L + L/2;
	string cur_color = color_svg[C[i][j]];
	draw_line(x0, y0, x0+dx[type[k][0]]*L/2, y0+dy[type[k][0]]*L/2, cur_color);
	draw_line(x0, y0, x0+dx[type[k][1]]*L/2, y0+dy[type[k][1]]*L/2, cur_color);
	draw_circle(x0, y0, l/2, cur_color);
}

void make_circle(int i, int j, int k) {
	string cur_color = color_svg[C[i][j]];
	int cx = i*L + L/2, cy = j*L + L/2, r = L/3;
	draw_line(cx, cy, cx+dx[type[k][0]]*L/2, cy+dy[type[k][0]]*L/2, cur_color);
	draw_circle(cx, cy, r, cur_color);
}

void make_image(){
	image << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>";
	image << endl;
	image << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">";
	image << endl;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			make_square(i, j);

	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++){
			int k = D[i][j];
			if (k < K1)
				make_line(i, j, k);
			else
				make_circle(i, j, k);
		}
	}
	image << "</svg>" << endl;
}

int main(int argc, char **argv) {

	string s;
	cin >> s;
	int val;
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
	string name = argv[1];
	int len = name.size();
	name[len-3] = 's';
	name[len-2] = 'v';
	name[len-1] = 'g';
	name = "images/" + name;
	image.open(name.c_str());
	make_image();
	image.close();
}