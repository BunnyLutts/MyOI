#define DEBUG
#include <cstdio>

using namespace std;

int main() {
#ifdef DEBUG
  freopen("0.in", "r", stdin);
  freopen("0.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  for (int i=1; i<=t; i++) {
    long long l, r, ans=0;
    scanf("%lld %lld", &l, &r);
    for (long long j=l; j<=r; j++) {
      bool flag=false;
      for (int k=1; k<10; k++) {
	if (j%k==0 && (j/k-1)%9+1==k) {
	  flag = true;
	  break;
	}
      }
      ans += flag;
    }
    printf("%lld\n", ans);
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
