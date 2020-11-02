// Woshiluo<woshiluo@woshiluo.site>
// 2020/10/26 11:36:18 
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

const int N = 2e5 + 1e4;

int to[N], val[N];
bool vis[N];

void no_ans() {
	printf( "NO\n" );
	exit(0);
}

void check( int left, int rig, int cur ) {
	vis[left] = vis[rig] = true;
	for( int i = left + 1; i < rig; i = to[i] + 1 ) {
		if( to[i] == 0 ) 
			continue;
		if( val[i] >= cur ) {
			no_ans();
		}
		check( i, to[i], val[i] );
	}
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int n;
	char op[3];
	scanf( "%d", &n );
	std::stack<int> q;
	for( int i = 1, x; i <= ( n + n ); i ++ ) {
		scanf( "%s", op );
		if( op[0] == '+' ) {
			q.push(i);
		}
		else if( op[0] == '-' ) {
			scanf( "%d", &x );
			if( q.empty() ) 
				no_ans();
			to[ q.top() ] = i;
			val[ q.top() ] = x;
			q.pop();
		}
	}

	for( int i = 1; i <= ( n + n ); i ++ ) {
		if( !vis[i] ) {
			check( i, to[i], val[i] );
		}
	}
	
	printf( "YES\n" );
	for( int i = 1; i <= ( n + n ); i ++ ) {
		if( val[i] != 0 )
			printf( "%d ", val[i] );
	}
}
