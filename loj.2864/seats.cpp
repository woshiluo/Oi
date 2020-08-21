#include "seats.h"

int h, w;
bool flag_sub5;
std::vector<int> r;

void give_initial_chart(int H, int W, 
		std::vector<int> R, std::vector<int> C) {
	r = R; h = H, w = W;
	if( W == 1 ) {
		flag_sub5 = 1;
	}
}

int swap_seats(int a, int b) {
	return r[a];
}
