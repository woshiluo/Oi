#include <cstdio>

#include <stack> 

const int N = 1e5 + 1e4;
const int K = 20;

int n, k, q;
int a[N], left[N][K], rig[N][K];
int pow_2[K];

int main() {
#ifdef woshiluo
	freopen( "loj.2395.in", "r", stdin );
	freopen( "loj.2395.out", "w", stdout );
#endif
	scanf( "%d%d%d", &n, &k, &q );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}
	{
		std::stack<int> st;
		for( int i = 1; i <= n; i ++ ) {
			while( !st.empty() && a[ st.top() ] <= a[i] ) {
				int top = st.top(); st.pop();
				rig[top][0] = i;
			}
			st.push(i);
		}
		while( !st.empty() ) {
			int top = st.top(); st.pop();
			rig[top][0] = n;
		}
	}
	{
		std::stack<int> st;
		for( int i = n; i >= 1; i -- ) {
			while( !st.empty() && a[ st.top() ] <= a[i] ) {
				int top = st.top(); st.pop();
				left[top][0] = i;
			}
			st.push(i);
		}
		while( !st.empty() ) {
			int top = st.top(); st.pop();
			left[top][0] = 1;
		}
	}

	pow_2[0] = 1;
	for( int k = 1; k < K; k ++ ) {
		pow_2[k] = pow_2[ k - 1 ] * 2;
		for( int i = 1; i <= n; i ++ ) {
			int tmp_l = left[i][ k - 1 ], tmp_r = rig[i][ k - 1 ];
			left[i][k] = std::min( left[tmp_l][ k - 1 ], left[tmp_r][ k - 1 ] );
			rig[i][k] = std::max( rig[tmp_l][ k - 1 ], rig[tmp_r][ k - 1 ] );
		}
	}

	while( q -- ) {
		int a, b;
		scanf( "%d%d", &a, &b );
		if( a > b ) 
			std::swap( a, b );

		int ans = 0;
		{
			int l = a, r = a;
			for( int k = 17; k >= 0; k -- ) {
				int tmp_l = std::min( left[l][k], left[r][k] ),
					tmp_r = std::max( rig[l][k], rig[r][k] );
				if( tmp_r >= b ) 
					continue;
				l = tmp_l; r = tmp_r;
				ans += pow_2[k];
			}
			a = r;
		}
		{
			int l = b, r = b;
			for( int k = 17; k >= 0; k -- ) {
				int tmp_l = std::min( left[l][k], left[r][k] ),
					tmp_r = std::max( rig[l][k], rig[r][k] );
				if( tmp_l <= a ) 
					continue;
				l = tmp_l; r = tmp_r;
				ans += pow_2[k];
			}
		}
		printf( "%d\n", ans );
	}
}
