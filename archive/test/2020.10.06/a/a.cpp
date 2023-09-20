#include <cstdio>

#include <algorithm>

const int N = 2e5 + 1e4;

int n;
int a[N];
long long sum[N];

bool check( long long mid ) {
	for( int st = 1; st <= n; st ++ ) {
		long long nxt = sum[ st - 1 ] + mid;
		int pos = std::lower_bound( sum + 1, sum + n + n + 1, nxt ) - sum;
		pos ++;
		if( pos == n + n + 2 || pos >= st + n ) 
			continue;
		nxt = sum[ pos - 1 ] + mid;
		pos = std::lower_bound( sum + 1, sum + n + n + 1, nxt ) - sum;
		pos ++;
		if( pos == n + n + 2 || pos >= st + n ) 
			continue;
		nxt = sum[ pos - 1 ] + mid;
		pos = std::lower_bound( sum + 1, sum + n + n + 1, nxt ) - sum;
		if( pos == n + n + 2 || pos >= st + n ) 
			continue;
		return true;
	}
	return false;
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	long long left = 0, rig = 0, res = 0;
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
		rig += a[i];
		sum[i] = sum[ i - 1 ] + a[i];
	}

	for( int i = 1; i <= n; i ++ ) {
		sum[ i + n ] = sum[ i + n - 1 ] + a[i];
	}

	while( left <= rig ) {
		long long mid = ( left + rig ) >> 1;
		if( check(mid) ) {
			res = mid;
			left = mid + 1;
		}
		else 
			rig = mid - 1;
	}

	printf( "%lld\n", res );
}
