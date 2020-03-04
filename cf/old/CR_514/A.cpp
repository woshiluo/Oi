#include <cstdio>
using namespace std;

const int N=110000;

int t[N],l[N];
int n,L,a,cnt,ans;


int main(){
	scanf("%d%d%d",&n,&L,&a);
	if(n==0){
		printf("%d",L/a);
		return 0;
	}
	for(int i=1;i<=n;i++){
		scanf("%d%d",&t[i],&l[i]);		
		ans+=(t[i]-(t[i-1]+l[i-1]))/a;		
	}
	ans+=(L-(t[n]+l[n]))/a;
	printf("%d",ans);
}
