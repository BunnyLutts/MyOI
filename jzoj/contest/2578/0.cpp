#define DEBUG
#include <cstdio>
#include <cmath>
#define MAXN 2000
#define MAXS 20000
#define EPS 1

using namespace std;

struct Circle {
  int t, x, y;
};

int sqr(int a) {
  return a*a;
}

double dis(const struct Circle *a, const struct Circle *b) {
  return sqrt(sqr(a->x-b->x)+sqr(a->y-b->y));
}

bool solve(struct Circle cir[], double v, int n, int k, int &x, int &y) {
  int f[MAXN+1][3];
  f[0][2] = 1;
  for (int i=1; i<=n; i++) {
    f[i][0] = 0, f[i][2]=1;
    for (int j=0; j<i; j++) {
      double temp=dis(&cir[i], &cir[j]);
      if (v*(cir[i].t-cir[j].t)>=temp) {
	if (f[i][0]<f[j][0]+1) {
	  f[i][0] = f[j][0]+1;
	  if (sqrt(f[j][1])/f[j][2]>temp/(cir[i].t-cir[j].t)) {
	    f[i][1] = f[j][1];
	    f[i][2] = f[j][2];
	  } else {
	    f[i][1] = sqr(cir[i].x-cir[j].x)+sqr(cir[i].y-cir[j].y);
	    f[i][2] = cir[i].t-cir[j].t;
	  }
	}
      }
    }
    if (f[i][0]>=k) {
      x = f[i][1];
      y = f[i][2];
      return true;
    }
  }
  return false;
}

void simpleRadict(int &a, int &b) {
  for (int i=2; i<=sqrt(b); i++) {
    for (; b%sqr(i)==0; b /= sqr(i)) {
      a *= i;
    }
  }
}

void simpleFract(int &a, int &b) {
  int n, m, r;
  for (n=a, m=b, r=a%b; r; n=m, m=r, r=n%m);
  a/=m, b/=m;
}

int main() {
#ifdef DEBUG
  freopen("0.in", "r", stdin);
  freopen("0.out", "w", stdout);
#endif

  int n, k;
  static struct Circle cir[MAXN+1];
  scanf("%d %d", &n, &k);
  for (int i=1; i<=n; i++) {
    scanf("%d %d %d", &cir[i].t, &cir[i].x, &cir[i].y);
  }

  int a, b, c;
  for (double l=EPS, r=MAXS, mid; l<=r; ) {
    mid = (l+r)/2;
    if (solve(cir, mid, n, k, b, c)) {
      a = 1;
      simpleRadict(a, b);
      simpleFract(a, c);
      r = mid-EPS;
    } else {
      l = mid+EPS;
    }
  }
  printf("%d %d %d", a, b, c);

  fclose(stdin);
  fclose(stdout);
  return 0;
}
