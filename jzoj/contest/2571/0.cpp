#define DEBUG
#include <cstdio>

using namespace std;

long long exgcd(long long a, long long b, long long &x, long long &y) {
  if (b==0) {
    x = 1, y = 0;
    return a;
  } else {
    long long tx, ty, ret;
    ret = exgcd(b, a%b, tx, ty);
    x = ty, y = tx-(a/b)*ty;
    return ret;
  }
}

int main() {
#ifdef DEBUG
  freopen("0.in", "r", stdin);
  freopen("0.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  for (int ti=1; ti<=t; ti++) {
    int s, m, l, r;
    scanf("%d %d %d %d", &s, &m, &l, &r);
    if (l>=m) {
      printf("-1\n");
    }
    if (l==r) {
      long long x, y, gcd = exgcd(s, m, x, y);
      if (l%gcd) {
	printf("-1\n");
      } else {
	x *= l/gcd;
	long long lcm = s/gcd*m;
	x %= lcm/s;
	x = x<0 ? x+lcm/s : x;
	printf("%lld\n", x);
      }
    } else {
      for (int x=1; ; x++) {
	if ((long long)s%m*x%m>=l && (long long)s%m*x%m<=r) {
	  printf("%d\n", x);
	  break;
	}
      }
    }
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
