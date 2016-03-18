#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1000+10;
int result[maxn];
int data[maxn][maxn];

int run(){

	int n , k , temp;
	scanf("%d %d",&n , &k);
	for(int i = 0 ; i < n ; i ++){
		for(int j = 0 ; j <= k ; j ++){
			scanf("%d",&temp);
			data[i][temp] = j;
		}
	}
	result[0] = 0;
	for(int i = k ; i > 0 ; i --){
		int cnt = 0;
		int tar = i + 1;
		if(i == k)
			tar = 0;
		for(int j = 0 ; j < n ; j ++){
			if(data[j][result[tar]] > data[j][i]){
				cnt++;
			}
		}
		//printf("%d %d %d %d %d\n",i , tar , cnt , result[i] , result[tar]);
		if(cnt > n / 2){
			result[i] = i;
		}else{
			result[i] = result[tar];
		}
		//printf("%d %d %d %d %d\n",i , tar , cnt , result[i] , result[tar]);

	}
	if(result[1] == 0){
		printf("otaku\n");
	}else
		printf("%d\n",result[1]);
}

int main(){
	run();
	return 0;
}

