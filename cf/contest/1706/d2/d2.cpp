/*
 * d1.cpp
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

const int N = 1e5 + 5;

int a[N];
int  val[N], pos[N];

struct Node {
	int val, pos;
	bool operator< ( const Node &_b ) const { return val > _b.val; }
};

int main() {
#ifdef woshiluo
	freopen( "d2.in", "r", stdin );
	freopen( "d2.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint k = read<int>();

		for( int i = 1; i <= n; i ++ ) 
			a[i] = read<int>();
		bool all_1 = true;
		for( int i = 1; i <= n; i ++ ) 
			if( a[i] > k ) 
				all_1 = false;

		if( all_1 ) {
			printf( "0\n" );
			continue;
		}

		std::vector<int> wait[N];
		std::deque<int> q;

		int res = N;
		int min = N;
		for( int j = 1; j <= n; j ++ ) {
			for( int l = 1, r = 0; r + 1 <= a[j]; l = r + 1 ) {
				r = a[j] / ( a[j] / l );
				pos[j] = l;
				val[j] = a[j] / l;
				wait[ val[j] ].push_back(j);

				chk_Min( min, val[j] );

				break;
			}
		}

		bool flag = true;
		for( int i = N - 1; i >= 1; i -- ) {
			chk_Min( res, i - min );

			for( auto &x: wait[i] ) {
				cint oldr = a[x] / ( a[x] / pos[x] );
				for( int l = oldr + 1, r = oldr; r + 1 <= a[x]; l = r + 1 ) {
					if( l > k ) {
						flag = false;
						break;
					}
					r = a[x] / ( a[x] / l );
					pos[x] = l;
					val[x] = a[x] / l;
					wait[ val[x] ].push_back(x);

					chk_Min( min, val[x] );

					break;
				}
			}
			wait[i].clear(); wait[i].shrink_to_fit();
			if( !flag ) 
				break;
		}

		printf( "%d\n", res );
	}
}
