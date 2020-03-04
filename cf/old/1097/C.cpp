#include <cstdio>
#include <cstring>
#include <algorithm>

int n,ans,len,rcnt,icnt,lcnt,ricnt,l,r,tmp;
int left[510000],rig[510000];
char s[510000];

int main(){
#ifndef ONLINE_JUDGE
    freopen("C.in","r",stdin);
#endif
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        l=r=0;
        len=strlen(s+1); 
        for(int j=1;j<=len;j++){
            if(s[j]==')'){
                if(l>0) l--;
                else r++;
            }
            if(s[j]=='(') l++;
        }        
        if(l&&r) continue;
        if(l) left[++lcnt]=l;
        if(r) rig[++ricnt]=r;
        if(l==0&&r==0) icnt++;
    }
    std::sort(rig+1,rig+ricnt+1);
    std::sort(left+1,left+lcnt+1);
    l=1;r=1;
    while(l<=lcnt&&r<=ricnt){
        if(left[l]==rig[r]){
            ans++;
            l++,r++;
        }
        else if(left[l]<rig[r]) l++;
        else if(left[l]>rig[r]) r++;
    }
    printf("%d",ans+(icnt>>1));
}
