/*
 * c.cpp
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


int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		int n = read<int>();
		std::vector<int> son( n + 10 );
		for( int i = 2; i <= n; i ++ ) 
			son[ read<int>() ] ++;
		std::sort( son.begin(), son.end(), []( const int &_a, const int &_b ) { return _a > _b; } );
		while( son.back() == 0 ) {
			son.pop_back();
		}
		son.push_back(1);
		const int size = son.size();
		int res = size;
		for( int i = 0; i < size; i ++ ) {
			son[i] -= ( size - i );
			chk_Max( son[i], 0 );
		}

		std::priority_queue<int> q;
		for( auto &x: son ) {
			if( x > 0 ) 
				q.push(x);
		}

		int base = 0;
		while( !q.empty() ) {
			if( !q.empty() && q.top() <= base ) {
				q.pop();
				continue;
			}

			res ++; base ++;
			int cur = q.top(); q.pop();
			if( cur - 1 <= base ) 
				continue;
			q.push( cur - 1 );
		}
		printf( "%d\n", res );
	}
}
