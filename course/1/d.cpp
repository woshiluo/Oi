/*
 * d.cpp 2023-12-28
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using i32 = int32_t;
using u32 = uint32_t;
using ci32 = const int32_t;
using cu32 = const uint32_t;

using i64 = int64_t;
using u64 = uint64_t;
using ci64 = const int64_t;
using cu64 = const uint64_t;

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
T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 1100;

std::string name[N];
std::map<std::string, i32> mp;
std::map<std::string, i32> vote;

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	ci32 n = read<i32>();
	for( int i = 1; i <= n; i ++ ) {
		std::cin >> name[i];
		mp[ name[i] ] = i;
	}
	
	ci32 q = read<i32>();
	i32 cnt = 0;
	for( int i = 1; i <= q; i ++ ) { 
		std::string cur;
		std::cin >> cur;
		ci32 tmp = read<i32>();
		cnt += tmp;
		if( mp.count(cur) == 0 ) 
			mp[cur] = n + 1;
		vote[cur] = tmp;
	}

	double avg = (double)cnt / q;

	bool flag = true;
	for( auto &p: mp ) {
		if( p.second == n + 1 ) {
			if( vote[ p.first ] > avg ) {
				flag = false;
				std::cout << p.first << "\n";
			}
		}
	}
	if( flag ) {
		printf( "Bing Mei You\n" );
	}
}
