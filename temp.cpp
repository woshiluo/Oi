#include <cstdio>
#include <cstring>

int a[100];

int main(){
	memset(a, -0x7f, sizeof(a));
	printf("%d",a[1]);
	printf("\n2147483647");
}
