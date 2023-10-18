/*
 * c.cpp 2023-10-08
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

#include <queue>
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

int aabs( cint cur ) { return cur < 0? -cur: cur; }

const int N = 4e5 + 1e4;

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

int n;
int vis[N];

void no_sol() {
	printf( "-1\n" );
	std::exit(0);
}

int in[N];
bool deleted[N], selected[N];

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	n = read<int>();
	std::vector<int> a( n + 1 );
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
	}
	for( int i = 1; i <= n; i ++ ) {
		add_edge( i, a[i] );
		in[ a[i] ] ++;
	}

	{
		std::queue<int> q;
		for( int i = 1; i <= n; i ++ )
			if( in[i] == 0 ) {
				selected[i] = true;
				deleted[i] = true;
				q.push(i);
			}

		while( !q.empty() ) {
			cint cur = q.front(); q.pop();
			for( int i = ehead[cur]; i; i = e[i].next ) {
				cint to = e[i].to;
				if( deleted[to] )
					continue;
				in[to] --;
				if( selected[cur] ) {
					deleted[to] = true;
					selected[to] = false;
					q.push(to);
					continue;
				} 
				if( in[to] == 0 ) {
					selected[to] = true;
					deleted[to] = true;
					q.push(to);
				}
			}
		}
	}

	for( int p = 1; p <= n; p ++ ) {
		if( deleted[p] ) 
			continue;
		deleted[p] = true;
		std::queue<int> q;
		q.push(p);
		std::vector<int> list;
		while( !q.empty() ) {
			cint cur = q.front(); q.pop();
			list.push_back(cur);
			for( int i = ehead[cur]; i; i = e[i].next ) {
				cint to = e[i].to;
				if( deleted[to] ) 
					continue;
				deleted[to] = true;
				q.push(to);
			}
		}
		cint size = list.size();
		if( size & 1 ) 
			no_sol();
		for( int i = 0; i < size; i += 2 ) 
			selected[ list[i] ] = true;
	}

	std::vector<int> nums;
	for( int i = 1; i <= n; i ++ )
		if( selected[i] ) 
			nums.push_back(i);
	printf( "%lu\n", nums.size() );
	for( auto &x: nums ) 
		printf( "%d ", a[x] );
}
