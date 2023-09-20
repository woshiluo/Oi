#include <cstdio>
#include <cstring>
using namespace std;

int n,alen;
char a[110];

int main(){
    scanf("%d",&n);
    scanf("%s",a);
    alen=strlen(a);
    for(int i=0;i<alen;i++) printf("%c",a[i]+n>'z'?a[i]+n-'z'+'a'-1:a[i]+n);
}
