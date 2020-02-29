#include <cstdio>

#include <queue>
#include <algorithm>

inline int Min( int a, int b ) { return a < b? a: b; }
int readin() {
	int res = 0; char x = getchar();
	while( x < '0' || x > '9' ) 
		x = getchar();
	while( x >= '0' && x <='9' ) {
		res = res * 10 + ( x - '0' );
		x = getchar();
	}
	return res;
}

const int N = 1e5 + 1e4;

struct node {
	int len, la;
	bool operator< ( const node &b ) const{
		return this -> len > b.len;
	}
};

int n, ans;
int a[N];
std::priority_queue<node> q;
std::queue<node> tmp;

int main() {
#ifdef woshiluo
	freopen( "luogu.4447.in", "r", stdin );
	freopen( "luogu.4447.out", "w", stdout );
#endif
	n = readin();
	ans = n;
	for( int i = 1; i <= n; i ++ ) {
		a[i] = readin();
	}

	std::sort( a + 1, a + n + 1 );

	for( int i = 1; i <= n; i ++ ) {
		if( a[i] != a[ i - 1 ] && i != 1 ) {
			while( tmp.empty() == false ) {
				q.push( tmp.front() );
				tmp.pop();
			}
		}
		bool flag = false;
		while( q.empty() == false ) {
			node top = q.top(); q.pop();
			if( top.la + 1 == a[i] ) {
				flag = true;
				tmp.push( (node) { top.len + 1, a[i] } );
				break;
			}
			else
				ans = Min( ans, top.len );

		}
		if( !flag ) 
			tmp.push( (node) { 1, a[i] } );
	}

	while( tmp.empty() == false ) {
		q.push( tmp.front() );
		tmp.pop();
	}

	while( q.empty() == false ) {
		node top = q.top(); q.pop();
		ans = Min( ans, top.len );
	}

	printf( "%d\n", ans );
}
