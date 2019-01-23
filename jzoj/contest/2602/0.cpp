#define DEBUG
#include <cstdio>

using namespace std;

unsigned long long min(unsigned long long a, unsigned long long b) {
  return a<b ? a : b;
}

unsigned long long max(unsigned long long a, unsigned long long b) {
  return a>b ? a : b;
}

int main() {
#ifdef DEBUG
  freopen("0.in", "r", stdin);
  freopen("0.out", "w", stdout);
#endif

  unsigned long long k, a, b;
  scanf("%llu %llu %llu", &k, &a, &b);
  unsigned long long ans=0;
  if (k==0) {
    printf("%llu", b-a+1);
    return 0;
  }
  if (k%2) {
    if (a<=k && k<=b) {
      ans++;
    }
    k*=2;
  }
  for (unsigned long long x=1; x*k<=b; x*=2L) {
    unsigned long long l=x*k, r=x*k+2*x-1L;
    if (l<=b && r>=a) {
      ans += min(b, r)-max(a, l)+1L;
    }
  }
  printf("%llu", ans);

  fcloseall();
  return 0;
}
