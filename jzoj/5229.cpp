#define DEBUG
#include <cstdio>
#include <algorithm>
#define MAXN 100000
#define MAXK 100000

using namespace std;

class Candy {
public:
  int x, y, color, id;


  static bool cmpX(Candy a, Candy b) {
    return a.x<b.x;
  }

  static bool cmpY(Candy a, Candy b) {
    return a.y<b.y;
  }
};

class TreeArray {
public:
  int a[MAXN+1], n, v[MAXN+1];

  void init(int n) {
    v[0]++;
    this->n = n;
  }

  int lowbit(int k) {
    return (-k)&k;
  }

  void set(int o, int t) {
    for (int i=o; i<=n; i+=lowbit(i)) {
      if (v[i]!=v[0]) {
	a[i] = 0;
	v[i] = v[0];
      }
      a[i] += t;
    }
  }

  int get(int o) {
    int ret=0;
    for (int i=o; i>0; i-=lowbit(i)) {
      if (v[i]!=v[0]) {
	a[i] = 0;
	v[i] = i;
      }
      ret += a[i];
    }
    return ret;
  }
};

class HashEle {
public:
  int v, *pos;

  void init(int *x) {
    pos = x;
    v = *x;
  }

  static bool cmp(HashEle a, HashEle b) {
    return a.v<b.v;
  }
};

class List {
public:
  int n[MAXN+2], p[MAXN+2];

  void ins(int last, int o) {
    p[o] = last;
    n[last] = o;
    n[o] = 0;
  }

  void pop(int o) {
    if (n[o]) {
      p[n[o]] = p[o];
    }
    if (p[o]) {
      n[p[o]] = n[o];
    }
  }
};

void hashing(Candy candy[], int n, int &xn, int &yn) {
  static HashEle x[MAXN+1], y[MAXN+1];
  for (int i=1; i<=n; i++) {
    x[i].init(&candy[i].x);
  }
  sort(x+1, x+n+1, HashEle::cmp);
  int p = *x[1].pos = 1;
  for (int i=2; i<=n; i++) {
    if (x[i].v!=x[i-1].v) {
      p++;
    }
    *x[i].pos = p;
  }
  xn = p;
  for (int i=1; i<=n; i++) {
    y[i].init(&candy[i].y);
  }
  sort(y+1, y+n+1, HashEle::cmp);
  p = *y[1].pos = 1;
  for (int i=2; i<=n; i++) {
    if (y[i].v!=y[i-1].v) {
      p++;
    }
    *y[i].pos = p;
  }
  yn = p;
}

int solve(Candy candy[], int n, int k) {
  int xn, yn;
  hashing(candy, n, xn, yn);

  static List list;
  static int last[MAXK+1];
  sort(candy+1, candy+n+1, Candy::cmpX);
  for (int i=1; i<=k; i++) {
    last[i] = 0;
  }
  for (int i=1; i<=n; i++) {
    list.ins(last[candy[i].color], candy[i].id);
    last[candy[i].color] = candy[i].id;
  }
  
  static int map[MAXN+1], ans[MAXK+1];
  static TreeArray tree;
  sort(candy+1, candy+n+1, Candy::cmpY);
  tree.init(xn);
  for (int i=1; i<=n; i++) {
    map[candy[i].id] = i;
    tree.set(candy[i].x, 1);
  }
  for (int i=1; i<=k; i++) {
    ans[k] = tree.get(xn)-tree.get(candy[map[last[i]]].x);
    for (int j=last[i]; j; j=list.p[j]) {
      int l=candy[map[list.p[j]]].x+1, r=candy[map[j]].x-1;
      if (r>=l) {
	ans[k] = max(ans[k], tree.get(r)-tree.get(l-1));
      }
    }
  }
  for (int i=1, p=1; i<=yn; i++) {
    for (; candy[p].y<i; p++) {
      tree.set(candy[p].x, -1);
      int l=candy[map[list.p[candy[p].id]]].x+1, r=candy[map[list.n[candy[p].id]]].x-1;
      if (r>=l) {
	ans[candy[p].color] = max(ans[candy[p].color], tree.get(r)-tree.get(l-1));
      } else if (!list.n[candy[p].id]) {
	ans[candy[p].color] = max(ans[candy[p].color], tree.get(xn)-tree.get(l-1));
      }
      list.pop(candy[p].id);
    }
  }

  ans[0] = 0;
  for (int i=1; i<=k; i++) {
    ans[0] = max(ans[0], ans[i]);
  }

  return ans[0];
}

int main() {
#ifdef DEBUG
  freopen("5229.in", "r", stdin);
  freopen("5229.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  for (int ti=1; ti<=t; ti++) {
    int n, k;
    static Candy candy[MAXN+1];
    scanf("%d %d", &n, &k);
    for (int i=1; i<=n; i++) {
      scanf("%d %d %d", &candy[i].x, &candy[i].y, &candy[i].color);
      candy[i].id = i;
    }
    int ans=solve(candy, n, k);
    for (int i=1; i<=n; i++){
      candy[i].y = -candy[i].y;
    }
    ans = max(ans, solve(candy, n, k));
    printf("%d\n", ans);
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
