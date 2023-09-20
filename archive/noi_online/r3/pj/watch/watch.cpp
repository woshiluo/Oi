#include <cstdio>
#include <cstring>

#include <bitset>
#include <algorithm>

int read() {
  int x = 0, w = 1; char ch = 0;
  while (ch < '0' || ch > '9') { if (ch == '-') w = -1; ch = getchar(); }
  while (ch >= '0' && ch <= '9') { x = x * 10 + (ch - '0'); ch = getchar(); }
  return x * w;
}

inline void write(int x) {
	static int sta[35]; int top = 0;
	do { sta[top++] = x % 10, x /= 10; } while (x);
	while (top) putchar(sta[--top] + 48);
}

const int N = 500010;

int n, m, V;
int wat[N];
std::bitset<N> f;

inline void oz(int v){
	for(int i=V;i>=v;i--){
		if( f[ i - v ] == false ) 
			continue;
		f[i]=true;
	}
}

inline void wq(int v){
	for(int i=v;i<=V;i++){
		if( f[ i - v ] == false ) 
			continue;
		f[i] = true;
	}
}

inline void bit_bag( int v, int num ) {
	int k = 1, tmp = k * v;
	while( num >= k ) {
		num -= k;
		oz( k * v );
		k <<= 1;
		tmp <<= 1;
	}
	k = num;
	oz( k * v );
}

int main(){
//	freopen( "watch.in", "r", stdin );
//	freopen( "watch.out", "w", stdout );

	f[0] = true;
	n = read(), m = read();
	V = 500002;
	for( int i = 1 ; i <= n ; i ++) {
		int v = read();
		int m = read();
		if( m == -1 || 1LL * m * v > V ) 
			wq(v);
		else if( m == 1 )
			oz(v);
		else 
			bit_bag( v, m );
	}
	for( int i = 1, tmp; i <= m; i ++ ) {
		tmp = read();
		if( f[tmp] )
			printf( "Yes\n" );
		else
			printf( "No\n" );
	}

	fclose( stdin );
	fclose( stdout );
	return 0;
}
