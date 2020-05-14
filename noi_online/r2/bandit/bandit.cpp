// Woshiluo<woshiluo@woshiluo.site>
// 2020/04/25 15:01
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <queue>
#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

const int N = 410;

int n, m, c1, c2, d, end_x, end_y;
int mp[N][N];
// 0 free
// 1 watching
// 2 disabled
// 3 end

// BFS Start
struct node{ 
	int x, y, m1, time, c1, c2; 
	node( int _x = 0, int _y = 0 ) {
		x = _x, y = _y;
		m1 = time = c1 = c2 = 0;
	}
};
std::queue<node> q1, q2, q3, q4;
int dx[8] = { +1, +1, +1, 0, 0, -1, -1, -1 };
int dy[8] = { +1, 0, -1, +1, -1, +1, 0, -1 };

struct _dis{ int time, c1, c2; };
_dis dis[N][N];

void without_magic( node top ) {
	for( int i = 0; i < 8; i ++ ) {
		node tmp = top;
		tmp.x += dx[i]; tmp.y += dy[i];
		tmp.time ++; tmp.m1 = 0;

		if( tmp.x <= 0 || tmp.y <= 0 || tmp.x > n || tmp.y > m )
			continue;
		if( mp[tmp.x][tmp.y] != 0 )
			continue;
		if( tmp.x == end_x && tmp.y == end_y ) {
			printf( "%d %d %d\n", tmp.time, tmp.c1, tmp.c2 );
			exit(0);
		}
		if( dis[tmp.x][tmp.y].time != 0 || mp[tmp.x][tmp.y] != 0 ) 
			continue;

		q1.push(tmp);
		dis[tmp.x][tmp.y] = (_dis){ tmp.time, tmp.c1, tmp.c2 };
	}
}

void magic_jump( node top ) {
	int tdx[4] = { +1, -1, 0, 0 };
	int tdy[4] = { 0, 0, +1, -1 };
	for( int i = 0; i < 4; i ++ ) {
		node tmp = top;
		tmp.x += tdx[i] * d; tmp.y += tdy[i] * d;
		tmp.time ++; tmp.m1 = 0; tmp.c2 ++;

		if( tmp.c2 > c2 || tmp.x <= 0 || tmp.y <= 0 || tmp.x > n || tmp.y > m )
			continue;
		if( mp[tmp.x][tmp.y] != 0 )
			continue;
		if( tmp.x == end_x && tmp.y == end_y ) {
			printf( "%d %d %d\n", tmp.time, tmp.c1, tmp.c2 );
			exit(0);
		}
		if( dis[tmp.x][tmp.y].time != 0 || mp[tmp.x][tmp.y] != 0 ) 
			continue;

		q2.push(tmp);
		dis[tmp.x][tmp.y] = (_dis){ tmp.time, tmp.c1, tmp.c2 };
	}
}

void magic_hide( node top ) {
	for( int i = 0; i < 8; i ++ ) {
		node tmp = top;
		tmp.x += dx[i]; tmp.y += dy[i];
		tmp.time ++; tmp.m1 = 1; tmp.c1 ++;

		if( tmp.c1 > c1 || tmp.x <= 0 || tmp.y <= 0 || tmp.x > n || tmp.y > m )
			continue;
		if( tmp.x == end_x && tmp.y == end_y ) {
			printf( "%d %d %d\n", tmp.time, tmp.c1, tmp.c2 );
			exit(0);
		}
		if( dis[tmp.x][tmp.y].time != 0 || mp[tmp.x][tmp.y] != 1 ) 
			continue;

		q3.push(tmp);
		dis[tmp.x][tmp.y] = (_dis){ tmp.time, tmp.c1, tmp.c2 };
	}
}

