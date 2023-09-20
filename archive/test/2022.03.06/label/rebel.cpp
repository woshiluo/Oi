/*
 * rebel.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <map>
#include <queue>
#include <vector>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }
template <typename T>
T read() { 
	T sum = 0, fl = 1; 
	char ch = getchar();
	for (; isdigit(ch) == 0; ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}
template <class T> 
T pow( T a, int p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const double eps = 1e-4;
const int N = 1100;

struct Node { int x, y, z, vx, vy, vz; };

std::vector<Node> nodes;

bool check( const double p, const int s ) {
	static std::vector<double> allow[N][N], nums;

	nums.clear();
	const int n = nodes.size();
	for( int i = 0; i < n; i ++ ) {
		for( int j = i + 1; j < n; j ++ ) {
			allow[i][j].clear();
			const double a = pow( nodes[i].vx - nodes[j].vx, 2 ) +
				pow( nodes[i].vy - nodes[j].vy, 2 ) +
				pow( nodes[i].vz - nodes[j].vz, 2 );
			const double b = 2 * ( 
					( nodes[i].x - nodes[j].x ) * ( nodes[i].vx - nodes[j].vx ) +
					( nodes[i].y - nodes[j].y ) * ( nodes[i].vy - nodes[j].vy ) +
					( nodes[i].z - nodes[j].z ) * ( nodes[i].vz - nodes[j].vz ) );
			const double c = - ( p * p - pow( nodes[i].x - nodes[j].x, 2 ) -
				pow( nodes[i].y - nodes[j].y, 2 ) -
				pow( nodes[i].z - nodes[j].z, 2 ) );
			const double delta = b * b - 4.0 * a * c;
			if( delta < 0 ) 
				continue;
			if( a == 0 ) {
				if( b == 0 ) {
					if( std::sqrt( 
							pow( nodes[i].x - nodes[j].x, 2 ) +
							pow( nodes[i].y - nodes[j].y, 2 ) +
							pow( nodes[i].z - nodes[j].z, 2 ) ) <= p ) {
						allow[i][j].push_back(0);
						allow[i][j].push_back(1e9);
					}
					else
						continue;
				}
				else {
					allow[i][j].push_back(c/b);
					allow[i][j].push_back(c/b + eps);
				}
			}
			else {
				allow[i][j].push_back( ( -b - std::sqrt(delta) ) / ( 2.0 * a ) );
				allow[i][j].push_back( ( -b + std::sqrt(delta) ) / ( 2.0 * a ) + eps );
			}
			std::sort( allow[i][j].begin(), allow[i][j].end() );
			if( allow[i][j].back() < 0 ) {
				allow[i][j].clear();
				continue;
			}
			chk_Max( allow[i][j][0], 0. );
			nums.push_back(allow[i][j][0]);
			nums.push_back(allow[i][j][1]);
		}
	}

	std::sort( nums.begin(), nums.end() );
	nums.erase( std::unique( nums.begin(), nums.end() ), nums.end() );
	const int tot = nums.size();
	auto find = [&]( const double cur ) { return std::lower_bound( nums.begin(), nums.end(), cur ) - nums.begin(); };

	struct Edge { int from, to; };
	static std::vector<Edge> op[ N * N ][2];
	for( int i = 0; i < tot; i ++ ) 
		op[i][0].clear(), op[i][1].clear();
	for( int i = 0; i < n; i ++ ) {
		for( int j = i + 1; j < n; j ++ ) {
			if( allow[i][j].size() == 0 )
				continue;
			allow[i][j][0] = find( allow[i][j][0] );
			allow[i][j][1] = find( allow[i][j][1] );
			op[ (int)allow[i][j][0] ][0].push_back( (Edge){ i, j } );
			op[ (int)allow[i][j][1] ][1].push_back( (Edge){ i, j } );
		}
	}

	if( nums.size() == 0 ) {
		return false;
	}

	const double end = nums.back() + 10.;
	std::vector<double> vis; vis.resize(n, -1.); vis[0] = s;
	static std::vector<bool> mp[N];
	for( int i = 0; i < n; i ++ ) {
		mp[i].clear();
		mp[i].resize( n, false );
	}
	std::vector<int> degree; degree.resize(n, 0);
	auto bfs = [&] ( const int st ) {
		std::queue<int> q;
		q.push(st);
		while( !q.empty() ) {
			int cur = q.front(); q.pop();
			for( int i = 0; i < n; i ++ ) {
				if( mp[cur][i] && vis[i] != end ) {
					vis[i] = end;
					q.push(i);
				}
			}
		}
	};
	for( int i = 0; i < tot; i ++ ) {
		for( auto &edge: op[i][1] ) {
			mp[edge.from][edge.to] = false;
			mp[edge.to][edge.from] = false;
			degree[edge.from] --;
			degree[edge.to] --;
			if( degree[edge.from] == 0 && vis[edge.from] == end )
				vis[edge.from] = nums[i] + s;
			if( degree[edge.to] == 0 && vis[edge.to] == end )
				vis[edge.to] = nums[i] + s;
		}
		for( auto &edge: op[i][0] ) {
			mp[edge.from][edge.to] = true;
			mp[edge.to][edge.from] = true;
			degree[edge.from] ++;
			degree[edge.to] ++;
			if( vis[edge.from] >= nums[i] && vis[edge.to] >= nums[i] ) {
				vis[edge.from] = vis[edge.to] = end;
			}
			else if( vis[edge.from] >= nums[i] ) {
				vis[edge.from] = vis[edge.to] = end;
				bfs(edge.to);
			}
			else if( vis[edge.to] >= nums[i] ) {
				vis[edge.from] = vis[edge.to] = end;
				bfs(edge.from);
			}
		}
		if( vis[1] >= nums[i] ) 
			return true;
	}

	return false;
}

int main() {
	freopen( "rebel.in", "r", stdin );
	freopen( "rebel.out", "w", stdout );

	int n, S;
	n = read<int>(); S = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		int x, y, z, vx, vy, vz;
		x = read<int>(); y = read<int>(); z = read<int>();
		vx = read<int>(); vy = read<int>(); vz = read<int>();
		nodes.push_back( (Node) { x, y, z, vx, vy, vz } );
	}
	double left = 0, rig = 2000, res = 2000;
	while( left + eps <= rig ) {
		double mid =  ( left + rig ) / 2.0;
		if( check(mid, S) ) {
			res = mid;
			rig = mid - eps;
		}
		else
			left = mid + eps;
	}
	printf( "%.6lf", res );
}
