#define DEBUG
#include <cstdio>
#include <algorithm>
#define INF 0x7fffffff
#define MAXN 100000
#define MAXM 100000
#define MAXA 1000000000

using namespace std;

class SegmentTree {
public:
  int v[4*MAXN+1], flag[4*MAXN+1];

  SegmentTree() {
    for (int i=0; i<=4*MAXN; i++) {
      v[i] = INF, flag[i] = 0;
    }
  }

  void set(int o, int l, int r, int t, int tv=0) {
    if (l==t && r==t) {
      flag[o]++;
      v[o] = min(v[o], tv);
    } else {
      int mid=(l+r)/2;
      if (t<=mid) {
	set(o*2, l, mid, t, tv);
      } else {
	set(o*2+1, mid+1, r, t, tv);
      }
      flag[o] = flag[o*2]+flag[o*2+1];
      v[o] = min(v[o*2], v[o*2+1]);
    }
  }

  int getMinValue(int o, int l, int r, int tl, int tr) {
    if (l==tl && r==tr) {
      return v[o];
    } else {
      int mid=(l+r)/2, ret=INF;
      if (tr>=l && tl<=mid) {
	ret = min(ret, getMinValue(o*2, l, mid, max(tl, l), min(tr, mid)));
      }
      if (tr>mid && tl<=r) {
	ret = min(ret, getMinValue(o*2+1, mid+1, r, max(tl, mid+1), min(tr, r)));
      }
      return ret;
    }
  }

  int getTimes(int o, int l, int r, int tl, int tr) {
    if (l==tl && r==tr) {
      return flag[o];
    } else {
      int mid=(l+r)/2, ret=0;
      if (tr>=l && tl<=mid) {
	ret += getTimes(o*2, l, mid, max(l, tl), min(mid, tr));
      }
      if (tr>mid && tl<=r) {
	ret += getTimes(o*2+1, mid+1, r, max(mid+1, tl), min(r, tr));
      }
      return ret;
    }
  }
};

class Soldier {
public:
  int iq, time, value;

  static bool cmp(Soldier a, Soldier b) {
    return a.time<b.time;
  }
};

class Ques {
public:
  int time, pos;

  static bool cmp(Ques x, Ques y) {
    return x.pos<y.pos;
  }
};

bool cmpHash(int *a, int *b) {
  return *a<*b;
}

void initSoldier(int n, Soldier a[]) {
  static int *pool[MAXN+1];
  for (int i=1; i<=n; i++) {
    pool[i] = &a[i].iq;
  }
  sort(pool+1, pool+n+1, cmpHash);
  int temp = *pool[1];
  *pool[1] = 1;
  int p=1;
  for (int i=2; i<=n; i++) {
    if (*pool[i]!=temp) {
      temp = *pool[i];
      p++;
    }
    *pool[i] = p;
  }

  static SegmentTree sgt;
  for (int i=n; i>0; i--) {
    sgt.set(1, 1, n, a[i].iq, 0);
    if (a[i].iq>1) {
      a[i].value = sgt.getTimes(1, 1, n, 1, a[i].iq-1);
    }
  }
}

void makeTime(int n, int m, Ques q[], Soldier a[]) {
  for (int i=1; i<=m; i++) {
    q[i].time = i;
  }
  sort(q+1, q+m+1, Ques::cmp);
  q[m+1].pos = n+1;
  q[0].pos = 1, q[0].time = m+1;

  static SegmentTree sgt;
  for (int i=0; i<=m; i++) {
    sgt.set(1, 1, n, a[q[i].pos].iq, q[i].time);
    for (int j=q[i].pos; j<q[i+1].pos;  j++) {
      a[j].time = sgt.getMinValue(1, 1, n, a[j].iq, n);
    }
  }
  sort(a+1, a+n+1, Soldier::cmp);
}

int main() {
#ifdef DEBUG
  freopen("5222.in", "r", stdin);
  freopen("5222.out", "w", stdout);
#endif

  static Soldier a[MAXN+1];
  static Ques q[MAXM+2];
  int n, m;
  scanf("%d %d", &n, &m);

  for (int i=1; i<=n; i++) {
    scanf("%d", &a[i].iq);
  }
  initSoldier(n, a);

  for (int i=1; i<=m; i++) {
    scanf("%d", &q[i].pos);
  }
  makeTime(n, m, q, a);

  long long ans=0;
  for (int i=1; i<=n; i++) {
    ans += a[i].value;
  }
  printf("%lld\n", ans);
  for (int i=1, j=1; i<=m; i++) {
    for (; j<=n && a[j].time<=i; j++) {
      ans -= a[j].value;
    }
    printf("%lld\n", ans);
  }
  fclose(stdin);
  fclose(stdout);
}
