#include <cstdio>

#include <algorithm>

const int N = 3e5 + 1e4;
const int INF = 1e9 + 10;

inline int read() {
  int x = 0, w = 1;
  char ch = 0;
  while (ch < '0' || ch > '9') { if (ch == '-') w = -1; ch = getchar();}
  while (ch >= '0' && ch <= '9') { x = x * 10 + (ch - '0'); ch = getchar(); }
  return x * w; 
}

int n;
int tmp[N], b[3][N], cnt[3];
long long sum[3][N];

inline long long query( int i, int left, int rig ) {
	if( left > rig ) 
		return 0;
	return sum[i][rig] - sum[i][ left - 1 ];
}

long long check( int x, int y ) {
	int xy = y - x;
	int cnt_x = std::lower_bound( b[1] + 1, b[1] + 1 + cnt[1], x ) - b[1] - 1;
	int cnt_y = std::lower_bound( b[2] + 1, b[2] + 1 + cnt[2], y ) - b[2] - 1;
	int cnt_xy = std::lower_bound( b[0] + 1, b[0] + 1 + cnt[0], xy ) - b[0] - 1;
	return ( ( 1LL * cnt_x * x ) - query( 1, 1, cnt_x ) + 
		query( 1, cnt_x + 1, cnt[1] ) - ( 1LL * ( cnt[1] - cnt_x ) * x ) ) 
		+ 
		( ( 1LL * cnt_y * y ) - query( 2, 1, cnt_y ) + 
		query( 2, cnt_y + 1, cnt[2] ) - ( 1LL * ( cnt[2] - cnt_y ) * y ) ) 
		+
		( ( 1LL * cnt_xy * xy ) - query( 0, 1, cnt_xy ) + 
		query( 0, cnt_xy + 1, cnt[0] ) - ( 1LL * ( cnt[0] - cnt_xy ) * xy ) );
}

long long f_y( int x ) {
	int left = -INF, rig = INF;
	while( left < rig ) {
		int k = ( rig - left ) / 3;
		if( rig - left == 1 ) {
			if( check( x, left ) < check( x, rig ) ) 
				rig = left;
			else 
				left = rig;
			continue;
		}
		if( rig - left == 2 )  {
			int mid = left + 1;
			long long fx = check( x, left ), fy = check( x, rig ), fmid = check( x, mid );
			if( fmid <= fx && fmid <= fy ) 
				left = rig = mid;
			else if( fx <= fmid && fx <= fy ) 
				rig = left;
			else 
				left = rig;
			continue;
		}
		int l_mid = left + k, r_mid = rig - k;
		if( check( x, l_mid ) < check( x, r_mid ) ) 
			rig = r_mid;
		else 
			left = l_mid;
	}
	return check( x, left );
}

long long f_x() {
	int left = -INF, rig = INF;
	while( left < rig ) {
		int k = ( rig - left ) / 3;
		if( rig - left == 1 ) {
			if( f_y(left) < f_y(rig) ) 
				rig = left;
			else 
				left = rig;
			continue;
		}
		if( rig - left == 2 ) {
			int mid = left + 1;
			long long fx = f_y(left), fy = f_y(rig), fmid = f_y(mid);
			if( fmid <= fx && fmid <= fy ) 
				left = rig = mid;
			else if( fx <= fmid && fx <= fy ) 
				rig = left;
			else 
				left = rig;
			continue;
		}
		int l_mid = left + k, r_mid = rig - k;
		if( f_y( l_mid ) < f_y( r_mid ) ) 
			rig = r_mid;
		else 
			left = l_mid;
	}
	return f_y( left );
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	n = read();
	for( int i = 1; i <= n; i ++ ) {
		tmp[i] = read();
		if( i % 6 == 0 || i % 6 == 5 || i % 6 == 4 ) 
			tmp[i] = - tmp[i];
		b[ i % 3 ][ ++ cnt[ i % 3 ] ] = tmp[i];
	}
	for( int i = 0; i < 3; i ++ ) {
		std::sort( b[i] + 1, b[i] + cnt[i] + 1 );
		for( int j = 1; j <= cnt[i]; j ++ ) {
			sum[i][j] = sum[i][ j - 1 ] + b[i][j];
		}
	}

	printf( "%lld\n", f_x() );
}
