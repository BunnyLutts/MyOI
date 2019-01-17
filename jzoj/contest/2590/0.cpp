#define DEBUG
#include <cstdio>
#include <algorithm>
#define MAXN 100000
#define MAXK 20

using namespace std;

int main() {
#ifdef DEBUG
  freopen("0.in", "r", stdin);
  freopen("0.out", "w", stdout);
#endif

  static int a[MAXN+1], b[MAXN+1];
  int n;
  scanf("%d", &n);
  for (int i=1; i<=n; i++) {
    scanf("%d", a+i);
  }

  for (int i=0; i<=MAXK; i++) {
    int sum=0;
    for (int j=1; j<=n; j++) {
      sum += (a[j]>>i)&1;
    }
    for (int j=1; j<=sum; j++) {
      b[j] |= 1<<i;
    }
  }

  unsigned long long ans=0;
  for (int i=1; i<=n; i++) {
    ans += (unsigned long long)b[i]*b[i];
  }
  printf("%llu", ans);

  fcloseall();
  return 0;
}
