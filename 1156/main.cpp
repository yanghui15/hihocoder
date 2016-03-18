#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>

#define pb(a) push_back(a)

using namespace std;

const int maxn = 1e5 + 10;
vector<int>edge[maxn],que[maxn];

struct SegNode{
	int left , right;
	int value , sum;
	int lvalue, rvalue;
	int mid(){
		return (left + right) / 2;
	}
};
SegNode tree[maxn * 4];
int in[maxn] , out[maxn];
int cnt = 0;

void dfs(int root , int pre){
	in[root] = cnt ++;
	for(int i = 0 ; i < edge[root].size() ; i ++){
		int v = edge[root][i];
		if(v == pre) continue;
		dfs(v , root);
	}
	out[root] = cnt;
}

void pushup(int idx){
	tree[idx].sum = tree[idx << 1].sum + tree[idx << 1 | 1].sum;
	if(tree[idx << 1].rvalue == tree[idx << 1 | 1].lvalue)
		tree[idx].sum --;
}

void build(int left , int right , int idx){
	tree[idx].left = left;
	tree[idx].right = right;
	tree[idx].value = 0;
	tree[idx].lvalue = 0;
	tree[idx].rvalue = 0;
	tree[idx].sum = 1;
	if(left == right)
		return;
	int mid = (left + right ) / 2;
	build(left , mid , idx << 1);
	build(mid + 1 , right , idx << 1 | 1);
	pushup(idx);
}

void update(int x , int idx , int y){
	if(x == tree[idx].left){
		tree[idx].value = y;
		tree[idx].lvalue = tree[idx].rvalue = y;
		return;
	}
	int mid = tree[idx].mid();
	if(x <= mid)
		update(x , idx << 1 , y);
	else
		update(x , idx << 1 | 1 , y);
	pushup(idx);
}

void init(int n){
	for(int i = 1 ; i <= n ; i ++)
		edge[i].clear();
}

void solve(){
	int n , q , x , y , opt;
	scanf("%d",&n);
	init(n);
	for(int i = 1 ; i < n ; i ++){
		scanf("%d %d",&x , &y);
		edge[x].pb(y);
		edge[y].pb(x);
	}
	cnt = 1;
	dfs(1 , -1);
	for(int i = 1; i <= n ; i ++)
		printf("%d ",in[i]);
	printf("\n");
	for(int i = 1 ; i <= n ; i ++)
		printf("%d " , out[i]);
	printf("\n");
	scanf("%d",&q);
	build(1 , n , 1);
	for(int i = 0 ; i < q ; i ++){
		scanf("%d",&opt);
		if(opt == 1){
			printf("%d\n",tree[1].sum);
		}else{
			scanf("%d %d",&x , &y);
			update(in[x] , 1 , y);
		}
	}
}

void run(){
	int T ;
	scanf("%d",&T);
	for(int i = 0 ; i < T ; i ++)
		solve();
}

int main(){
	run();
	return 0;
}
