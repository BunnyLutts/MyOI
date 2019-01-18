#define DEBUG
#include <cstdio>
#define INF 0x7ffffff
#define MAXN 3000

int min(int a, int b) {
  return a<b ? a : b;
}

int abs(int a) {
  return a>0 ? a : -a;
}

int solve(int o, int n, int *a, int sum, int ill) {
  static bool book[MAXN+1];
  static int vil[MAXN+1];
  vil[0] = 1;
  if (o<=n) {
    int ret=INF;
    for (int i=1; i<=n; i++) {
      if (!book[i]) {
	bool flag=true;
	for (int j=i+1; j<vil[o-1] && flag; j++) {
	  flag = book[j];
	}
	if (flag) {
	  vil[o] =i;
	  book[i] = true;
	  ret=min(ret, solve(o+1, n, a, sum+ill*(abs(vil[o]-vil[o-1])+1)-a[i], ill-a[i]));
	  book[i] = false;
	}
      }
    }
    return ret;
  } else {
    return sum;
  }
}

int main() {
#ifdef DEBUG
  freopen("2.in", "r", stdin);
  freopen("2.out", "w", stdout);
#endif

  static int a[MAXN+1];
  int n, t=0;
  scanf("%d", &n);
  for (int i=1; i<=n; i++) {
    scanf("%d", a+i);
    t+=a[i];
  }

  printf("%d", solve(1, n, a, 0, t));

  fcloseall();
  return 0;
}
