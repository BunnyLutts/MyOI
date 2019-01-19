#define DEBUG
#include <cstdio>
#define MAXN 1000000

using namespace std;

int main() {
#ifdef DEBUG
  freopen("2.in", "r", stdin);
  freopen("2.out", "w", stdout);
#endif

  static bool book[MAXN+1];
  int t;
  scanf("%d", &t);
  for (int ti=1; ti<=t; ti++) {
    int n, m;
    scanf("%d %d", &n, &m);
    int ans=0;
    for (int i=1; i<=n; i++) {
      if (!book[i]) {
	for (int j=i; j<=n; j*=2) {
	  book[j] = true;
	}
	ans++;
      }
    }
    printf("%d\n", ans);
    for (int i=1; i<=n; i++) {
      book[i] = false;
    }
  }

  fcloseall();
  return 0;
}
