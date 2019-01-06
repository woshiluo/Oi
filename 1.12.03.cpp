#include <stdio.h>

bool jl(double a,int b){
	if(a>=37.5&&b==1) return true;
	else return false;
	
}

int main(){
	int n,ans=0;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		char a[10];
		double b;
		int c;
		scanf("%s %lf %d",a,&b,&c);
		if(jl(b,c)){
			ans++;
			printf("%s\n",a);
		}
	}
	printf("%d",ans);
	
}
