#include <cstdio>
int num = 0;
int n;
int a[1100],b[1100];
int acnt,bcnt,ccnt=1;
void Stack(int inWait,int outWait,int outs){
	if(n == outs){
		for(int i=1;i<=n;i++){
			printf("%d ",b[i]);
		}
		printf("\n");
		num++;
		return ;
	}
	if(inWait > 0){
		a[++acnt]=ccnt++;
		Stack(inWait-1,outWait+1,outs);
		a[acnt--]=0;
		ccnt--;
	}
	if(outWait > 0){
		int temp=a[acnt];
		b[++bcnt]=a[acnt];
		a[acnt--]=0;
		Stack(inWait,outWait-1,outs+1);
		a[++acnt]=temp;
		b[bcnt--]=0;
	}
}

int main(){
	scanf("%d",&n);
	Stack(n, 0, 0);
	printf("%d\n",num);
	return 0;
}
