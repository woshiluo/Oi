// Woshiluo<woshiluo@woshiluo.site>
// Started at 2020-04-08 22:53
// Blog: https://blog.woshiluo.com
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <map>
#include <iostream>

template<class T> 
T Min( T a, T b ) { return a < b? a: b; }
template<class T> 
T Max( T a, T b ) { return a > b? a: b; }
template<class T> 
void chk_Min( T &a, T b ) { if( a > b ) a = b; }
template<class T> 
void chk_Max( T &a, T b ) { if( a < b ) a = b; }

long long n;
std::map<long long, long long> mp;

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	scanf( "%lld", &n );
	long long la = 1;
	long long sum = 0, ans = 0;
	for( int i = 1; i <= n; i ++ ) {
		long long cur, tmp;
		scanf( "%lld", &cur );
		tmp = - sum - cur;
		if( cur == 0 ) {
			mp.clear();
			sum = 0;
			la = i + 1;
			continue;
		}
		if( mp.find( tmp ) != mp.end() ) {
			long long pos = mp[tmp];
			ans += ( i - pos + 1LL ) - 1LL;
			la = pos + 1;
			sum = 0;
			mp.clear();
		}
		else 
			ans += ( i - la + 1LL );

		sum += cur;
		mp[ cur - sum ] = i;
	}
	printf( "%lld\n", ans );
}
