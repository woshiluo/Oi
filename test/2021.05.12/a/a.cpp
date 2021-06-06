#include <cstdio>
#include <cstring>

#include <map>
#include <vector>

template <class T> 
T ksm( T a, int p ) {
	T res = 1;
	while(p) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}

const int PRE_N = 1e6 + 1e5;
const int mod = 1e9 + 7;

int n, m;
std::vector<int> prime;
bool is_prime[PRE_N];

struct ModInt {
	int cur;
	ModInt( int _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

	ModInt operator +( const ModInt &b ) const { return ( cur + b.cur ) % mod; }
	ModInt operator -( const ModInt &b ) const { return ( ( cur - b.cur ) + mod ) % mod; }
	ModInt operator *( const ModInt &b ) const { return ( 1LL * cur * b.cur ) % mod; }
	ModInt operator /( const ModInt &b ) const { return ( 1LL * cur * ksm( b, mod - 2 ).cur ) % mod; }

	inline void output( const char end = '\n' ) const {
		printf( "%d%c", cur, end );
	}
};
ModInt phi[PRE_N], muphi[PRE_N], sum_phi[PRE_N], sum_muphi[PRE_N];
int min_prime[PRE_N];

namespace get_phi {
	// S = sum_h
	// h = f * g
	// phi * 1 = id
	ModInt S( int pos ) { return ( ModInt(1) + pos ) * pos / 2; }
	ModInt g( int pos ) { return pos; }
	// TODO: May unorderd_map
	std::map<int, ModInt> mp;
	ModInt sum_f( int pos ) {
		if( pos < PRE_N ) 
			return sum_phi[pos];
		if( mp.count(pos) ) 
			return mp[pos];
		ModInt res = S(pos);
		for( int l = 2, r; l <= pos; l = r + 1 ) {
			r = pos / ( pos / l );
			res = res - ( g(r) - g( l - 1 ) ) * sum_f( pos / l );
		}
		return mp[pos] = res;
	}
}

namespace get_muphi {
	// S = sum_h
	// h = f * g
	// muphi * 1 = phi
	// phi * mu = muphi
	ModInt S( int pos ) { return get_phi::sum_f(pos); }
	ModInt g( int pos ) { return pos; }
	// TODO: May unorderd_map
	std::map<int, ModInt> mp;
	ModInt sum_f( int pos ) {
		if( pos < PRE_N ) 
			return sum_muphi[pos];
		if( mp.count(pos) ) 
			return mp[pos];
		ModInt res = S(pos);
		for( int l = 2, r; l <= pos; l = r + 1 ) {
			r = pos / ( pos / l );
			res = res - ( g(r) - g( l - 1 ) ) * sum_f( pos / l );
		}
		return mp[pos] = res;
	}
}

void pre() {
	muphi[1] = phi[1] = 1; 
	sum_phi[1] = sum_muphi[1] = 1;
	memset( is_prime, true, sizeof( is_prime ) );
	for( int i = 2; i < PRE_N; i ++ ) {
		if( is_prime[i] == true ) {
			min_prime[i] = i;
			muphi[i] = i - 2; phi[i] = i - 1;
			prime.push_back(i);
		}
		for( auto p: prime ) {
			if( 1LL * p * i >= PRE_N ) 
				break;
			int cur = p * i;
			is_prime[cur] = false;
			if( i % p == 0 ) { 
				min_prime[cur] = min_prime[i] * p;
				phi[cur] = phi[i] * p;
				if( min_prime[i] == i ) 
					muphi[cur] = phi[cur] - phi[i];
				else 
					muphi[cur] = muphi[ min_prime[i] * p ] * muphi[ i / min_prime[i] ];
			}
			else {
				min_prime[cur] = p;
				phi[cur] = phi[i] * phi[p];
				muphi[cur] = muphi[i] * muphi[p];
			}
		}
	}
	for( int i = 2; i < PRE_N; i ++ ) {
		sum_phi[i] = sum_phi[ i - 1 ] + phi[i];
		sum_muphi[i] = sum_muphi[ i - 1 ] + muphi[i];
	}
}

ModInt f( int a, int b ) {
	int min = std::min( a, b );
	ModInt res = 0;
	for( int l = 1, r; l <= min; l = r + 1 ) {
		r = std::min( a / ( a / l ), b / ( b / l ) );
		res = res + ModInt(1) * ( a / l ) * ( b / l ) * ( get_muphi::sum_f(r) - get_muphi::sum_f( l - 1 ) );
	}
	return res;
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	pre();
	scanf( "%d%d", &n, &m );
	f(n,m).output();
}
