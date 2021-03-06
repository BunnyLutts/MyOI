#define DEBUG
#include <cstdio>
#include <cassert>
#include <algorithm>
#define INF 0x7ffffff
#define MAXN 10000
#define MAXM 50000
#define MAXK 10

using namespace std;

class Heap {
public:
  int v[MAXN*MAXK*2+1][3], size, map[MAXN+1][MAXK+1];

  bool cmp(int a, int b) {
    if (v[a][0]==v[b][0]) {
      return v[a][2]<=v[b][2];
    }
    return v[a][0]<v[b][0];
  }

  void swap(int a, int b) {
    int temp;
    temp=v[a][0], v[a][0]=v[b][0], v[b][0]=temp;
    temp=v[a][1], v[a][1]=v[b][1], v[b][1]=temp;
    temp=v[a][2], v[a][2]=v[b][2], v[b][2]=temp;
    map[v[a][1]][v[a][2]] = a;
    map[v[b][1]][v[b][2]] = b;
  }

  void up(int o) {
    if (o>1 && cmp(o, o/2)) {
      swap(o, o/2);
      up(o/2);
    }
  }

  void down(int o) {
    if ((o*2==size || (o*2<size && cmp(o*2, o*2+1))) && cmp(o*2, o)) {
      swap(o*2, o);
      down(o*2);
    }
    if (o*2<size && cmp(o*2+1, o*2) && cmp(o*2+1, o)) {
      swap(o*2+1, o);
      down(o*2+1);
    }
  }

  void push(int x, int y, int f) {
    size++;
    v[size][0]=f, v[size][1]=x, v[size][2] = y;
    map[x][y] = size;
    up(size);
  }

  void pop(int o=1) {
    map[v[o][1]][v[o][2]] = 0;
    if (o<size) {
      swap(o, size);
    }
    size--;
    if (size) {
      down(o);
    }
  }
};

int n, m, k, s, t, ind[MAXN+1], to[2*MAXM+1], link[2*MAXM+1], val[2*MAXM+1], f[MAXN+1][MAXK+1];
Heap q;

void addSide(int u, int v, int l) {
  m++;
  to[m] = v;
  val[m] = l;
  link[m] = ind[u];
  ind[u] = m;
}

int main() {
  #ifdef DEBUG
  freopen("5172.in", "r", stdin);
  freopen("5172.out", "w", stdout);
  #endif

  int m;
  scanf("%d %d %d %d %d", &n, &m, &k, &s, &t);
  for (int i=1; i<=m; i++) {
    int u, v, l;
    scanf("%d %d %d", &u, &v, &l);
    addSide(u, v, l);
    addSide(v, u, l);
  }

  for (int i=1; i<=n; i++) {
    for (int j=0; j<=k; j++) {
      f[i][j] = INF;
    }
  }
  int ans=INF;
  f[s][0] = 0;
  q.push(s, 0, 0);
  for (int cnt=1; q.size; cnt++) {
    int x=q.v[1][1], y=q.v[1][2], z=q.v[1][0];
    q.pop();
    if (f[x][y]>ans) {
      continue;
    }
    for (int i=ind[x]; i; i=link[i]) {
      if (f[to[i]][y]>z+val[i] && z+val[i]<=ans) {
	f[to[i]][y] = z+val[i];
	if (to[i]==t) {
	  ans = min(ans, f[to[i]][y]);
	}
	if (q.map[to[i]][y]) {
	  q.pop(q.map[to[i]][y]);
	}
	q.push(to[i], y, f[to[i]][y]);
      }
      if (y+1<=k && f[to[i]][y+1]>z) {
	f[to[i]][y+1] = z;
	if (to[i]==t) {
	  ans = min(ans, f[to[i]][y+1]);
	}
	if (q.map[to[i]][y+1]) {
	  q.pop(q.map[to[i]][y+1]);
	}
	q.push(to[i], y+1, f[to[i]][y+1]);
      }
    }
  }

  printf("%d", ans);

  fclose(stdin);
  fclose(stdout);
}
