#include <cstdio>
using namespace std;

const int N=1100000;

int a[N];
int n,cnt;

int main(){
	scanf("%d",&n);
	if(n==1){
		printf("1");
		return 0;
	}
	if(n==2){
		printf("1 2");
		return 0;
	}
	if(n==3){
		printf("1 1 3");
		return 0;
	}
	cnt=1;
	while(n>3){
		for(int i=1;i<=(n+1)>>1;i++) printf("%d ",cnt);
		n>>=1;
		cnt<<=1;
	}
	if(n==3){
		printf("%d %d %d",cnt,cnt,cnt*3);
	}
	if(n==2){
		printf("%d %d\n",cnt,cnt*2);
	}
}
