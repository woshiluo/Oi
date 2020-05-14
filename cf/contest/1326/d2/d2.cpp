// Woshiluo Luo<woshiluo@woshiluo.site>  
// 2020/03/19 23:47:01 
#include <cstdio>
#include <cstring>

#include <algorithm>

template<class T>
T Min( T _a, T _b ) { return _a < _b? _a: _b; }
template<class T>
T Max( T _a, T _b ) { return _a > _b? _a: _b; }
template<class T>
T chk_Min( T &_a, T _b ) { return _a = (_a < _b? _a: _b); }
template<class T>
T chk_Max( T &_a, T _b ) { return _a = (_a > _b? _a: _b); }

const int N = 2e6 + 1e5;

int T;
char str[N];

char* process( char s[], int st, int ed ) {
	if( st > ed ) {
		char *proed = new char[3];
		proed[0] = 0;
		return proed;
	}
	int cur = 0;
	char *proed = new char[N];
	proed[0] = '^';
	for( int i = st; i <= ed; i ++ ) {
		proed[ ++ cur ] = '#';
		proed[ ++ cur ] = s[i];
	}
	proed[ ++ cur ] = '#';
	proed[ ++ cur ] = '$';
	proed[ cur + 1 ] = 0;
	return proed;
}


int* malache( char *s ) {
	int len = strlen(s);
	if( len <= 0 ) {
		int *tmp = new int[2];
		tmp[0] = -1;
		return tmp;
	}
	int *P = new int[N];
	len --;
	int center = 0, rig = 0;
	for( int i = 0; i <= len; i ++ ) {
		int mirror = 2 * center - i;
		if( rig > i )
			P[i] = Min( P[ mirror ], rig - i );
		else 
			P[i] = 0;

		while( s[ i + P[i] + 1 ] == s[ i - P[i] - 1 ] ) 
			P[i] ++;

		if( i + P[i] > rig ) {
			center = i;
			rig = i + P[i];
		}
	}

	int id = 0;
	for( int i = 1; i < len - 1; i ++ ) {
		if( i - P[i] == 1 ) {
			if( P[i] > P[id] ) 
				id = i;
		}
		if( i + P[i] == len - 1 ){
			if( P[i] > P[id] ) 
				id = i;
		}
	}
	int *tmp = new int[2];
	tmp[0] = ( id - P[id] ) / 2, tmp[1] = P[id];
	delete(P), delete(s);
	return tmp;
}

int main() {
#ifdef woshiluo
	freopen( "d2.in", "r", stdin );
	freopen( "d2.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%s", str + 1 );
		int len = strlen( str + 1 );
		int st = 0;
		while(1) {
			int left = st + 1, rig = len - st;
			if( str[left] == str[rig] && left < rig )
				st ++;
			else 
				break;
		}
		for( int i = 1; i <= st; i ++ ) 
			printf( "%c", str[i] );

		if( st + 1 <= len - st ) { 
			int *tmp = malache( process( str, st + 1, len - st ) );

			if( tmp[0] != -1 ) {
			for( int i = 0; i < tmp[1]; i ++ ) {
				printf( "%c", str[ st + tmp[0] + i + 1 ] );
			}
			}
			delete(tmp);
		}

		for( int i = len - st + 1; i <= len; i ++ ) {
			printf( "%c", str[i] );
		}

		printf( "\n" );

	}
}
