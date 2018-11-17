#include <cstdio>
#include <algorithm>
#define MAXN 50000
#define MAXSUML 499990000

using namespace std;

class Set {
public:
  int to[MAXN+2][2], ver;

  void update() {
    ver++;
  }

  void check(int o) {
    if (to[o][0]!=ver) {
      to[o][1] = o;
      to[o][0] = ver;
    }
  }

  int get(int o) {
    check(o);
    if (to[o][1]!=o) {
      to[o][1] = get(to[o][1]);
    }
    return to[o][1];
  }

  void merge(int x, int y) {
    check(x), check(y);
    to[get(x)][0] = ver;
    to[get(x)][1] = get(y);
  }
};

class Tree {
public:
  int m, ind[MAXN+1], to[MAXN*2-1], next[MAXN*2-1], len[MAXN*2-1], f[MAXN][2];
  
  void addSide(int x, int y, int z) {
    m++;
    to[m] = y;
    next[m] = ind[x];
    len[m] = z;
    ind[x] = m;
  }

  void build(int o, int fa, int limit) {
    static int a[MAXN+1];
    static Set prev, nex;
    f[o][0] = f[o][1] = 0;
    for (int i=ind[o]; i; i=next[i]) {
      if (to[i]!=fa) {
	build(to[i], o, limit);
      }
    }
    a[0] = 0;
    for (int i=ind[o]; i; i=next[i]) {
      if (to[i]!=fa) {
	a[++a[0]] = f[to[i]][1]+len[i];
	f[o][0] += f[to[i]][0];
      }
    }

    sort(a+1, a+a[0]+1);
    int temp=a[0]+1;
    for (int l=1, r=a[0], mid; l<=r; ) {
      mid = (l+r)/2;
      if (a[mid]>=limit) {
	r = mid-1;
	temp = mid;
      } else {
	l = mid+1;
      }
    }
    f[o][0] += a[0]-temp+1;
    a[0] = temp-1;

    prev.update(), nex.update();
    prev.merge(a[0]+1, a[0]);
    for (int i=nex.get(1); i<=a[0]; i=nex.get(i+1)) {
      temp = 0;
      for (int l=nex.get(i+1), r=prev.get(a[0]), mid; l<=r; ) {
	mid = prev.get((l+r)/2);
	if (mid>=l && a[i]+a[mid]>=limit) {
	  temp = mid;
	  r = prev.get(mid-1);
	} else {
	  l = nex.get(mid+1);
	}
      }
      if (temp) {
	f[o][0]++;
	prev.merge(i, i-1), prev.merge(temp, temp-1);
	nex.merge(i, i+1), nex.merge(temp, temp+1);
      }
    }
    f[o][1] = a[prev.get(a[0]+1)];
  }

  int getAns(int num) {
    int ret=0;
    for (int l=1, r=MAXSUML, mid; l<=r; ) {
      mid = (l+r)/2;
      build(1, 0, mid);
      if (f[1][0]>=num) {
	l = mid+1;
	ret = mid;
      } else {
	r = mid-1;
      }
    }
    return ret;
  }
};

int main() {
  freopen("track.in", "r", stdin);
  freopen("track.out", "w", stdout);

  static Tree tree;
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i=1; i<n; i++) {
    int u, v, l;
    scanf("%d %d %d", &u, &v, &l);
    tree.addSide(u, v, l);
    tree.addSide(v, u, l);
  }

  printf("%d", tree.getAns(m));

  fclose(stdin);
  fclose(stdout);
  return 0;
}
