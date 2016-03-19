#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int maxn = 100000 + 100;

struct Query{
	int left , right;
	int idx;
};

Query q[maxn];
Query node[maxn];
int ans[maxn];
int tree[maxn];

bool cmp(const Query &a , const Query &b){
	if(a.left == b.left)
		return b.right < a.right;
	else
		return a.left > b.left;
}

int lowbit(int x){
	return x & (-x);
}

void add(int idx , int val){
	while(idx < maxn){
		tree[idx] += val;
		idx += lowbit(idx);
	}
}

int sum(int idx){
	int ans = 0;
	while(idx > 0){
		ans += tree[idx];
		idx -= lowbit(idx);
	}
	return ans;
}

int sum(int left , int right){
	return sum(right) - sum(left - 1);
}

void run(){
	int n , que;
	scanf("%d %d",&n , &que);
	int ll , rr;
	for(int i = 0 ; i < n - 1; i ++){
		scanf("%d %d",&ll , &rr);
		node[i].left = min(ll , rr);
		node[i].right = max(ll , rr);
	}
	sort(node , node + n - 1 , cmp);
	for(int i = 0 ; i < que ; i ++){
		scanf("%d %d",&q[i].left , &q[i].right);
		q[i].idx = i;
	}
	sort(q , q + que , cmp);
	int idx = 0;
	for(int i = 0 ; i < que ; i ++){
		while(idx < n-1 && node[idx].left >= q[i].left){
			add(node[idx++].right , 1);
		}
		int temp = sum(q[i].left , q[i].right);
		ans[q[i].idx] = q[i].right - q[i].left + 1 - temp;
	}
	for(int i = 0 ; i < que ; i ++){
		printf("%d\n",ans[i]);
	}

}

int main(){
	run();
	return 0;
}