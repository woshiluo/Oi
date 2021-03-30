#include <stdio.h>

int c[1100000];


int main(){
	int n;
	scanf("%d",&n);
	c[1]=1;
	c[2]=2;
	for(int i=0;i<n;i++){
		int s;
		scanf("%d",&s);
		if(s==1) {
			printf("1\n");
			continue;
		}
		if(s==2) {
			printf("2\n");
			continue;
		}
		int temp=3;
		while(1){
			c[temp]=(2*c[temp-1]+c[temp-2])%32767;
			if(temp==s) break;
			temp++;
		}
		printf("%d\n",c[s]);
	}

}
