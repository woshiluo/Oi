#include <cstdio>
#include <cstring>

const int N=1100000;

char a[N],b[N];
int kmp[N];
int alen,blen,k;


int main(){
	scanf("%s",a+1);
	scanf("%s",b+1);

	alen=strlen(a);
	blen=strlen(b);
	
	for(int i=2;i<=blen;i++){
		while(k&&b[i]!=b[k+1]) k=kmp[k];
		if(b[i]==b[i+1]) k++;
		kmp[i]=k;
	}	

	k=0;

	for(int i=1;i<=alen;i++){
		while(k&&a[i]!=b[k+1]) k=kmp[k];
		if(a[i]==b[k+1]) k++;
		if(k==blen){printf("%d\n",i-blen+1);k=kmp[k];}
	}
	for(int i=1;i<=blen;i++) printf("%d ",kmp[i]);
}
