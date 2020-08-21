// Woshiluo<woshiluo@woshiluo.site>
// 2020/06/30 09:33:34 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <queue>
#include <algorithm>

const int N = 4e5 + 1e4;
const int MAX = 0x3f3f3f3f;

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

int n, k;
int a[N], b[N], t[N];
std::priority_queue<int> both, ali, bob;

int main() {
#ifdef woshiluo
	freopen( "e1.in", "r", stdin );
	freopen( "e1.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &k );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d%d%d", &t[i], &a[i], &b[i] );
		if( a[i] == 1 && b[i] == 1 ) {
			both.push( -t[i] );
		}
		else if( a[i] == 1 ) {
			ali.push( -t[i] );
		}
		else if( b[i] == 1 ) {
			bob.push( -t[i] );
		}
	}
	long long ans = 0;
	for( int i = 1; i <= k; i ++ ) {
		int all_min = MAX, one_min = MAX;
		if( !both.empty() ) {
			chk_Min( all_min, - both.top() );
		}
		if( !ali.empty() && !bob.empty() ) {
			chk_Min( one_min, - ali.top() - bob.top() );
		}
		if( all_min == MAX && one_min == MAX ) {
			printf( "-1" );
			return 0;
		}
		if( one_min < all_min ) {
			ans += one_min;
			ali.pop(), bob.pop();
		}
		else {
			ans += all_min;
			both.pop();
		}
	}
	printf( "%lld\n", ans );
}
