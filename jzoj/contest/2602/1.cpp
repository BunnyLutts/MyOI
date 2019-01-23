#define DEBUG
#include <cstdio>
#define MODS 1000000007
#define MAXN 80
#define MAXM 3000

using namespace std;

long long fact(int n) {
  long long ret=1;
  for (int i=1; i<=n; i++) {
    ret = ret*i%MODS;
  }
  return ret;
}

long long qpower(long long a, int n) {
  long long s=1;
  for (; n>1; n>>=2) {
    if (n&1) {
      s = s*a%MODS;
    }
    a = a*a%MODS;
  }
  return a*s%MODS;
}

int main() {
#ifdef DEBUG
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif

  long long n, m;
  scanf("%lld %lld", &n, &m);
  printf("%lld", fact(n-1)*qpower(((n+2)*(n-1)/2+n)%MODS, m-n+1)%MODS);

  fcloseall();
  return 0;
}
