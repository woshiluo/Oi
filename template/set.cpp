struct Set {
	int set[N];
	void init( ci32 n ) { for( int i = 0; i <= n; i ++ ) set[i] = i; }
	int get_fa( ci32 cur ) {
		if( set[cur] == cur )
			return cur;
		set[cur] = get_fa( set[cur] );
		return set[cur];
	}
	int& operator[]( const int cur ) { 
		return set[ get_fa(cur) ];
	}
} set;
