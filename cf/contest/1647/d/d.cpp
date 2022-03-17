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

#include <cmath>
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

const int MA = 1e7 + 1e5;

bool is_prime[MA];
std::vector<int> primes;

void init() {
	for( int i = 0; i < MA; i ++ ) {
		is_prime[i] = true;
	}
	for( int i = 2; i < MA; i ++ ) {
		if( is_prime[i] ) {
			primes.push_back(i);
		}
		for( auto &cur: primes ) {
			if( 1LL * cur * i >= MA ) 
				break;
			const int nxt = cur * i;
			is_prime[nxt] = false;
			if( i % cur == 0 ) 
				break;
		}
	}
}

bool chk_prime( const int cur ) {
	for( int i = 2; 1LL * i * i <= cur; i ++ ) {
		if( cur % i == 0 ) {
			return false;
		}
	}
	return true;
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	init();
	int T = read<int>();
	while( T -- ) {
		int x, d;
		x = read<int>(); d = read<int>();
		int tot = 0;
		while( x % d == 0 ) {
			tot ++;
			x /= d;
		}
		if( tot <= 1 ) {
			printf( "NO\n" );
			continue;
		}
		bool is_x = chk_prime(x);
		if( is_prime[d] && x == 1 ) {
			printf( "NO\n" );
			continue;
		}
		if( is_prime[d] && is_x ) {
			printf( "NO\n" );
			continue;
		}
		if( is_x && tot == 2 ) {
			printf( "NO\n" );
			continue;
		}
		if( is_x ) {
			int tmp = d, cnt = 0;
			for( auto &cur: primes ) {
				bool flag = false;
				while( tmp % cur == 0 ) {
					flag = true;
					tmp /= cur;
				}
				cnt += flag;
			}
			if( cnt == 1 && d % x == 0 ) {
				tmp = d; cnt = 0;
				for( auto &cur: primes ) {
					while( tmp % cur == 0 ) {
						tmp /= cur;
						cnt ++;
					}
				}
				int t_p = cnt + ( x != 1 );
				if( t_p / ( cnt - 1 ) + ( t_p % ( cnt - 1 ) != 0 ) > ( tot - 1 ) ) {
					printf( "NO\n" );
					continue;
				}
			}
		}

		printf( "YES\n" );
	}
}
