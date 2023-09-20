/*
 * loj.3535.cpp
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

#include <bitset>
#include <random>
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

typedef std::bitset<256> string;

const int N = 410000;
const int M = 256;
const int P = 16;

int mp[256];

string s[N];


namespace gen {/*{{{*/
	typedef unsigned long long ull;

	ull myRand(ull &k1, ull &k2) {
		ull k3 = k1, k4 = k2;
		k1 = k4;
		k3 ^= (k3 << 23);
		k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
		return k2 + k4;
	}

	void gen(int n, ull a1, ull a2) {
		for (int i = 1; i <= n; i++)
			for (int j = 0; j < 256; j++)
				s[i][ mp[j] ] = (myRand(a1, a2) & (1ull << 32)) ? 1 : 0;
	}
}/*}}}*/

inline bool chk_pos( cint cur, cint p ) { return ( cur >> p ) & 1; }

namespace online {/*{{{*/
	const int K = 70;

	int lastans = 0;

	string input() {
		static char str[K];
		scanf( "%s", str );

		string res;
		for( int i = 0; i < 64; i ++ ) {
			cint cur = ( str[i] <= '9' )? ( str[i] - '0' ): ( str[i] - 'A' + 10 );
			cint base = i * 4;
			for( int j = 0; j < 4; j ++ ) {
				res[ mp[ base + j ] ] = chk_pos( cur, 4 - j - 1 ) ^ lastans;
			}
		}

		return res;
	}
	void output( cint k ) {
		lastans = k;
		putchar( k + '0' );
		putchar( '\n' );
	}
}/*}}}*/

std::vector<int> list[P][ 1 << P ];

int main() {
#ifdef woshiluo
	freopen( "loj.3535.in", "r", stdin );
	freopen( "loj.3535.out", "w", stdout );
#else
	freopen( "qi.in", "r", stdin );
	freopen( "qi.out", "w", stdout );
#endif

	for( int i = 0; i < 256; i ++ ) 
		mp[i] = i;
	
	std::mt19937 rnd(998244353);
	std::shuffle( mp, mp + 256, rnd );

	cint n = read<int>();
	cint m = read<int>();
	{/*{{{*/
		const ull a1 = read<ull>();
		const ull a2 = read<ull>();
		gen::gen( n, a1, a2 );
	}/*}}}*/

	for( int i = 1; i <= n; i ++ ) {
		string cur = s[i];
		for( int j = 0; j < P; j ++ ) {
			cint p = ( ( cur << ( j * P ) ) >> ( M - P ) ).to_ulong();
			list[j][p].push_back(i);
		}
	}

	for( int i = 1; i <= m; i ++ ) {
		string cur = online::input();
		cint k = read<int>();
		bool flag = false;
		for( int j = 0; j < P; j ++ ) {
			cint p = ( ( cur << ( j * P ) ) >> ( M - P ) ).to_ulong();
			for( auto &x: list[j][p] ) {
				if( (int)( ( cur ^ s[x] ).count() ) <= k ) {
					flag = true;
					break;
				}
			}
			if( flag ) 
				break;
		}

		online::output(flag);
	}
}
