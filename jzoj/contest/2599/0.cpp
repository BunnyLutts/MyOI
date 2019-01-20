#define DEBUG
#include <cstdio>
#include <cmath>
#define MAXN 100000

using namespace std;

int min(int a, int b) {
  return a<b ? a : b;
}

int max(int a, int b) {
  return a>b ? a : b;
}

long long addSqr(long long sqrsum, int sum, int size, int add) {
  return sqrsum+(long long)add*add*size+2LL*sum*add;
}

class SegmentTree {
public:
  int sum[MAXN*4+1], mark[MAXN*4+1];
  long long sqrsum[MAXN*4+1];

  void markDown(int o, int l, int r) {
    if (mark[o]) {
      sqrsum[o] = addSqr(sqrsum[o], sum[o], r-l+1, mark[o]);
      sum[o] += mark[o]*(r-l+1);
      if (l!=r) {
	mark[o*2]+=mark[o], mark[o*2+1]+=mark[o];
      }
      mark[o] = 0;
    }
  }

  void add(int o, int l, int r, int tl, int tr, int tv) {
    markDown(o, l, r);
    if (l==tl && r==tr) {
      mark[o] += tv;
      markDown(o, l, r);
    } else {
      int mid=(l+r)/2;
      if (tl<=mid && tr>=l) {
	add(o*2, l, mid, max(tl, l), min(tr, mid), tv);
      }
      if (tl<=r && tr>mid) {
	add(o*2+1, mid+1, r, max(tl, mid+1), min(tr, r), tv);
      }
      markDown(o*2, l, mid), markDown(o*2+1, mid+1, r);
      sum[o] = sum[o*2]+sum[o*2+1];
      sqrsum[o] = sqrsum[o*2]+sqrsum[o*2+1];
    }
  }

  void get(int o, int l, int r, int tl, int tr, int &retsum, long long &retsqrsum) {
    markDown(o, l, r);
    if (l==tl && r==tr) {
      retsum += sum[o];
      retsqrsum += sqrsum[o];
    } else {
      int mid=(l+r)/2;
      if (tl<=mid && tr>=l) {
	get(o*2, l, mid, max(tl, l), min(tr, mid), retsum, retsqrsum);
      }
      if (tl<=r && tr>mid) {
	get(o*2+1, mid+1, r, max(tl, mid+1), min(tr, r), retsum, retsqrsum);
      }
    }
  }
};

int main() {
#ifdef DEBUG
  freopen("0.in", "r", stdin);
  freopen("0.out", "w", stdout);
#endif

  static SegmentTree sgt;
  int n, q;
  scanf("%d %d", &n, &q);

  for (int i=1; i<=n; i++) {
    int a;
    scanf("%d", &a);
    sgt.add(1, 1, n, i, i, a);
  }

  for (int i=1; i<=q; i++) {
    int t, a, b, c, sum;
    long long sqrsum;
    scanf("%d", &t);
    switch (t) {
    case 0:{
      scanf("%d %d", &a, &b);
      sgt.add(1, 1, n, a, a, b);
      break;
    }
    case 1: {
      scanf("%d %d %d", &a, &b, &c);
      sgt.add(1, 1, n, a, b, c);
      break;
    }

    case 2: {
      scanf("%d %d", &a, &b);
      sum = sqrsum = 0;
      sgt.get(1, 1, n, a, b, sum, sqrsum);
      printf("%d\n", sum);
      break;
    }
    case 3: {
      scanf("%d %d", &a, &b);
      sum = sqrsum = 0;
      sgt.get(1, 1, n, a, b, sum, sqrsum);
      long double ave = (long double)sum/(b-a+1);
      printf("%.10LF\n", (sqrsum-2*ave*sum+(b-a+1)*ave*ave)/(b-a+1));
      break;
    }
    }
  }

  fcloseall();
  return 0;
}
