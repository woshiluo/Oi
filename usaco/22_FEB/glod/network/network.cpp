/*
 * network.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

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

const int N = 1e5 + 1e4;
const int MAXX = 1e6 + 1e4;

struct Node { 
	int id, x, y; 
	ll operator+ ( const Node &_b ) {
		int p1 = _b.x - x, p2 = _b.y - y;
		return 1LL * p1 * p1 + 1LL * p2 * p2;
	}
};
struct Edge { int from, to; ll val; };

struct Set {/*{{{*/
	int fa[N];
	void init( int n ) {
		for( int i = 0; i <= n; i ++ ) {
			fa[i] = i;
		}
	}
	Set( int n = 0 ) { init(n); }
	int& get_fa( int cur ) {
		if( fa[cur] == cur ) 
			return fa[cur];
		int &p = get_fa( fa[cur] );
		fa[cur] = p;
		return p;
	}
	inline int& operator[] ( int index ) {
		return this -> get_fa(index);
	}
} set;/*}}}*/

Node node[N];
std::vector<int> mp[MAXX];
std::vector<Edge> edge;

int main() {
#ifdef woshiluo
	freopen( "network.in", "r", stdin );
	freopen( "network.out", "w", stdout );
#endif
	int n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		int x, y;
		x = read<int>(); y = read<int>();
		mp[x].push_back(y);
	}

	n = 0;
	for( int i = 0; i < MAXX; i ++ ) {
		if( mp[i].size() == 0 )
			continue;
		std::sort( mp[i].begin(), mp[i].end() );
		mp[i].erase( std::unique( mp[i].begin(), mp[i].end() ), mp[i].end() );

		for( auto &y: mp[i] ) {
			n ++;
			node[n] = (Node){ n, i, y };
			y = n;
		}
	}

	std::sort( node + 1, node + n + 1, []( const Node &_a, const Node &_b ) { return _a.x < _b.x; } );
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= 20; j ++ ) {
			if( i + j < 1 || i + j == i || i + j > n ) 
				continue;
			edge.push_back( (Edge){ i, i + j, node[i] + node[ i + j ] } );
		}
	}
	for( int i = 0; i < MAXX; i ++ ) {
		if( mp[i].size() == 0 )
			continue;
		for( int j = 0; j <= 20; j ++ ) {
			for( auto &y1: mp[i] ) {
				for( auto &y2: mp[ i + j ] ) { 
					if( y1 == y2 ) 
						continue;
					edge.push_back( (Edge){ y1, y2, node[y1] + node[y2] } );
				}
			}
		}
	}

	std::sort( edge.begin(), edge.end(), []( const Edge &_a, const Edge &_b ) { return _a.val < _b.val; } );

	ll res = 0;
	set.init(n);
	for( auto &e: edge ) {
		if( set[ e.from ] == set[ e.to ] ) 
			continue;
		res += e.val;
		set[ e.from ] = set[ e.to ];
	}

	printf( "%lld\n", res );
}
