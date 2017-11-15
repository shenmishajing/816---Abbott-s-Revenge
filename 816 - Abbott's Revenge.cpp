#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;

struct pos
{
	int x, y, dir;
	pos(int x = 0, int y = 0, int dir = 0) :x(x), y(y), dir(dir) {};
};

bool searched[10][10][4];
pos parent[10][10][4];
stack<int> route[2];
queue<int> position[3];
vector<int> picture[10][10][4];
const int dirction[4][2] = { { -1,0 },{ 0,1 },{ 1,0 },{ 0,-1 } };

void clear();
int cscanf(char&c);
int dircte(char c);
void print(int x, int y, int dir);
bool move();
bool inside(int x, int y);
int sx, sy, gx, gy;
int main()
{
	char c;
	string name;
	int dir, n, m, d;
	cin >> name;
	while (name !="END")
	{
		{
			clear();
			cin >> sx >> sy;
			cscanf(c);
			cin >> gx >> gy;
			dir = dircte(c);
			parent[sx + dirction[dir][0]][sy + dirction[dir][1]][dir] = pos(sx, sy, dir);
			position[0].push(sx + dirction[dir][0]);
			position[1].push(sy + dirction[dir][1]);
			position[2].push(dir);
			cin >> n; }
		while (n != 0)
		{
			cin >> m;
			cscanf(c);
			while (isalpha(c))
			{
				d = dircte(c);
				while (cscanf(c) == 0)
					picture[n][m][d].push_back(dircte(c));
			}
			cin >> n;
		}

		cout << name << endl;
		if (!move())
			cout << "No Solution Possible" << endl;

		cin >> name;
	}
	return 0;
}

void clear()
{
	int i, j, k;
	for ( i = 0; i < 9; i++)
		for ( j = 0; j < 9; j++)
			for (k = 0; k < 4; k++)
			{
				picture[i][j][k].clear();
				parent[i][j][k] = pos();
				searched[i][j][k] = 0;
			}
	while (!route[0].empty())
	{
		route[0].pop();
		route[1].pop();
	}
	while (!position[0].empty())
	{
		position[0].pop();
		position[1].pop();
		position[2].pop();
	}
}

int cscanf(char & c)
{
	int sum = 0;
	c = getchar();
	while (!isalpha(c))
	{
		sum++;
		cin >> c;
		if (c == '*')
			return -1;
	}
	return sum;
}

int dircte(char c)
{
	switch (c)
	{
	case 'L':return -1;
	case 'N':
	case 'F':
		return 0;
	case 'E':
	case 'R':
		return 1;
	case 'S':return 2;
	case 'W':return 3;
	default:
		break;
	}
	return -2;
}

void print(int x,int y,int dir)
{
	int n = 0;
	pos p;
	route[0].push(x);
	route[1].push(y);
	while (x != sx || y != sy)
	{
		p = parent[x][y][dir];
		x = p.x;
		y = p.y;
		dir = p.dir;
		route[0].push(x);
		route[1].push(y);
	}
	cout << "  ";
	while (!route[0].empty())
	{
		if (n == 10)
		{
			cout << endl << "  ";
			n = 0;
		}
		cout << "(" << route[0].top() << "," << route[1].top() << ") ";
		route[0].pop();
		route[1].pop();
		n++;
	}
	cout << endl;
}

bool move()
{
	int x, y, dir, i;
	while (!position[0].empty())
	{
		x = position[0].front();
		y = position[1].front();
		dir = position[2].front();
		position[0].pop();
		position[1].pop();
		position[2].pop();
		for ( i = 0; i < picture[x][y][dir].size(); i++)
		{
			int  d = dir + picture[x][y][dir][i];
			if (d < 0) d += 4;
			if (d > 3) d -= 4;
			int a = x + dirction[d][0], b = y + dirction[d][1];
			if (inside(a,b)&&!searched[a][b][d])
			{
				parent[a][b][d] = pos(x, y, dir);
				if (a == gx&&b == gy)
				{
					print(a, b, d);
					return true;
				}
				searched[a][b][d] = 1;
				position[0].push(a);
				position[1].push(b);
				position[2].push(d);
			}
		}
	}
	return false;
}

inline bool inside(int x, int y)
{
	return (x <= 9 && x >= 1 && y <= 9 && y >= 1);
}
