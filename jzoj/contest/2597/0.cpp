#define DEBUG
#include <cstdio>
#define MAXN 10
#define MAXK 10

using namespace std;

struct Official {
  int a, b;
};

int min(int a, int b) {
  return a<b ? a : b;
}

double max(double a, double b) {
  return a>b ? a : b;
}

double solveByHoney(int o, int a, int n, int *honey, const Official *official, double p, int tot) {
  static bool book[MAXN+1];
  if (tot*2>n) {
    return p;
  }
  if (o<=n) {
    double ret=0;
    book[o] = true;
    ret += solveByHoney(o+1, a, n, honey, official, p*honey[o]/100, tot+1);
    book[o] = false;
    ret += solveByHoney(o+1, a, n, honey, official, p*(100-honey[o])/100, tot);
    return ret;
  } else {
    if (tot*2>n) {
      return p;
    } else {
      int sum=0;
      for (int i=1; i<=n; i++) {
	if (!book[i]) {
	  sum += official[i].a;
	}
      }
      return a*p/(sum+a);
    }
  }
}

double solve(int o, int k, int a, int n, const Official *official) {
  static int honey[MAXN+1];
  double ret=0;
  if (o<=n) {
    for (int i=0; i<=k; i++) {
      honey[o] = min(official[o].b+i*10, 100);
      ret = max(ret, solve(o+1, k-i, a, n, official));
    }
  } else {
    ret = solveByHoney(1, a, n, honey, official, 1, 0);
  }
  return ret;
}

int main() {
#ifdef DEBUG
  freopen("0.in", "r", stdin);
  freopen("0.out", "w", stdout);
#endif

  static Official official[MAXN+1];
  int n, k, a;
  scanf("%d %d %d", &n, &k, &a);
  for (int i=1; i<=n; i++) {
    scanf("%d %d", &official[i].a, &official[i].b);
  }

  printf("%.6lf", solve(1, k, a, n, official));

  fcloseall();
  return 0;
}
