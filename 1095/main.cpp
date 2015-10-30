#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

const int maxn = 1e5 + 10;
int re[maxn];
int n , k;

bool solve(int T){
	int hi = 0;
	int ho = 0;
	long long sum = 0;
	for(int i = 1 ; i <= n ; i ++){
		sum += T;
		if(sum <= re[i]){
			hi ++;
			sum = 0;
		}else{
			ho ++;
			sum -= re[i];
		}
	}
	if(hi > ho)
		return false;
	else
		return true;
}

int run(){
	scanf("%d %d",&n,&k);
	for(int i = 1 ; i <= n ; i ++)
		scanf("%d",&re[i]);
	int left = 1 , right = k * 10;
	int mid = -1;
	while(left < right){
		mid = (left + right) / 2;
		bool ans = solve(mid);
//		printf("%d %d %d %d\n",left , right , mid , ans);
		if(ans)
			right = mid;
		else
			left = mid + 1;
	}
	printf("%d\n",left);
}

int main(){
	run();
	return 0;
}
