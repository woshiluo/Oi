#include <cstdio>
#include <ctime>
#include <cstdlib>

int main(){
	srand( time(0) );
	printf("%d", rand() % 2);
}
