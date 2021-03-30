#include <cstdio>
using namespace std;

int main(){
	int a1,a2,a3,b1,b2,b3;
	scanf("%d %d %d %d %d %d",&a1,&b1,&a2,&b2,&a3,&b3);
	int s=a1*b1-a2*b2-a3*b3;
	printf("%d",s);
}
