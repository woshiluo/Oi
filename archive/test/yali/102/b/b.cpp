/*
 * b.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
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
#include <random>
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

const int n = ( 1 << 19 );
const int N = ( 1 << 20 );

std::mt19937 rnd(3153);

int k;
ll a[4][N];

inline int full_pow( const int cur ) { return 1 << cur; } 

struct Node {
	int x, y;
};

void calc() {
	static int p[90];
	int max_bit = Min( 17, k );
	for( int i = 0; i < k; i ++ ) {
		p[i] = i;
	}
	std::shuffle( p, p + k, rnd );
	std::vector<int> b[4][N], sta_list;
	std::map<ll, Node> mp;

	for( int j = 0; j < 4; j ++ ) {
		for( int i = 0; i < n; i ++ ) {
			int cur = 0;
			for( int cur_bit = 0; cur_bit < max_bit; cur_bit ++ ) {
				cur |= ( ( ( a[j][i] >> p[cur_bit] ) & 1 ) << cur_bit );
			}
			sta_list.push_back(cur);
			b[j][cur].push_back(i);
		}
	}
	
	std::sort( sta_list.begin(), sta_list.end() );
	sta_list.erase( std::unique( sta_list.begin(), sta_list.end() ), sta_list.end() );

	for( auto sta: sta_list ) {
		for( auto i: b[0][sta] ) {
			for( auto j: b[1][sta] ) {
				ll xsum = ( a[0][i] ^ a[1][j] );
				if( mp.count( xsum ) )
					continue;
				mp[xsum] = (Node){ i, j };
			}
		}
	}
	for( auto sta: sta_list ) {
		for( auto i: b[2][sta] ) {
			for( auto j: b[3][sta] ) {
				ll xsum = ( a[2][i] ^ a[3][j] );
				if( mp.count(xsum) ) {
					Node node = mp[xsum];
					printf( "%d %d %d %d\n", node.x + 1, node.y + 1, i + 1, j + 1 );
					std::exit(0);
				}
			}
		}
	}

	return ;
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	k = read<int>(); ll v = read<ll>();
	for( int j = 0; j < 4; j ++ ) { 
		for( int i = 0; i < n; i ++ ) {
			a[j][i] = read<ll>();
		}
	}
	for( int i = 0; i < n; i ++ ) {
		a[0][i] ^= v;
	}

	while(1) calc();

	return 0;
}
