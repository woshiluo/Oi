/*
 * b.cpp 2023-09-30
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
#include <cstdint>
#include <cstring>

#include <map>
#include <queue>
#include <vector>
#include <random>
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

// std::random_device seed;
// std::mt19937_64 rnd( seed() );
std::map<int64_t, int> ans;

constexpr int64_t chk_pos( const int64_t cur, const int64_t pos ) { return ( cur >> pos ) & 1; }

void bfs( cint a, cint b, cint m ) {
	std::queue< std::pair<int64_t, int64_t> > q;
	std::map< std::pair<int64_t, int64_t>, int > mp;
	q.push( { a, b } );
	mp[ { a, b } ] = 0;
	while( !q.empty() ) {
		const auto [ x, y ] = q.front(); q.pop();
		cint lst = mp[ { x, y } ];
		{
			std::pair<int64_t, int64_t> nxt = { x & y, y };
			if( !mp.count(nxt) ) {
				mp[nxt] = lst + 1;
				q.push(nxt);
			}
		}
		{
			std::pair<int64_t, int64_t> nxt = { x | y, y };
			if( !mp.count(nxt) ) {
				mp[nxt] = lst + 1;
				q.push(nxt);
			}
		}
		{
			std::pair<int64_t, int64_t> nxt = { x, x ^ y };
			if( !mp.count(nxt) ) {
				mp[nxt] = lst + 1;
				q.push(nxt);
			}
		}
		{
			std::pair<int64_t, int64_t> nxt = { x, y ^ m };
			if( !mp.count(nxt) ) {
				mp[nxt] = lst + 1;
				q.push(nxt);
			}
		}
	}
	for( auto &pair: mp ) {
		const auto [ res, step ] = pair;
		const auto [ c, d ] = res;
		int64_t r = 0;
		for( int i = 0; i <= 30; i ++ ) {
			int64_t s = ( chk_pos(a, i) | ( chk_pos(b, i) << 1 ) | ( chk_pos(m, i) << 2 ) );
			if( chk_pos( c, i ) ) 
				r |= ( 1ll << s );
			else
				r |= ( 1ll << ( s + 8 ) );
			if( chk_pos( d, i ) ) 
				r |= ( 1ll << ( s + 16 ) );
			else
				r |= ( 1ll << ( s + 24 ) );
		}
		ans[r] = step;
	}
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	for( int bit = 1; bit <= 10; bit ++ ) {
		for( int k = 0; k < 1024; k ++ ) { 
			int64_t mod = ( 1 << bit );
			bfs( rand() % mod, rand() % mod, rand() % mod );
		}
	}
	int T = read<int>();
	while( T -- ) {
		cint a = read<int>();
		cint b = read<int>();
		cint c = read<int>();
		cint d = read<int>();
		cint m = read<int>();
		int64_t r = 0;
		for( int i = 0; i <= 30; i ++ ) {
			int64_t s = ( chk_pos(a, i) | ( chk_pos(b, i) << 1 ) | ( chk_pos(m, i) << 2 ) );
			if( chk_pos( c, i ) ) 
				r |= ( 1ll << s );
			else
				r |= ( 1ll << ( s + 8 ) );
			if( chk_pos( d, i ) ) 
				r |= ( 1ll << ( s + 16 ) );
			else
				r |= ( 1ll << ( s + 24 ) );
		}
		if( ans.count(r) ) 
			printf( "%d\n", ans[r] );
		else
			printf( "-1\n" );
	}
}
