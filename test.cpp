#include <cstdio>

class a{
	public:
		int A;
		class b{
			public:
				int B;
				class c{
					public:
						int C;
						int f(int k);
				}h;
				int q(int w);
		}g;
}s;

int a::b::q(int w){
	printf("%d", w);
	return w;
}

int a::b::c::f(int k){
	printf("%d",B * k);
	return k;
}

//int a::b::c::f(int k){
//	printf("%d", k);
//	return k;
//}

int main(){
	s.g.h.f(2);
}
