#include <cstdio>
#include <algorithm>
#define INF 0x7ffffff
#define MAXN 100000
#define MAXM 100000

using namespace std;

class Matrix{
public:
  int arr[2][2], n, m; 

  void init(int n, int m) {
    this->n = n;
    this->m = m;
  }

  static Matrix* add(const Matrix *a, const Matrix *b) {
    if (a->m!=b->n) {
      throw -2;
    }
    Matrix *temp = new Matrix;
    temp->init(a->n, b->m);
    for (int i=0; i<a->n; i++) {
      for (int j=0; j<b->m; j++) {
	temp->arr[i][j] = 0;
	for (int k=0; k<a->m; k++) {
	  temp->arr[i][j] = max(temp->arr[i][j], temp->arr[i][k]+b->arr[k][j]);
	}
      }
    }
    return temp;
  }
};

class SegmentTree {
public:
  Matrix *value[4*MAXN+1];

  void set(int o, int l, int r, int t, int v[2]) {
    value[o]->init(2, 2);
    if (l==r) {
      value[o]->arr[0][0] = v[0];
      value[o]->arr[0][1] = v[1];
      value[o]->arr[1][0] = 0;
      value[o]->arr[1][1] = -INF;
    } else {
      int mid=(l+r)/2;
      if (t<=mid) {
	set(o*2, l, mid, t, v);
      } else {
	set(o*2+1, mid+1, r, t, v);
      }
      value[o] = Matrix::add(value[o*2], value[o*2+1]);
    }
  }

  Matrix* get(int o, int l, int r, int tl, int tr) {
    if (l==tl && r==tr) {
      return &value[o];
    } else {
      int mid=(l+r)/2;
      if (tl<=mid && tr>=l) {
      }
    }
  }
};

class Tree {
public:
  int n, m, ind[MAXN+1], to[2*MAXN-1], next[2*MAXN], p[MAXN*2], size[MAXN+1], dfn[MAXN+1], g[MAXN+1][2], f[MAXN+1][2];
  SegmentTree sgt;

  void addSide(int u, int v) {
    m++;
    to[m] = v;
    next[m] = ind[u];
    ind[u] = m;
    dfn[0] = size[0] = 0;
  }

  void initSize(int o, int fa) {
    size[o] = 1;
    for (int i=ind[o]; i; i=next[i]) {
      if (to[i]!=fa) {
	initSize(to[i], o);
	size[o] += size[to[i]];
      }
    }
  }

  void initDfn(int o, int fa) {
    g[o][0] = 0;
    g[o][1] = p[o];
    dfn[o] = ++dfn[0];
    int max_way=0;
    for (int i=ind[o]; i; i=next[i]) {
      if (to[i]!=fa) {
	if (size[to[i]]>size[max_way]) {
	  max_way = to[i];
	}
      }
    }
    if (max_way) {
      initDfn(max_way, o);
      for (int i=ind[o]; i; i=next[i]) {
	if (to[i]!=fa && i!=max_way) {
	  initDfn(to[i], o);
	  g[o][0] += max(g[to[i]][1], g[to[i]][0]);
	  g[o][1] += f[to[i]][0];
	}
      }
    }
    sgt.set(1, 1, n, dfn[o], g[o]);
  }

  void build() {
    initSize(1, 0);
    initDfn(1, 0);
  }
};

int main() {
  freopen("defense.in", "r", stdin);
  freopen("defense.out", "w", stdout);

  char temp[3];
  static Tree t;
  int m;
  scanf("%d %d %s", &t.n, &m, temp);
  for (int i=1; i<=t.n; i++) {
    scanf("%d", t.p+i);
  }
  for (int i=1; i<t.n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    t.addSide(u, v);
    t.addSide(v, u);
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
