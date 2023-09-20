#include <cstdio>

const int N = 2e5 + 1e4;

inline int in() {
	int res = 0; char x = getchar();
	while( x < '0' || x > '9' )
		x = getchar();
	while( x >= '0' && x <= '9' ) {
		res = ( res * 10 ) + x - '0';
		x = getchar();
	}
	return res;
}

int n, cnt, ans;
int ed[N];

// BIT Start
int BIT[N];
int _n = N - 10;
inline int lowbit( int cur ) { return cur & ( - cur ); }
void add( int pos, int val ) {
	for( ; pos <= _n; pos += lowbit(pos) )
		BIT[pos] += val;
}
int query( int pos ) {
	int res = 0;
	for( ; pos; pos -= lowbit(pos) ) {
		res += BIT[pos];
	}
	return res;
}
// BIT End


int main() {
#ifdef woshiluo
	freopen( "luogu.2161.in", "r", stdin );
	freopen( "luogu.2161.out", "w", stdout );
#endif
	n = in();
	char op[5]; int x, y;
	for( int i = 1; i <= n ; i ++ ) {
		scanf( "%s", op );
		if( op[0] == 'A' ) {
			ans = 0;
			x = in(); y = in();
			while(1) {
				int left = 0, rig = y, sum_rig = query(y), res = 0;
				while( left <= rig ){
					int mid = ( left + rig ) >> 1;
					if( query(mid) < sum_rig ) {
						left = mid + 1;
					}
					else {
						res = mid;
						rig = mid - 1;
					}
				}
				while( res > 2 && query( res - 1 ) == sum_rig )
					res --;
				if( x <= ed[res] ) {
					add( res, -1 ); 
					ed[res] = 0;
					cnt --, ans ++;
				}
				else 
					break;
			}
			add( x, 1 );
			ed[x] = y; cnt ++;
			printf( "%d\n", ans );
		}
		else 
			printf( "%d\n", cnt );
	}
}
