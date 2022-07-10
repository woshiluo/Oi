/*
 * d.cpp
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

const int N = 2e5 + 1e4;

int cnt[N];
bool vis[N];

std::vector<std::pair<int, int>> edges;
std::vector<int> list;

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();

		int rt = -1, cnt1 = 0;
		for( int i = 1; i <= n; i ++ ) {
			int tmp;
			scanf( "%1d", &tmp );

			cnt[i] = ( tmp? 1: 2 );
			vis[i] = false;

			if( cnt[i] == 1 ) {
				rt = i;
				cnt1 ++;
			}
		}

		auto last = [&] ( cint cur ) { 
			if( cur - 1 == 0 ) 
				return n;
			return cur - 1;
		};
		auto next = [&] ( cint cur ) { 
			if( cur + 1 == n + 1 ) 
				return 1;
			return cur + 1;
		};

		// TODO: prove
		if( cnt1 & 1 || cnt1 == 0 ) {
			printf( "NO\n" );
			continue;
		}

		vis[rt] = true;
		edges.clear();

		auto add_edge = [&]( cint from, cint to ) { edges.push_back( std::make_pair( from, to ) ); };

		bool flag = false;
		for( int i = next(rt); !vis[i]; i = next(i) ) {
			vis[i] = true;
			if( cnt[i] == 2 ) {
				if( !flag ) {
					add_edge( rt, i );
					flag = true;
				}
				else
					add_edge( last(i), i );
			}
			else {
				if( flag ) {
					add_edge( last(i), i );
					flag = false;
				}
				else {
					if( cnt[ next(i) ] == 2 ) {
						list.clear();

						int j = next(i);
						for( ; cnt[j] == 2; j = next(j) ) {
							vis[j] = true;
							list.push_back(j);
						}

						add_edge( i, next(i) );
						std::reverse( list.begin(), list.end() );

						add_edge( rt, list.front() );
						cint size = list.size();
						for( int k = 0; k < size - 1; k ++ ) 
							add_edge( list[k], list[ k + 1 ] );

						i = last(j);
					}
					else 
						add_edge( rt, i );
				}
			}
		}

		if( flag ) {
			printf( "NO\n" );
		}
		else {
			printf( "YES\n" );
			for( auto &pair: edges ) {
				printf( "%d %d\n", pair.first, pair.second );
			}
		}
	}
}
