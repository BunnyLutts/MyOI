#define DEBUG
#include <cstdio>
#define MODS 1000000007
#define MAXN 100000
#define MAXR 1000000000

using namespace std;

int min(int a, int b) {
  return a<b ? a : b;
}

int max(int a, int b) {
  return a>b ? a : b;
}

long long qpower(long long a, int n) {
  long long s=1;
  for (; n>1; n>>=1) {
    if (n&1) {
      s = s*a%MODS;
    }
    a = a*a%MODS;
  }
  return a*s%MODS;
}

const long long k2=qpower(2, MODS-2);

class ArithPro {
public:
  long long a, d;

  ArithPro() {
    a=d=0;
  }

  ArithPro(long long a, long long d) {
    this->a = a, this->d = d;
  }

  ArithPro kth(int k) {
    return ArithPro((a+d*k%MODS)%MODS, d);
  }

  long long sum(int n) {
    return (a+n*d%MODS+d)%MODS*n%MODS*k2%MODS;
  }
};

ArithPro operator+(ArithPro a, ArithPro b) {
  ArithPro ret;
  ret.a = (a.a+b.a)%MODS, ret.d = (a.d+b.d)%MODS;
  return ret;
}

class SegmentTree {
public:
  ArithPro val;
  int al, ar;
  SegmentTree *left, *right;

  SegmentTree(int l, int r) {
    al = l, ar = r;
    val=ArithPro();
    left=right=NULL;
  }

  void add(int l, int r, ArithPro v) {
    if (al==l && ar==r) {
      val = val+v;
    } else {
      int mid = (al+ar)/2;
      if (l<=mid && r>=al) {
	if (!left) {
	  left = new SegmentTree(al, mid);
	}
	left->add(max(al, l), min(mid, r), v);
      }
      if (l<=ar && r>mid) {
	if (!right) {
	  right = new SegmentTree(mid+1, ar);
	}
	right->add(max(mid+1, l), min(ar, r), v);
      }
      if (left) {
	val = val+left->val;
      }
      if (right) {
	val = val+right->val;
      }
    }
  }

  long long get(int l, int r) {
    if (al==l && ar==r) {
      return val.sum(r-l+1);
    } else {
      int mid=(al+ar)/2;
      long long ret = val.sum(r-l+1);
      if (l<=mid && r>=al && left) {
	ret = ret+left->get(max(al, l), min(mid, r));
      }
      if (l<=ar && r>mid && right) {
	ret = ret+right->get(max(mid+1, l), min(ar, r));
      }
      return ret;
    }
  }
};

int main() {
  freopen("sort.in", "r", stdin);
  freopen("sort.out", "w", stdout);

  static int s[MAXN+1], l[MAXN+1], r[MAXN+1];
  static long long f[MAXN+1];
  int n;
  scanf("%d", &n);
  for (int i=1; i<=n; i++) {
    scanf("%d %d %d", s+i, l+i, r+i);
  }

  SegmentTree *below=new SegmentTree(0, MAXR), *above=new SegmentTree(0, MAXR);
  for (int i=1; i<=n; i++) {
    f[i] = (f[i]+below->get(l[i], r[i])*qpower(r[i]-l[i]+1, MODS-2)%MODS)%MODS;
    below->add(l[i], r[i], ArithPro(0, qpower(r[i]-l[i]+1, MODS-2)));
    if (r[i]<MAXR) {
      below->add(r[i]+1, MAXR, ArithPro(1, 0));
    }
  }
  for (int i=n; i>=1; i--) {
    f[i] = (f[i]+above->get(l[i], r[i])*qpower(r[i]-l[i]+1, MODS-2)%MODS)%MODS;
    if (r[i]>l[i]) {
      above->add(l[i]+1, r[i], ArithPro(0, qpower(r[i]-l[i]+1, MODS-2)));
    }
    if (r[i]<MAXR){
      above->add(r[i]+1, MAXR, ArithPro(1, 0));
    }
  }

  long long ans=0;
  for (int i=1; i<=n; i++) {
    ans = (ans+s[i]*f[i]%MODS)%MODS;
  }
  printf("%lld", ans);

  fcloseall();
  return 0;
}
