#define DEBUG
#include <cstdio>

using namespace std;

long long calc(long long x) {
  if (x<1) {
    return 0;
  }
  long long ans=0;
  for (int i=0; i<9; i++) {
    int temp = x/(i+1)-1;
    if (temp>=i) {
      ans += (temp-i)/9+1;
    }
  }
  return ans;
}

int main() {
#ifdef DEBUG
  freopen("0.in", "r", stdin);
  freopen("0.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  for (int i=1; i<=t; i++) {
    long long l, r;
    scanf("%lld %lld", &l, &r);
    printf("%lld\n", calc(r)-calc(l-1));
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
