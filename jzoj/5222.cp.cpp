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
  SegmentTree *left, *right;
  int l, r, v, flag;

  SegmentTree(int l, int r) {
    this->l = l, this->r = r, this->flag = 0, this->v = INF;
  }

  int getFlag() {
    return this ? flag : 0;
  }

  int getV() {
    return this ? v : INF;
  }

  void merge() {
    flag = left->getFlag() + right->getFlag();
    v = min(left->getV(), right->getV());
  }

  void set(int t, int tv=0) {
    if (l==r) {
      flag++;
      v = min(v, tv);
    } else {
      int mid=(l+r)/2;
      if (t<=mid) {
	if (!left) {
	  left = new SegmentTree(1, mid);
	}
	left->set(t, tv);
      } else {
	if (!right) {
	  right = new SegmentTree(mid+1, r);
	}
	right->set(t, tv);
      }
      merge();
    }
  }

  int getMinValue(int tl, int tr) {
    if (l==tl && r==tr) {
      return v;
    } else {
      int mid=(l+r)/2, ret=INF;
      if (tr>=l && tl<=mid && left) {
	ret = min(ret, left->getMinValue(max(tl, l), min(tr, mid)));
      }
      if (tr>mid && tl<=r && right) {
	ret = min(ret, right->getMinValue(max(tl, mid+1), min(tr, r)));
      }
      return ret;
    }
  }

  int getTimes(int tl, int tr) {
    if (l==tl && r==tr) {
      return flag;
    } else {
      int mid=(l+r)/2, ret=0;
      if (tr>=l && tl<=mid && left) {
	ret += left->getTimes(max(tl, l), min(tr, mid));
      }
      if (tr>mid && tl<=r && right) {
	ret += right->getTimes(max(tl, mid+1), min(tr, r));
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

void initSoldier(int n, Soldier a[]) {
  SegmentTree *sgt = new SegmentTree(0, MAXA);
  for (int i=n; i>0; i--) {
    sgt->set(a[i].iq);
    a[i].value = sgt->getTimes(0, a[i].iq-1);
  }
}

void makeTime(int n, int m, Ques q[], Soldier a[]) {
  for (int i=1; i<=m; i++) {
    q[i].time = i;
  }
  sort(q+1, q+m+1, Ques::cmp);
  q[m+1].pos = n+1;
  q[0].pos = 1, q[0].time = m+1;

  SegmentTree *sgt = new SegmentTree(0, MAXA);
  for (int i=0; i<=m; i++) {
    sgt->set(a[q[i].pos].iq, q[i].time);
    for (int j=q[i].pos; j<q[i+1].pos;  j++) {
      a[j].time = sgt->getMinValue(a[j].iq, MAXA);
    }
  }
  sort(a+1, a+n+1, Soldier::cmp);
}

int main() {
#ifdef DEBUG
  freopen("5222.in", "r", stdin);
  freopen("5222.cp.out", "w", stdout);
#endif

  static Soldier a[MAXN+1];
  static Ques q[MAXM+2];
  int n, m;
  scanf("%d %d", &n, &m);

  for (int i=1; i<=n; i++) {
    scanf("%d", &a[i].iq);
  }
  initSoldier(n, a);
#ifdef DEBUG
  for (int i=1; i<=n; i++) {
    printf("%d\n", a[i].value);
  }
#endif

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
