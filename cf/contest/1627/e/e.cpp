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

const int N = 1e5 + 1e4;
const ll LLF = 1LL << 60LL;

struct Ladder {
	int x1, x2, y1, y2; ll h;
};

template <class T>
T aabs( T a ) { return a < 0? -a: a; }

void work() {
	int n, m, k;
	static int x[N];
	static std::vector<Ladder> la[N];
	static std::vector<int> pos[N];
	static std::vector<ll> val[N];
	static std::vector<bool> vis[N];

	n = read<int>(); m = read<int>(); k = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		x[i] = read<int>();

		la[i].clear(); pos[i].clear(); val[i].clear(); vis[i].clear();
	}
	for( int i = 1; i <= k; i ++ ) {
		Ladder ladder;
		ladder.x1 = read<int>(); ladder.y1 = read<int>();
		ladder.x2 = read<int>(); ladder.y2 = read<int>();
		ladder.h = read<ll>();
		la[ ladder.x1 ].push_back( ladder );
		la[ ladder.x2 ].push_back( ladder );
		pos[ ladder.x1 ].push_back(ladder.y1);
		pos[ ladder.x2 ].push_back(ladder.y2);
	}

	pos[1].push_back(1);
	pos[n].push_back(m);
	for( int i = 1; i <= n; i ++ ) {
		std::sort( pos[i].begin(), pos[i].end() );
		pos[i].erase( std::unique( pos[i].begin(), pos[i].end() ), pos[i].end() );
		val[i].resize( pos[i].size(), LLF );
		vis[i].resize( pos[i].size(), false );
	}
	val[1][0] = 0;
	vis[1][0] = true;

	auto get = []( const int &p1, const int &y ) {
		return std::lower_bound( pos[p1].begin(), pos[p1].end(), y ) - pos[p1].begin();
	};
	for( int i = 1; i <= n; i ++ ) {
		int size = pos[i].size();
		const int leftest = 0, rightest = m + 1;
		{
			bool has_min = false;
			ll min = LLF;
			for( int j = 0; j < size; j ++ ) {
				if( has_min ) {
					vis[i][j] = true;
					chk_Min( val[i][j], min + 1LL * aabs( pos[i][j] - leftest ) * x[i] );
				}
				if( vis[i][j] ) {
					has_min = true;
					chk_Min( min, val[i][j] - 1LL * aabs( pos[i][j] - leftest ) * x[i] );
				}
			}
		}
		{
			bool has_min = false;
			ll min = LLF;
			for( int j = size - 1; j >= 0; j -- ) {
				if( has_min ) {
					vis[i][j] = true;
					chk_Min( val[i][j], min + 1LL * aabs( pos[i][j] - rightest ) * x[i] );
				}
				if( vis[i][j] ) {
					has_min = true;
					chk_Min( min, val[i][j] - 1LL * aabs( pos[i][j] - rightest ) * x[i] );
				}
			}
		}
		for( auto ladder: la[i] ) {
			if( ladder.x1 != i ) 
				continue;
			int p1 = get( ladder.x1, ladder.y1 );
			int p2 = get( ladder.x2, ladder.y2 );
			if( vis[ ladder.x1 ][p1] ) {
				vis[ ladder.x2 ][p2] = true;
				chk_Min( val[ ladder.x2 ][p2], val[ ladder.x1 ][p1] - ladder.h );
			}
		}
	}
	if( !vis[n].back() ) 
		printf( "NO ESCAPE\n" );
	else
		printf( "%lld\n", val[n].back() );
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int T = read<int>(); 
	while( T -- ) {
		work();
	}
}
