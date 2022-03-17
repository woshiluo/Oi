/*
 * k.cpp
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

const int N = 1100;

int mp[N][N], a[N][N];

int main() {
#ifdef woshiluo
	freopen( "k.in", "r", stdin );
	freopen( "k.out", "w", stdout );
#endif
	int n, m;
	scanf( "%d%d\n", &n, &m );
	for( int i = 1; i <= n; i ++ ) {
		static char str[N];
		fgets( str + 1, N - 1, stdin );
		for( int j = 1; j <= m; j ++ ) {
			if( str[j] == '.' )
				mp[i][j] = 0;
			if( str[j] == '|' ) 
				mp[i][j] = 1;
			if( str[j] == '-' ) 
				mp[i][j] = 2;
			if( str[j] == '/' ) 
				mp[i][j] = 3;
			if( str[j] == '+' ) 
				mp[i][j] = 4;
		}
	}
	

	std::vector<int> st;
	for( int i = 1; i <= m; i ++ ) {
		if( mp[n][i] == 4 ) {
			st.push_back(i);
		}
	}

	int l = st.size() - 1, w;

	{
		int cx = n, cy = 1, cnt = 0;
		while(1) {
			if( mp[ cx - 1 ][cy] == 1 ) {
				cx -= 3;
				continue;
			}
			if( mp[ cx - 1 ][ cy + 1 ] == 3 ) {
				cx -= 2;
				cy += 2;
				cnt ++;
				continue;
			}
			break;
		}
		w = cnt;
	}


	for( int i = 1; i <= l; i ++ ) {
		int j = w;
		int cx = n, cy = st[i], cnt = 0;
		while(1) {
			if( mp[ cx - 1 ][cy] == 1 ) {
				cx -= 3;
				cnt ++;
				continue;
			}
			if( mp[ cx - 1 ][ cy + 1 ] == 3 ) {
				a[i][j] = cnt;
				j --;
				cx -= 2;
				cy += 2;
				continue;
			}
			a[i][j] = cnt;
			break;
		}
	}

	int res = 0;
	for( int i = 1; i <= l; i ++ ) {
		for( int j = 1; j <= w; j ++ ) {
			res += a[i][j];
		}
	}
	printf( "%d\n", res );
	
}
