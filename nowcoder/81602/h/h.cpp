/*
 * h.cpp 2024-08-06
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#include <set>
#include <map>
#include <list>
#include <string>
#include <vector>
#include <algorithm>


const int STA_COUNT = 8;
const int MAX_LENGTH = 8196;

using i32 = int32_t;
using u32 = uint32_t;
using ci32 = const int32_t;
using cu32 = const uint32_t;

using i64 = int64_t;
using u64 = uint64_t;
using ci64 = const int64_t;
using cu64 = const uint64_t;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
constexpr T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
constexpr T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }
template <typename T>
T read() { 
	T sum = 0, fl = 1; 
	char ch = getchar();
	for (; isdigit(ch) == 0; ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}
template <class T> 
constexpr T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

std::map<std::string, i32> hash;
std::map<i32, std::string> rev_hash;

int get_hash( const char* str ) {
	std::string p = str;
	if( hash.count(p) ) 
		return hash[p];
	ci32 idx = hash.size();
	hash[p] = idx;
	rev_hash[idx] = p;
	return idx;
}

enum Statements{
	InsertStatement,
	SelectStatement,
	SelectInStatement,
	DeleteStatement,
	DeleteInStatement,
	BeginStatement,
	CommitStatement,
	AbortStatement
};

const char sta_str[8][32] = { 
	"insert(",
	"select(",
	"select_in(",
	"delete(",
	"delete_in(",
	"begin(",
	"commit(",
	"abort(",
};

struct SetValue {
	std::vector<i32> list;
};

struct Field {
	std::vector<i32> row;
};

struct Tabel {
	std::list<Field*> list;
} base_table, cur_table;

void insert( std::vector<i32> &row ) {
	Field *p = new Field;
	p -> row = row;
	cur_table.list.push_back(p);
}

SetValue select( ci32 output_id, ci32 con_id, ci32 con_value ) {
	SetValue value;
	for( auto &p: cur_table.list ) {
		if( p -> row[con_id] == con_value ) {
			value.list.push_back( p -> row[output_id] );
		}
	}
	return value;
}

SetValue select_in( ci32 output_id, ci32 con_id, const SetValue& con_value ) {
	std::set<i32> set;
	for( auto &x: con_value.list ) {
		set.insert(x);
	}
	SetValue value;
	for( auto &p: cur_table.list ) {
		if( set.count( p -> row[con_id] ) ) {
			value.list.push_back( p -> row[output_id] );
		}
	}
	return value;
};

size_t delete_( ci32 con_id, ci32 con_value ) {
	i32 cnt = 0;
	std::list<Field*> res;
	for( auto &x: cur_table.list ) {
		if( x -> row[con_id] == con_value ) {
			cnt ++;
			continue;
		}
		res.push_back(x);
	}
	cur_table.list = std::move(res);
	return cnt;
}

size_t delete_in( ci32 con_id, const SetValue& con_value ) {
	std::set<i32> set;
	for( auto &x: con_value.list ) {
		set.insert(x);
	}
	i32 cnt = 0;
	std::list<Field*> res;
	for( auto &x: cur_table.list ) {
		if( set.count( x -> row[con_id] ) ) {
			cnt ++;
			continue;
		}
		res.push_back(x);
	}
	cur_table.list = std::move(res);
	return cnt;
}

void begin() {
	cur_table = base_table;
}

void commit() {
	base_table = cur_table;
}

void abort_() {
}

Statements find_statements( const char *buf, int &p ) {
	for( int i = 0; i < STA_COUNT; i ++ ) {
		ci32 len = strlen( sta_str[i] );
		bool flag = true;
		for( int j = 0; j < len; j ++ ) {
			if( buf[ j + p ] != sta_str[i][j] ) {
				flag = false;
				break;
			}
		}
		if( flag ) {
			p += len;
			return (Statements)i;
		}
	}
	std::exit(-1);
}

int get_string( const char *buf, int &p ) {
	static char res[MAX_LENGTH];
	int res_cnt = 0;
	while( buf[p] == '(' || buf[p] == ',' || buf[p] == ')' ) 
		p ++;

	while( buf[p] != '(' && buf[p] != ',' && buf[p] != ')' ) {
		res[ res_cnt ] = buf[p];
		res_cnt ++;
		res[ res_cnt ] = 0;
		p ++;
	}

	while( buf[p] == '(' || buf[p] == ',' || buf[p] == ')' ) 
		p ++;

	return get_hash(res);
}

SetValue find_select( const char* buf, int &p ) {
	const Statements state = find_statements( buf, p );
	switch(state) {
		case SelectStatement: {
			ci32 p1 = get_string( buf, p );
			ci32 p2 = get_string( buf, p );
			ci32 p3 = get_string( buf, p );
			return select( p1, p2, p3 );
		};
		case SelectInStatement: {
			ci32 p1 = get_string( buf, p );
			ci32 p2 = get_string( buf, p );
			const SetValue value = find_select( buf, p );
			return select_in( p1, p2, value );
		};
		default: {
			std::exit(-1);
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "h.in", "r", stdin );
	freopen( "h.out", "w", stdout );
#endif


	ci32 n = read<i32>();
	ci32 m = read<i32>();
	for( int i = 1; i <= n; i ++ ) {
		static char buf[MAX_LENGTH];
		scanf( "%s", buf );
		get_hash(buf);
	}
	for( int i = 1; i <= m; i ++)  {
		int p = 0;
		static char buf[MAX_LENGTH];
		fgets( buf, MAX_LENGTH, stdin );
		while( buf[0] == '\n' || buf[0] == '\r' )
			fgets( buf, MAX_LENGTH, stdin );
		const Statements state = find_statements( buf, p );
		switch(state) {
			case InsertStatement: {
				std::vector<i32> list;
				for( int j = 0; j < n; j ++ )
					list.push_back( get_string( buf, p ) );
				insert(list);
				break;
			};
			case SelectStatement: {
				ci32 p1 = get_string( buf, p );
				ci32 p2 = get_string( buf, p );
				ci32 p3 = get_string( buf, p );
				const SetValue value = select( p1, p2, p3 );
				ci32 size = value.list.size();
				printf( "%d\n", size );
				if( size != 0 ) {
					printf( "%s\n", rev_hash[ *value.list.begin() ].c_str() );
					ci32 id = ( size >> 1 ) + ( size & 1 ) - 1;
					printf( "%s\n", rev_hash[ value.list[id] ].c_str() );
					printf( "%s\n", rev_hash[ *value.list.rbegin() ].c_str() );
				}
				break;
			};
			case SelectInStatement: {
				ci32 p1 = get_string( buf, p );
				ci32 p2 = get_string( buf, p );
				const SetValue p3 = find_select( buf, p );
				const SetValue value = select_in( p1, p2, p3 );
				ci32 size = value.list.size();
				printf( "%d\n", size );
				if( size != 0 ) {
					printf( "%s\n", rev_hash[ *value.list.begin() ].c_str() );
					ci32 id = ( size >> 1 ) + ( size & 1 ) - 1;
					printf( "%s\n", rev_hash[ value.list[id] ].c_str() );
					printf( "%s\n", rev_hash[ *value.list.rbegin() ].c_str() );
				}
				break;
			};
			case DeleteStatement: {
				ci32 p1 = get_string( buf, p );
				ci32 p2 = get_string( buf, p );
				ci32 res = delete_(p1, p2);
				printf( "%d\n", res );
				break;
			};
			case DeleteInStatement: {
				ci32 p1 = get_string( buf, p );
				const SetValue value = find_select( buf, p );
				ci32 res = delete_in(p1, value);
				printf( "%d\n", res );
				break;
			};
			case BeginStatement: {
				begin();
				break;
			};
			case CommitStatement: {
				commit();
				break;
			};
			case AbortStatement: {
				abort_();
				break;
			};
		}
	}
}
