// Woshiluo<woshiluo@woshiluo.site>
// 2021/02/28 23:06:28 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }
template <typename T=int>
T read() { 
	T sum = 0, fl = 1; 
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

ll try_less( ll cnt ) {
	ll cur = 1;
	while( cur < cnt ) {
		if( ( cur << 1LL ) > cnt ) 
			return cnt - cur;
		cur <<= 1LL;
	}
	return 0;
}

int T;
int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	T = read();
	while( T -- ) {
		int u, v;
		ll cnt = 0;
		u = read(); v = read();
		if( u > v ) {
			printf( "NO\n" );
			continue;
		}
		for( int k = 30; k >= 0; k -- ) {
			int cur = 1 << k;
			cnt <<= 1LL;
			int u_cur = u / cur, v_cur = v / cur;
			u %= cur; v %= cur;
			if( u_cur == v_cur ) 
				continue;
			if( u_cur > v_cur ) 
				cnt = try_less(cnt);
			else 
				cnt ++;
		}
		printf( "%s\n", cnt == 0? "YES": "NO" );
	}
}
