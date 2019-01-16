#define DEBUG
#include <cstdio>
#include <cmath>
#define MAXN 2000
#define MAXS 20000

using namespace std;

struct Circle {
  int t, x, y;
};

struct V {
  double v;
  int from, to;
};

int sqr(int a) {
  return a*a;
}

inline int read(int &a) {
  a=0;
  char c;
  for (c=getchar(); c<'0' || c>'9'; c=getchar());
  for (; c>='0' && c<='9'; c=getchar()) {
    a = a*10+c-'0';
  }
  return a;
}

double dis(const struct Circle *a, const struct Circle *b) {
  return sqrt(sqr(a->x-b->x)+sqr(a->y-b->y));
}

void sort(V *a, int l, int r) {
  int i=l, j=r;
  double mid = a[(l+r)/2].v;
  V temp;
  for (; i<=j; ) {
    for (; a[j].v>mid; j--);
    for (; a[i].v<mid; i++);
    if (i<=j) {
      temp=a[i], a[i]=a[j], a[j]=temp;
      i++, j--;
    }
  }
  if (i<r) {
    sort(a, i, r);
  }
  if (j>l) {
    sort(a, l, j);
  }
}

bool solve(struct Circle cir[], double v, int n, int k) {
  int f[MAXN+1];
  for (int i=1; i<=n; i++) {
    f[i] = 0;
    for (int j=0; j<i; j++) {
      double temp=dis(&cir[i], &cir[j]);
      if (v*(cir[i].t-cir[j].t)>=temp) {
	if (f[i]<f[j]+1) {
	  f[i] = f[j]+1;
	}
      }
    }
    if (f[i]>=k) {
      return true;
    }
  }
  return false;
}

void simplizeRadict(int &a, int &b) {
  for (int i=2; i<=sqrt(b); i++) {
    for (; b%sqr(i)==0; b /= sqr(i)) {
      a *= i;
    }
  }
}

void simplizeFract(int &a, int &b) {
  int n, m, r;
  for (n=a, m=b, r=a%b; r; n=m, m=r, r=n%m);
  a/=m, b/=m;
}

int main() {
#ifdef DEBUG
  freopen("4783.in", "r", stdin);
  freopen("4783.out", "w", stdout);
#endif

  int n, k, vsize=0;
  static struct Circle cir[MAXN+1];
  static V v[MAXN*MAXN+1];
  read(n), read(k);
  for (int i=1; i<=n; i++) {
    read(cir[i].t), read(cir[i].x), read(cir[i].y);
    for (int j=1; j<i; j++) {
      v[++vsize].v = dis(&cir[i], &cir[j])/(cir[i].t-cir[j].t);
      v[vsize].from=j, v[vsize].to = i;
    }
  }

  sort(v, 1, vsize);

  int ans;
  for (int l=1, r=vsize, mid; l<=r; ) {
    mid = (l+r)/2;
    if (solve(cir, v[mid].v, n, k)) {
      ans = mid;
      r = mid-1;
    } else {
      l = mid+1;
    }
  }

  int a, b, c;
  a = 1;
  b = sqr(cir[v[ans].to].x-cir[v[ans].from].x)+sqr(cir[v[ans].to].y-cir[v[ans].from].y);
  c = cir[v[ans].to].t-cir[v[ans].from].t;
  simplizeRadict(a, b);
  simplizeFract(a, c);
  printf("%d %d %d", a, b, c);

  fclose(stdin);
  fclose(stdout);
  return 0;
}
