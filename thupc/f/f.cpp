/*
 * f.cpp 2023-12-17
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
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

#include <vector>
#include <algorithm>

using i8 = int8_t;
using u8 = uint8_t;

using i16 = int16_t;
using u16 = uint16_t;

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
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
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
T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 128;

struct Counter {
	int k;
	void output() {
		k --;
		if( k == 0 )
			std::exit(0);
	}
} counter;

enum CommandType {
	Slackoff,
	Move,
	Swap,
	Mirror,
	Replace,
	Active,
	Trigger,
};

struct Command {
	CommandType type;
	CommandType target;
	Command* p;

	bool h;
	i8 x, y, z;

	Command* clone() {
		Command* res = new Command();
		res -> h = h;
		res -> x = x; res -> y = y; res -> z = z;
		res -> type = type; res -> target = target;
		if( p && type == CommandType::Trigger ) 
			res -> p = p -> clone();
		else
			res -> p = p;
		return res;
	}

	Command() { h = 0; x = y = z = 0; p = 0; }
//	~Command() { if(p) delete p; }
};

struct Robot;

Robot* get_robots_by_id( ci32 id );

struct Robot {/*{{{*/
	int id, l, r, n;
	std::vector<Command*> commands;

	Robot() { commands.push_back(0); }
	Robot* get_pointer( ci32 h ) { return get_robots_by_id( h == 0? l: r ); }

	void exec();

	void active() {
		ci32 size = commands.size();
		for( int i = 1; i < size; i ++ ) {
			this -> exec( commands[i] );
		}
	}

	void slackoff( bool triggered = false ) {
		printf( "Robot %d slacks off.\n", id ); counter.output();
		if( this -> r != id )
			this -> get_pointer(1) -> trigger( CommandType::Slackoff, triggered );
	}

	void move( ci32 h, ci32 z, bool triggered = false ) {
		if( h == 0 ) {
			l += z;
			l %= n;
		}
		if( h == 1 ) {
			r += z;
			r %= n;
		}
		printf( "Robot %d moves its %s hand towards Robot %d.\n", this -> id, h == 0? "left": "right", this -> get_pointer(h) -> id ); counter.output();
		if( this -> r != id )
			this -> get_pointer(1) -> trigger( CommandType::Move, triggered );
	}

	void swap( Robot* another, i32 x, i32 y, bool triggered = false ) {
		printf( "Robot %d swaps a line of command with Robot %d.\n", this -> id, another -> id ); counter.output();
		std::swap( another -> commands[x], this -> commands[y] );
		if( this -> r != id )
			this -> get_pointer(1) -> trigger( CommandType::Swap, triggered );
	}

	void mirror( Robot* another, ci32 x, bool triggered = false ) {
		printf( "Robot %d modifies a line of command of Robot %d.\n", this -> id, another -> id ); counter.output();
		another -> commands[x] -> h ^= 1;
		if( another -> commands[x] -> type == CommandType::Trigger )
			another -> commands[x] -> p -> h ^= 1;
		if( this -> r != id )
			this -> get_pointer(1) -> trigger( CommandType::Mirror, triggered );
	}

	void replace( Robot* another, ci32 x, Command* p, bool triggered = false ) {
		printf( "Robot %d replaces a line of command of Robot %d.\n", this -> id, another -> id ); counter.output();
		another -> commands[x] = p -> clone();
		if( this -> r != id )
			this -> get_pointer(1) -> trigger( CommandType::Replace, triggered );
	}

	void active( Robot* another, bool triggered = false ) {
		printf( "Robot %d activates Robot %d.\n", this -> id, another -> id ); counter.output();
		another -> active();
		if( this -> r != id )
			this -> get_pointer(1) -> trigger( CommandType::Active, triggered );
	}

	void trigger( CommandType type, bool triggered ) {
		ci32 size = commands.size();
		for( int i = 1; i < size; i ++ ) {
			if( commands[i] -> type == CommandType::Trigger && ( commands[i] -> target == type || ( triggered && commands[i] -> target == CommandType::Trigger ) ) ) {
				this -> exec( commands[i] -> p, true );
				break;
			}
		}
	}

	void exec( Command* cur_command, bool triggered = false ) {
		switch(cur_command -> type) {
			case CommandType::Slackoff:
				this -> slackoff(triggered);
				break;
			case CommandType::Move:
				this -> move( cur_command -> h, cur_command -> z, triggered );
				break;
			case CommandType::Swap: 
				this -> swap( get_pointer( cur_command -> h ), cur_command -> x, cur_command -> y, triggered );
				break;
			case CommandType::Mirror: 
				this -> mirror( get_pointer( cur_command -> h ), cur_command -> x, triggered );
				break;
			case CommandType::Replace:
				this -> replace( get_pointer( cur_command -> h ), cur_command -> x, cur_command -> p, triggered );
				break;
			case CommandType::Active: 
				this -> active( get_pointer( cur_command -> h ), triggered );
				break;
			case CommandType::Trigger:
				break;
		}
	}
} robots[N];/*}}}*/

Robot* get_robots_by_id( ci32 id ) { return &robots[id]; }

CommandType read_command_type() {/*{{{*/
	static char op[16];
	scanf( "%s", op );
	while( op[ strlen(op) - 1 ] == ':' )
		op[ strlen(op) - 1 ] = 0;
	if( strcmp( op, "SLACKOFF" ) == 0 ) {
		return CommandType::Slackoff;
	}
	if( strcmp( op, "MOVE" ) == 0 ) { 
		return CommandType::Move;
	}
	if( strcmp( op, "SWAP" ) == 0 ) { 
		return CommandType::Swap;
	}
	if( strcmp( op, "MIRROR" ) == 0 ) { 
		return CommandType::Mirror;
	}
	if( strcmp( op, "REPLACE" ) == 0 ) { 
		return CommandType::Replace;
	}
	if( strcmp( op, "ACTIVATE" ) == 0 ) { 
		return CommandType::Active;
	}
	if( strcmp( op, "TRIGGER" ) == 0 ) {
		return CommandType::Trigger;
	}
	return CommandType::Slackoff;
}/*}}}*/

Command* read_command() {/*{{{*/
	Command *cur = new Command();
	cur -> type = read_command_type();
	switch( cur -> type ) {
		case CommandType::Slackoff:
			break;
		case CommandType::Move:
			cur -> h = read<i32>();
			cur -> z = read<i32>();
			break;
		case CommandType::Swap:
			cur -> h = read<i32>();
			cur -> x = read<i32>();
			cur -> y = read<i32>();
			break;
		case CommandType::Mirror:
			cur -> type = CommandType::Mirror;
			cur -> h = read<i32>();
			cur -> x = read<i32>();
			break;
		case CommandType::Replace:
			cur -> h = read<i32>();
			cur -> x = read<i32>();
			cur -> p = read_command();
			break;
		case CommandType::Active:
			cur -> h = read<i32>();
			break;
		case CommandType::Trigger:
			cur -> target = read_command_type();
			cur -> p = read_command();
			break;
	}

	return cur;
}/*}}}*/


int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif
	ci32 n = read<i32>();
	ci32 m = read<i32>();
	ci32 k = read<i32>();

	counter.k = k;

	for( int i = 0; i < n; i ++ ) {
		robots[i].n = n;
		robots[i].id = i;

		robots[i].l = read<i32>();
		robots[i].r = read<i32>();
		for( int j = 0; j < m; j ++ ) {
			robots[i].commands.push_back(read_command());
		}
	}

	while(1) {
		for( int i = 0; i < n; i ++ ) {
			robots[i].active();
		}
	}
}
