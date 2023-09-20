#include <cstdio>

#include <queue>

struct node {
	int dep;
	long long cur, cnt;
	node( int _dep = 0, long long _cur = 0, long long _cnt = 0 ) { dep = _dep; cur = _cur; cnt = _cnt; }
	bool operator< ( const node &b ) const { return ( this -> cur == b.cur )? this -> dep > b.dep: this -> cur > b.cur; }
};

int n, k;
std::priority_queue<node> q;

inline long long Max( long long a, long long b ) { return a > b? a: b; }

int main() {
#ifdef woshiluo
	freopen( "luogu.2168.in", "r", stdin );
	freopen( "luogu.2168.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &k );
	for( int i = 1; i <= n; i ++ ) {
		long long tmp;
		scanf( "%lld", &tmp );
		q.push( (node){ 0, tmp, tmp } );
	}
	long long ans = 0;
	int max_h     = 0;
	int less = ( k - 1 ) - ( n - 1 ) % ( k - 1 );
	if( less == k - 1 ) 
		less = 0;
	for( int i = 1; i <= less; i ++ ) 
		q.push( (node){ 0, 0, 0 } );
	while( q.size() >= k ) {
		node nxt;
		for( int i = 1; i <= k; i ++ ) {
			node top  = q.top();
			nxt.dep   = Max( nxt.dep, top.dep );
			nxt.cnt  += top.cnt + top.cur;
			nxt.cur  += top.cur;
			q.pop();
		}
		nxt.dep ++;
		max_h  = Max( max_h, nxt.dep );
		ans   += nxt.cur;
		q.push( nxt );
	}
	printf( "%lld\n%d", ans, max_h );
}
