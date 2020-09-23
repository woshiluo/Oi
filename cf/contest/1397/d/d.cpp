// Woshiluo<woshiluo@woshiluo.site>
// 2020/08/31 00:16:02 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <queue>
#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

const int N = 110;

int T;
int n;

struct node {
	int id, val;
	bool operator< ( const node &b ) const { return val < b.val; }
};

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		std::priority_queue<node> q;
		scanf( "%d", &n );
		for( int i = 1, tmp; i <= n; i ++ ) {
			scanf( "%d", &tmp );
			q.push((node){ i, tmp });
		}
		int lst = 0;
		bool fir = true;
		while( !q.empty() ) {
			node top = q.top(); q.pop();
			if( top.id == lst ) {
				if( q.empty() ) 
					break;
				node top2 = q.top(); q.pop();
				top2.val --; lst = top2.id; fir ^= 1;
				if( top2.val != 0 ) 
					q.push(top2);
				q.push(top);
			}
			else {
				top.val --; lst = top.id; fir ^= 1;
				if( top.val != 0 ) 
					q.push(top);
			}
		}
		printf( "%s\n", fir? "HL": "T" );
	}
}
