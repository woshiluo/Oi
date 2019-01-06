#include<cstdio>
#include<cstring> 
using namespace std;

bool c;
char a[20],b[1100000];
int cnt=0,f;

int main(){
	scanf("%s\n",a);
	fgets(b,1100000,stdin);
	int len1=strlen(a);
	int len2=strlen(b);
	b[len2]='\0';
	for(int i=0;i<len2;i++){
		for(int j=0;j<len1;j++){
			if(b[i+j]!=a[j]&&b[i+j]!=a[j]-32&&b[i+j]-32!=a[j]) break;
			if(j==len1-1){
				if(b[i+j+1]!=' '&&i+j+1<len2)break;
				if(b[i-1]!=' '&&i-1>=0)break;
				cnt++;
				if(!c){
					f=i;
					c=true;
				}
			}
		}
	}
	if(c) printf("%d %d",f,cnt);
	else printf("-1");
	return 0;
}
