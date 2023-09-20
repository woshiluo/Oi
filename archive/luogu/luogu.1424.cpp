#include <cstdio>
using namespace std;

int a[8]={0,250,250,250,250,250,0,0};
int x,n,cnt;

int main(){
	scanf("%d%d",&x,&n);
	int temp=n/7;
	n%=7;
	cnt+=1250*temp;
	for(int i=1;i<=n;i++){
		cnt+=a[x];
		x++;
		if(x>7)x-=7;
	}
	printf("%d",cnt);
}
