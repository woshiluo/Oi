// Woshiluo<woshiluo@woshiluo.site>
// 2021/02/08 00:45:45 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <stack>
#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

std::stack<int> st[2];

int main() {
	int n;
	scanf( "%d", &n );
	int cur = 0;
	long long ans = 0;
	for( int i = 1; i <= n; i ++ ) {
		int tmp;
		scanf( "%d", &tmp );
		if( st[cur].empty() ) {
			ans ++;
			st[cur].push(tmp);
		}
		else if( st[cur ^ 1].empty() ) {
			ans ++;
			st[ cur ^ 1 ].push(tmp);
		}
		else if( tmp != st[cur].top() ) {
			ans ++;
			st[cur].push(tmp);
		}
		else {
			if( tmp != st[ cur ^ 1 ].top() ) 
				ans ++;
			st[ cur ^ 1 ].push(tmp);
		}
		cur ^= 1;
	}
	printf( "%lld\n", ans );
}