void magic_both( node top ) {
	int tdx[4] = { +1, -1, 0, 0 };
	int tdy[4] = { 0, 0, +1, -1 };
	for( int i = 0; i < 4; i ++ ) {
		node tmp = top;
		tmp.x += tdx[i] * d; tmp.y += tdy[i] * d;
		tmp.time ++; tmp.m1 = 1; tmp.c1 ++; tmp.c2 ++;

		if( tmp.c1 > c1 || tmp.c2 > c2 || tmp.x <= 0 || tmp.y <= 0 || tmp.x > n || tmp.y > m )
			continue;
		if( tmp.x == end_x && tmp.y == end_y ) {
			printf( "%d %d %d\n", tmp.time, tmp.c1, tmp.c2 );
			exit(0);
		}
		if( dis[tmp.x][tmp.y].time != 0 || mp[tmp.x][tmp.y] != 1 ) 
			continue;

		q4.push(tmp);
		dis[tmp.x][tmp.y] = (_dis){ tmp.time, tmp.c1, tmp.c2 };
	}
}

void bfs( int st_x, int st_y ) {
	q1.push( node( st_x, st_y ) );
	int cur_time = 0;
	while( !q1.empty() || !q2.empty() || !q3.empty() || !q4.empty() ) {
		node top;
		bool flag = false;
		if( !q1.empty() && q1.front().time == cur_time ) {
			top = q1.front();
			q1.pop();
			flag = true;
		}
		else if( !q2.empty() && q2.front().time == cur_time ) {
			top = q2.front();
			q2.pop();
			flag = true;
		}
		else if( !q3.empty() && q3.front().time == cur_time ) {
			top = q3.front();
			q3.pop();
			flag = true;
		}
		else if( !q4.empty() && q4.front().time == cur_time ) {
			top = q4.front();
			q4.pop();
			flag = true;
		}

		if( flag == false ) {
			cur_time ++;
			continue;
		}

		without_magic( top );
		magic_jump(top);
		if( top.m1 == 0 ) {
			magic_hide(top);
			magic_both(top);
		}
	}
}
// BFS End

// Gen Map
int to_int( char str[] ) {
	int res = 0;
	int len = strlen( str );
	for( int i = 0; i < len; i ++ ) {
		res = res * 10 + ( str[i] - '0' );
	}
	return res;
}
namespace Gen_map{ 
	int dx[4] = { +1, -1, 0, 0 };
	int dy[4] = { 0, 0, +1, -1 };
	int dep[N][N];
	bool vis[N][N];
	struct node { 
		int x, y, dep; 
		node( int _x, int _y, int _dep ) { x = _x, y = _y; dep = _dep; }
	};
	void set_dep( int x, int y, int _dep ) {
		dep[x][y] = _dep;
	}
	void gen_map() {
		std::queue<node> q;
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= n; j ++ ) {
				if( mp[i][j] == 2 ) 
					q.push( node( i, j, dep[i][j] ) );
			}
		}
		while( !q.empty() ) {
			node top = q.front();
			for( int i = 0; i < 4; i ++ ) {
				node tmp = top;
				tmp.x += dx[i];
				tmp.y += dy[i];
				tmp.dep --;

				if( tmp.dep <= 0 || tmp.x <= 0 || tmp.y <= 0 || tmp.x > n || tmp.y > m || mp[tmp.x][tmp.y] != 0 || vis[tmp.x][tmp.y] ) 
					continue;

				mp[tmp.x][tmp.y] = 1;
				vis[ tmp.x ][ tmp.y ] = true;
				q.push( tmp );
			}
			q.pop();
		}
	}
}

int main() {
	freopen( "bandit.in", "r", stdin );
	freopen( "bandit.out", "w", stdout );
	scanf( "%d%d%d%d%d", &n, &m, &c1, &c2, &d );
	char tmp_str[N];
	int s_x = 0, s_y = 0;
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= m; j ++ ) {
			scanf( "%s", tmp_str );
			if( tmp_str[0] == '.' )
				continue;
			else if( tmp_str[0] == 'S' ) {
				mp[i][j] = 4;
				s_x = i, s_y= j;
				dis[i][j].time = 1;
				continue;
			}
			else if( tmp_str[0] == 'T' ) {
				end_x = i, end_y = j;
				continue;
			}
			else {
				mp[i][j] = 2;
				Gen_map::set_dep( i, j, to_int( tmp_str ) );
			}
		}
	}

	Gen_map::gen_map();
	bfs( s_x, s_y );
	printf( "-1" );
	
	fclose( stdin );
	fclose( stdout );
	return 0;
}
