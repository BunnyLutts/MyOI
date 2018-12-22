#define DEBUG
#include <cstdio>
#define MAXK 22680

long long calc(int *suf, long long x) {
  return suf[MAXK]*(x/MAXK)+suf[x%MAXK];
}

int main() {
#ifdef DEBUG
  freopen("2700.in", "r", stdin);
  freopen("2700.out", "w", stdout);
#endif

  static int suf[MAXK+1];
  int t;
  scanf("%d", &t);
  for (int i=1; i<=MAXK; i++) {
    suf[i] = suf[i-1];
    for (int j=1; j<=9; j++) {
      if (i%j==0 && (i/j-1)%9+1==j) {
	suf[i]++;
	break;
      }
    }
  }
  for (int i=1; i<=t; i++) {
    long long l, r;
    scanf("%lld %lld", &l, &r);
    printf("%lld\n", calc(suf, r)-calc(suf, l-1));
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
