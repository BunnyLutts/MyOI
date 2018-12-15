#define DEBUG
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXA 1000000
#define MAXN 100000
#define MAXM 100000

using namespace std;

class SegmentTree {
public:
  int v[4*MAXN+1], a[4*MAXN+1];
  bool *flag;

  void set(int o, int l, int r, int t, int tv) {
    if (l==r) {
      v[o] = flag[tv];
      a[o] = tv;
    } else {
      int mid=(l+r)/2;
      if (t<=mid) {
	set(o*2, l, mid, t, tv);
      } else {
	set(o*2+1, mid+1, r, t, tv);
      }
      v[o] = v[o*2]+v[o*2+1];
      a[o] = max(a[o*2], a[o*2+1]);
    }
  }

  void mod(int o, int l, int r, int tl, int tr, int s) {
    if (l==r) {
      a[o] = a[o]%s;
      v[o] = flag[a[o]];
    } else {
      int mid=(l+r)/2;
      if (l==tl && r==tr) {
	if (a[o*2]>=s) {
	  mod(o*2, l, mid, l, mid, s);
	}
	if (a[o*2+1]>=s) {
	  mod(o*2+1, mid+1, r, mid+1, r, s);
	}
      } else {
	if (tr>=l && tl<=mid) {
	  mod(o*2, l, mid, max(l, tl), min(mid, tr), s);
	}
	if (tr>mid && tl<=r) {
	  mod(o*2+1, mid+1, r, max(mid+1, tl), min(r, tr), s);
	}
      }
      a[o] = max(a[o*2], a[o*2+1]);
      v[o] = v[o*2]+v[o*2+1];
    }
  }

  int get(int o, int l, int r, int tl, int tr) {
    if (l==tl && r==tr) {
      return v[o];
    } else {
      int mid=(l+r)/2, ret=0;
      if (tr>=l && tl<=mid) {
	ret += get(o*2, l, mid, max(l, tl), min(mid, tr));
      }
      if (tr>mid && tl<=r) {
	ret += get(o*2+1, mid+1, r, max(mid+1, tl), min(r, tr));
      }
      return ret;
    }
  }
};

void initFlag(int n, bool flag[]) {
  for (int i=1; i<=n; i++) {
    flag[i] = true;
  }
  for (int i=2; i<=n; i++) {
    if (flag[i]) {
      for (int j=2; i*j<=n; j++) {
	flag[i*j] = false;
      }
    }
  }
  flag[0] = flag[1] = flag[6] = true;
  for (int i=1; (1<<i)<=n; i++) {
    flag[1<<i] = true;
  }
}

int main() {
#ifdef DEBUG
  freopen("100045.in", "r", stdin);
  freopen("100045.out", "w", stdout);
#endif

  static bool flag[MAXA+1];
  initFlag(MAXA, flag);
  int n, m;
  static SegmentTree tree;
  tree.flag = flag;
  scanf("%d %d", &n, &m);
  for (int i=1; i<=n; i++) {
    int a;
    scanf("%d", &a);
    tree.set(1, 1, n, i, a);
  }

  for (int i=1; i<=m; i++) {
    int type;
    scanf("%d", &type);
    if (type==1) {
      int l, r;
      scanf("%d %d", &l, &r);
      printf("%d\n", tree.get(1, 1, n, l, r));
    } else if (type==2) {
      int l, r, s;
      scanf("%d %d %d", &l, &r, &s);
      tree.mod(1, 1, n, l, r, s);
    } else {
      int c, x;
      scanf("%d %d", &c, &x);
      tree.set(1, 1, n, c, x);
    }
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
