/*
 * loj.3210.cpp
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <algorithm>

typedef const int cint;
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

const int N = 2e3 + 1e2;

struct Set {/*{{{*/
	int fa[N];

	void init( cint n ) {
		for( int i = 0; i <= n; i ++ ) {
			fa[i] = i;
		}
	}
	Set( int n = 0 ) { init(n); }

	int& get_fa( cint cur ) {
		if( this -> fa[cur] == cur ) 
			return fa[cur];
		fa[cur] = get_fa( fa[cur] );
		return get_fa( fa[cur] );

	}
	int& operator[] ( cint cur ) {
		return this -> get_fa(cur);
	}
} set;/*}}}*/

struct Edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( cint from, cint to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

int id[N], mp[N];

void swap_node( cint from, cint to ) {
	std::swap( id[from], id[to] );
	mp[ id[from] ] = from;
	mp[ id[to] ] = to;
}

int depth[N], fa[N];
bool ed[N];
int get_min( cint cur, cint la, cint limit ) {
	fa[cur] = la; depth[cur] = depth[la] + 1;
	int res = ( la == 0 || ed[cur] )? N: cur;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		cint current_edge = set[i];
		if( current_edge == 0 || set[ i ^ 1 ] == limit || set[i] == limit || e[current_edge].to == la ) 
			continue;
	
		chk_Min( res, get_min( e[current_edge].to, cur, set[ current_edge ^ 1 ] ) );
	}
	return res;
}

void init() {
	ecnt = 1;
	memset( ed, 0, sizeof(ed) );
	memset( ehead, 0, sizeof(ehead) );
}

bool get_path( cint cur, cint la, cint limit, cint gol, std::vector<int> &path ) {
	if( cur == gol ) 
		return true;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		cint current_edge = set[i];
		if( current_edge == 0 || set[ i ^ 1 ] == limit || set[i] == limit || e[current_edge].to == la ) 
			continue;
		path.push_back(current_edge);
		if( get_path( e[current_edge].to, cur, set[ current_edge ^ 1 ], gol, path ) ) 
			return true;
		path.pop_back();
	}
	return false;
}

int main() {
#ifdef woshiluo
	freopen( "loj.3210.in", "r", stdin );
	freopen( "loj.3210.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		init();
		set.init( n + n );

		for( int i = 1; i <= n; i ++ ) {
			id[i] = read<int>();
			mp[ id[i] ] = i;
		}

		for( int i = 1; i < n; i ++ ) {
			cint u = read<int>();
			cint v = read<int>();

			add_edge( u, v );
			add_edge( v, u );
		}

		for( int i = 1; i <= n; i ++ ) {
			int from = mp[i];
			int to = get_min( from, 0, 0 );

			id[to] = i;

			std::vector<int> path;
			get_path( from, 0, 0, to, path );
			{
				cint size = path.size();
				for( int j = 0; j < size - 1; j ++ ) {
					set[ path[j] ] = path[ j + 1 ];
				}
			}
			ed[to] = true;
		}

		for( int i = 1; i <= n; i ++ ) 
			printf( "%d ", id[i] );
		printf( "\n" );
	}
}
