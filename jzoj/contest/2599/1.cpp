#define DEBUG
#include <cstdio>
#define MAXN 100000
#define MODS 1000000007

using namespace std;

void swap(int &a, int &b) {
  a=a^b, b=a^b, a=a^b;
}

long long qpower(long long a, int n) {
  long long ret=a, s=1;
  for (; n>1; n>>=1) {
    if (n&1) {
      s = s*ret%MODS;
    }
    ret = ret*ret%MODS;
  }
  return s*ret%MODS;
}

long long solve(int o, int n, int *s, int *l, int *r, long long p) {
  static int val[MAXN+1], map[MAXN+1];
  long long ret=0;
  if (o<=n) {
    for (int i=l[o]; i<=r[o]; i++) {
      val[o] = i, map[o] = o;
      ret = (ret+solve(o+1, n, s, l, r, p))%MODS;
    }
  } else {
    for (int i=1; i<n; i++) {
      for (int j=1; j<=i; j++) {
	if (val[j]>val[j+1]) {
	  swap(val[j], val[j+1]);
	  swap(map[j], map[j+1]);
	}
      }
    }
    for (int i=1; i<=n; i++) {
      ret = (ret+s[map[i]]*i%MODS)%MODS;
    }
    ret = ret*p%MODS;
  }
  return ret;
}

int main() {
  freopen("sort.in", "r", stdin);
  freopen("sort.out", "w", stdout);

  static int s[MAXN+1], l[MAXN+1], r[MAXN+1];
  int n;
  long long p=1;
  scanf("%d", &n);
  for (int i=1; i<=n; i++) {
    scanf("%d %d %d", s+i, l+i, r+i);
    p = (p*(r[i]-l[i]+1))%MODS;
  }

  printf("%lld", solve(1, n, s, l, r, qpower(p, MODS-2)));

  fcloseall();
  return 0;
}
