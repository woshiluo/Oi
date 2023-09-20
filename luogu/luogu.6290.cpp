#include <cstdio>

#include <algorithm>

const int N = 5e4 + 1e3;
const double eqs = 1e-4;

struct part{ int time, v; };

int n, L, k;
part a[N], b[N];
bool used_a[N], used_b[N];

int st[N][2], st_cnt;

int main() {
#ifdef woshiluo
	freopen( "luogu.6290.in", "r", stdin );
	freopen( "luogu.6290.out", "w", stdout );
#endif
	scanf( "%d%d%d", &n, &L, &k );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d%d", &a[i].time, &a[i].v );
	}
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d%d", &b[i].time, &b[i].v );
	}

	for( int i = 1; i <= k; i ++ ) {
		int cnt = 0;
		double left = 0, rig = (2e9);
		while( left <= rig ) {
			cnt ++;
			double mid = ( left + rig ) / 2;

			double max_x = 0, min_y = 1e18;
			for( int i = 1; i <= n; i ++ ) {
				long long tmp = 0;
				if( used_a[i] == false ) {
					tmp = 1.0 * a[i].v * ( 1.0 * mid - a[i].time );
					if( tmp > max_x ) 
						max_x = tmp;
				}
				if( used_b[i] == false ) {
					tmp = 1.0 * L - 1.0 * b[i].v * ( 1.0 * mid - b[i].time );
					if( tmp < min_y ) 
						min_y = tmp;
				}
			}

			if( cnt >= 45 ) 
				break;
			if( max_x < min_y ) 
				left = mid + eqs;
			else 
				rig = mid - eqs;
		}	
		double mid = ( left + rig ) / 2.0;
		double max_x = 0, min_y = 1e18;
		int x_id = 0, y_id = 0;
		for( int i = 1; i <= n; i ++ ) {
			long long tmp = 0;
			if( used_a[i] == false ) {
				tmp = 1.0 * a[i].v * ( 1.0 * mid - a[i].time );
				if( tmp > max_x ) {
					max_x = tmp;
					x_id = i;
				}
			}
			if( used_b[i] == false ) {
				tmp = 1.0 * L - 1.0 * b[i].v * ( 1.0 * mid - b[i].time );
				if( tmp < min_y ) {
					min_y = tmp;
					y_id = i;
				}
			}
		}
		printf( "%d %d\n", x_id, y_id );
		used_a[ x_id ] = used_b[ y_id ] = true;
	}
}
