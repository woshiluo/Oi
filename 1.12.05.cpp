#include <stdio.h>
#include <string.h>

int ans=0,first;
char a[100000],b[1000000];

int main(){
	fgets(a,100000,stdin);
	fgets(b,1000000,stdin);
	int len1=strlen(a);
	int len2=strlen(b);
	for(int i=0;i<len2;i++){
		if(b[i]==a[0]||b[i]-a[0]==32||a[0]-b[i]==32){
			if(b[i-1]!=' '&&i>0)continue;
			int cnt=0;
			for(int j=0;j<len1-1;j++){
				if(b[i+j]==a[j]||b[i+j]-a[j]==32||a[j]-b[i+j]==32)cnt++;
			}
			if(cnt==len1-1&&(b[i+len1-1]=='\0'||b[i+len1-1]==' '||b[i+len1-1]=='\n')){
				if(ans==0){
					first=i;
				}
				ans++;
			}
		}
	}
	if(ans==0) printf("-1");
	else 	printf("%d %d",ans,first);
}
