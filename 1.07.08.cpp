#include <cstdio>
#include <cstring>
using namespace std;

char a[110],b,c;
int alen;

int main(){
    scanf("%s",a);
    alen=strlen(a);
    scanf(" %c %c",&b,&c);
    for(int i=0;i<alen;i++){
        if(a[i]==b) a[i]=c;
    }
    printf("%s",a);
}
