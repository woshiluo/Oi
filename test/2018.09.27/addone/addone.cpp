#include <cstdio>
#include <cstring>
#include <algorithm>

inline int nid(char now){
	if(now>='0'&&now<='9') return now-'0';
	if(now>='A'&&now<='Z') return now-'A'+10;
	return 0;
}

inline char _nid(int now){
	if(now>=0&&now<=9) return now+'0';
	else return now-10+'A';
}

struct number{
	int n[210],len;
}num[40],ori;

int tlen,jz,ncnt;
bool flag;
char t[210];

bool cmp(number a,number b){
	for(int i=0;i<=a.len&&i<=b.len;i++){
		if(a.n[i]!=b.n[i]) return a.n[i]<b.n[i];
	}
	return a.len>b.len;
}

int main(){
	freopen("addone.in","r",stdin);
	freopen("addone.out","w",stdout);
	scanf("%s",t);	
	tlen=strlen(t);
	ori.len=tlen-1;
	for(int i=tlen-1;i>=0;i--){
		ori.n[tlen-i-1]=nid(t[i]);
		if(ori.n[tlen-i-1]+1>jz) jz=ori.n[tlen-i-1]+1;
	}
	for(int i=jz;i<=36;i++){
		flag=false;
		ncnt++;		
		num[ncnt]=ori;
		num[ncnt].n[0]++;
		for(int j=0;j<=num[ncnt].len;j++){
			if(num[ncnt].n[j]>=i){
				num[ncnt].n[j+1]+=num[ncnt].n[j]/i;
				num[ncnt].n[j]%=i;	
				if(num[ncnt].n[j]!=num[ncnt-1].n[j]) flag=true;
			}
			else{
				if(num[ncnt].n[j]!=num[ncnt-1].n[j]) flag=true;
				break;
			}
		}
		if(num[ncnt].n[num[ncnt].len+1]>0) num[ncnt].len++;
		if(num[ncnt].len!=num[ncnt-1].len) flag=true;
		if(!flag) ncnt--;
	}
	std::sort(num+1,num+ncnt+1,cmp);
	for(int i=1;i<=ncnt;i++){
		for(int j=num[i].len;j>=0;j--){
			printf("%c",_nid(num[i].n[j]));	
		}
		printf("\n");
	}
	fclose(stdin);
	fclose(stdout);
}
