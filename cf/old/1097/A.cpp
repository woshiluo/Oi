#include <cstdio>

bool vis_left[1100],vis_rig[1110],ans;
char s[110];

int main(){
    scanf("%s",s);
    vis_left[s[0]]=true;
    vis_rig[s[1]]=true;
    for(int i=1;i<=5;i++){ 
        scanf("%s",s);
        if(vis_left[s[0]]) ans=1;
        else if(vis_rig[s[1]]) ans=1;
    }
    if(ans==0) printf("NO\n");
    else printf("YES\n");
}
