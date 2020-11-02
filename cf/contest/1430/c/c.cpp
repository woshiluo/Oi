// Woshiluo<woshiluo@woshiluo.site>
// 2020/10/11 17:38:26 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <stack>
#include <vector>
#include <algorithm>

using std::make_pair;

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

int T;

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		int n;
		scanf( "%d", &n );

		std::stack<int> st;
		std::vector<std::pair<int, int>> ans;
		for( int i = 1; i <= n; i ++ ) {
			st.push(i);
		}

		for( int i = 1; i < n; i ++ ) {
			int a = st.top(); st.pop();
			int b = st.top(); st.pop();
			st.push( ( a + b + 1 ) / 2 );
			// printf( "%d %d\n", a, b );
			ans.push_back( make_pair( a, b ) );
		}
		printf( "%d\n", st.top() );
		for( auto opt: ans ) {
			printf( "%d %d\n", opt.first, opt.second );
		}
	}
}
