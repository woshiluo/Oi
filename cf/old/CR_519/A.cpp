#include <cstdio>

int n,k,e,tmp;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&tmp);
		e+=tmp;
		k=k>tmp?k:tmp;
	}
	while(1){
		if(k*n-e>e){
			printf("%d",k);
			return 0;
		}
		k++;
	}
}
