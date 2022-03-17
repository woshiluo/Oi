/*
 * e.cpp
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

#include <map>
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

const int N = 2e5 + 1e4;

struct Edge {
	int to, next;
} e[ N << 1 ];
int ehead[ N << 1 ], ecnt = 1;
void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int t;
std::map<int, int> cnt[N][2];
std::map<int, int> mp;
std::vector<int> a[N];
int pool[N];
bool used[ N << 1 ];

void dfs( int cur ) {
	for( int &i = ehead[cur]; i; i = e[i].next ) {
		if( used[i] ) 
			continue;
		used[i] = used[ i ^ 1 ] = true;
		int to = e[i].to;
		if( cur <= t ) 
			cnt[cur][0][to - t] ++;
		else
			cnt[to][1][cur - t] ++;
		dfs(to);
	}
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	t = read<int>(); int tot = 0;
	for( int i = 1; i <= t; i ++ ) {
		int n = read<int>();
		for( int j = 1; j <= n; j ++ ) {
			int tmp = read<int>();

			if( !mp.count(tmp) ) {
				tot ++;
				mp[tmp] = tot;
			}

			tmp = mp[tmp];
			a[i].push_back(tmp);
			pool[tmp] ++;
			add_edge( i, tmp + t );
			add_edge( tmp + t, i );
		}
	}
	for( int i = 0; i <= tot; i ++ ) {
		if( pool[i] & 1 ) {
			printf( "NO\n" );
			return 0;
		}
	}

	printf( "YES\n" );
	for( int i = 1; i <= t; i ++ )
		dfs(i);
	for( int i = 1; i <= t; i ++ ) {
		for( auto &val: a[i] ) {
			if( cnt[i][0][val] > 0 ) {
				printf( "L" );
				cnt[i][0][val] --;
			}
			else {
				printf( "R" );
				cnt[i][1][val] --;
			}
		}
		printf( "\n" );
	}
}
