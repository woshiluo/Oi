// Woshiluo<woshiluo@woshiluo.site>
// 2020/12/17 23:26:48 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }
template <class T> 
T aabs( T a ) { return ( a < 0 )? ( - a ): a; }

typedef long long ll;

const ll N = 1e5 + 1e4;


struct Opt {
	ll time, gol;
} opt[N];

inline bool in( ll left, ll rig, ll val ) {
	if( rig < left )
		std::swap( left, rig );
	return ( left <= val ) && ( val <= rig );
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	ll T;
	scanf( "%lld", &T );
	while( T -- ) {
		ll n;
		scanf( "%lld", &n );
		for( ll i = 1; i <= n; i ++ ) {
			scanf( "%lld%lld", &opt[i].time, &opt[i].gol );
		}
		opt[ n + 1 ].time = opt[n].time + (int)(2e9);
		opt[ n + 1 ].gol = opt[n].gol;
		n ++;

		ll cur_step = 0, gol_step = 0, ans = 0, gol_id = 0;
		for( ll i = 1; i <= n; i ++ ) {
			// Before
			if( aabs( gol_step - cur_step ) <= aabs( opt[i].time - opt[ i - 1 ].time ) ) {
				if( gol_id != 0 && i == gol_id + 1 ) 
					ans ++;
				else if( i - 1 != 0 && in( cur_step, gol_step, opt[ i - 1 ].gol ) ) 
					ans ++;
				cur_step = gol_step;
			}
			else {
				ll nxt_step = cur_step + ( gol_step < cur_step ? -1: 1 ) * aabs( opt[i].time - opt[ i - 1 ].time );
				if( in( cur_step, nxt_step, opt[ i - 1 ].gol ) ) 
					ans ++;
				cur_step = nxt_step;
				continue;
			}
			
			// On opt[i].time
			gol_id = i;
			gol_step = opt[i].gol;
		}
		
		printf( "%lld\n", ans );
	}
}
