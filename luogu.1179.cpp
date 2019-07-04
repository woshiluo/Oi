#include <cstdio>
using namespace std;

int main(){
	int n,m,sum=0;
	scanf("%d%d",&n,&m);
	for(int i=n;i<=m;i++){
		int temp=i;
		while(temp>=10){
			if(temp%10==2) sum++;
			temp/=10;
		}
		if(temp==2) sum++;
	}
	printf("%d",sum);
}
