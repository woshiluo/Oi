#include <cstdio>
using namespace std;

int a,b,c,d,e,f,g;

int main(){
	scanf("%d%d%d%d",&a,&b,&c,&d);
	e=c-a-1;
	f=(60-b)+d;
	if(f>=60) {f-=60;e++;}
	printf("%d %d",e,f);
}
