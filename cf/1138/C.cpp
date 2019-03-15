#include <cstdio> 
#include <algorithm> 

const int N = 1100;

int n, m, end;
int map[N][N], map_i[N][N], map_j[N][N], max_i[N], max_j[N], temp[N] ;

int main(){
	scanf("%d%d", &n, &m);
    for(int i = 1 ;i <= n ; ++i){
        for(int j = 1 ;j <= m ; ++j){
			scanf("%d", &map[i][j]);
            map_i[i][j] = map_j[i][j] = map[i][j];
		}
	}
    for(int i = 1 ;i <= n ; ++i){
        for(int j = 1 ;j <= m ; ++j){
            temp[j] = map[i][j]; 
		}
        std::sort(temp + 1, temp + 1 + m);
        end = std::unique(temp + 1, temp + 1 + m) - temp - 1;
        for(int j = 1 ;j <= m ; ++j){
            map_i[i][j] = std::lower_bound(temp + 1, temp + 1 + end, map[i][j]) - temp;
            max_i[i] = std::max(max_i[i], map_i[i][j]);
        }
    }
    for(int j = 1 ;j <= m ; ++j){
        for(int i = 1 ;i <= n ; ++i){
            temp[i] = map[i][j];
		}
        std::sort(temp + 1, temp + 1 + n);
        end = std::unique(temp + 1, temp + 1 + n) - temp - 1;
        for(int i = 1 ;i <= n ; ++i){
            map_j[i][j] = std::lower_bound(temp + 1, temp + 1 + end, map[i][j]) - temp;
            max_j[j] = std::max(max_j[j], map_j[i][j]);
        }
    }
    for(int i = 1 ;i <= n ; ++i){
        for(int j = 1 ;j <= m ; ++j){
            if(map_i[i][j] > map_j[i][j])
                printf("%d ", std::max(max_j[j] + map_i[i][j] - map_j[i][j], max_i[i]));
            else
                printf("%d ", std::max(max_i[i] + map_j[i][j] - map_i[i][j], max_j[j]));
		}
		printf("\n");
    }
    return 0;
}
