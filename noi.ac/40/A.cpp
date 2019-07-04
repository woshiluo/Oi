#include <cstdio>
#include <cstring>

inline int Aabs(int a){return a<0?(0-a):a;}

int n,len,alen;
char a[110000],t[1100000],tmp;

int main(){
	scanf("%d",&n);
	getchar();
	for(int i=1;i<=n;i++){
		int j=1;
		scanf("%s",t);
		len=strlen(t);
		alen=alen>len?alen:len;
		int k=1;
		for(int j=len-1;j>=0;j--){
			if(a[k]==0) a[k]=t[j];
			else a[k]=Aabs(t[j]-a[k])+'a';
			k++;
		}
	}
	for(int i=alen;i>=1;i--) printf("%c",a[i]);
}
