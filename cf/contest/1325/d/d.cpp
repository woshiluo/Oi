// Woshiluo Luo<woshiluo@woshiluo.site>  
// 2020/03/14 23:39:20 
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <algorithm>

template<class T>
T Min( T _a, T _b ) { return _a < _b? _a: _b; }
template<class T>
T Max( T _a, T _b ) { return _a > _b? _a: _b; }
template<class T>
T chk_Min( T &_a, T _b ) { return _a = (_a < _b? _a: _b); }
template<class T>
T chk_Max( T &_a, T _b ) { return _a = (_a > _b? _a: _b); }

unsigned long long u, v;
int bit_u[110], bit_less[110], bit_cnt[110];
std::vector<unsigned long long> ans;

inline void noans() {
	printf( "-1\n" );
	exit(0);
}

void to_bit( unsigned long long a, int bit[] ) {
	int cnt = 0;
	while( a ) {
		bit[ ++ cnt ] = a & 1;
		a >>= 1;
	}
}

int main() {
	scanf( "%llu%llu", &u, &v );
	if( v < u ) 
		noans();
	
	to_bit( v - u, bit_less );
	to_bit( u, bit_u );

	for( int i = 1; i <= 100; i ++ ) {
		bit_cnt[i] = bit_u[i];
	}
	int p = 64; 
	int cnt = 0;
	while( p ) {
		bit_cnt[p] += ( cnt - ( cnt & 1 ) );
		cnt = cnt & 1;
		if( bit_less[p] )
			cnt ++;
		p --; cnt <<= 1;
	}

	if( cnt != 0 )
		noans();

	bool flag = true;
	while( flag ) {
		flag = false; 
		unsigned long long out = 0;
		unsigned long long p = 1;
		for( int i = 1; i <= 64; i ++, p <<= 1 ) {
			if( bit_cnt[i] ) {
				out = out | p;
				bit_cnt[i] --;
				flag = true;
			}
		}
		if( flag )
			ans.push_back(out);
	}

	cnt = ans.size();
	printf( "%d\n", cnt );
	for( int i = 0; i < cnt; i ++ ) {
		printf( "%llu ", ans[i] );
	}
}
