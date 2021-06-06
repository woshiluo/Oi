// Woshiluo<woshiluo@woshiluo.site>
// 2021/04/16 22:42:19 
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
template <typename T>
T read() { 
	T sum = 0, fl = 1; 
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

const int N = 3e5 + 1e4;

void work() {
	int n = read<int>();
	int n2 = 2 * n, n3 = 3 * n;
	char s[4][N];
	bool black[4];

	memset( black, 0, sizeof(black) );

	scanf( "%s%s%s", s[0], s[1], s[2] );
	for( int i = 0; i < 3; i ++ ) {
		int black_cnt = 0;
		for( int j = 0; j < n2; j ++ ) {
			black_cnt += ( s[i][j] - '0' );
		}
		if( black_cnt >= n ) 
			black[i] = true;
	}

	for( int i = 0; i < 3; i ++ ) {
		for( int j = 0; j < 3; j ++ ) {
			if( i == j ) 
				continue;
			if( black[i] == black[j] ) {
				int p1 = 0, p2 = 0, cnt = 0;
				char res[N];
				char both = black[i]? '1': '0';
				while( p1 < n2 && p2 < n2 ) {
					if( p1 < n2 && s[i][p1] != both ) {
						res[cnt] = s[i][p1];
						if( p2 < n2 && s[j][p2] == s[i][p1] ) 
							p2 ++;
						cnt ++; p1 ++;
					}
					else if( p2 < n2 && s[j][p2] != both ) {
						res[cnt] = s[j][p2];
						p2 ++; cnt ++;
					}
					else {
						res[cnt] = both;
						if( p1 < n2 ) p1 ++;
						if( p2 < n2 ) p2 ++;
						cnt ++;
					}
				}
				while( p1 < n2 ) {
					res[cnt] = s[i][p1];
					p1 ++; cnt ++;
				}
				while( p2 < n2 ) {
					res[cnt] = s[j][p2];
					p2 ++; cnt ++;
				}
				if( cnt <= n3 ) {
					res[cnt] = 0;
					printf( "%s\n", res );
					return ;
				}
			}
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		work();
	}
}
