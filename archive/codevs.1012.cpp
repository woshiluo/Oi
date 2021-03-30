#include <cstdio>
#include <cmath>
using namespace std;

int gcd(int n,int m){
	if(m==0) return n;
	return gcd(m,n%m);
}

int main(){
	int x,y,ans=0;
	scanf("%d %d",&x,&y);
	int cnt=x*y;
	for(int i=x;i<cnt;i++){
		if(i*(cnt/i/x)==y){
			if(gcd(i,cnt/i)==x){
				ans++;
			}
		}
	}
	printf("%d",ans);
}
