#define DEBUG
#include <cstdio>

using namespace std;

long long min(long long a, long long b) {
  return a<b ? a : b;
}

long long max(long long a, long long b) {
  return a>b ? a : b;
}

int main() {
#ifdef DEBUG
  freopen("0.in", "r", stdin);
  freopen("0.out", "w", stdout);
#endif

  int k, a, b;
  scanf("%d %d %d", &k, &a, &b);
  long long ans=0;
  if (k%2) {
    if (a<=k && k<=b) {
      ans++;
    }
    k*=2;
  }
  for (long long x=1; x*k<=b; x*=2) {
    long long l=x*k, r=x*k+2*x-1;
    if (l<=b && r>=a) {
      ans += min(b, r)-max(a, l)+1;
    }
  }
  printf("%lld", ans);

  fcloseall();
  return 0;
}
