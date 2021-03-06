#define DEBUG
#include <cstdio>
#define MAXN 10000

using namespace std;

int main() {
#ifdef DEBUG
  freopen("100031.in", "r", stdin);
  freopen("100031.out", "w", stdout);
#endif

  int n, k=0;
  static int a[MAXN+1], b[MAXN+1];
  scanf("%d", &n);
  for (int i=1; i<=n; i++) {
    scanf("%d", b+i);
    if (!b[i]) {
      k++;
    }
  }

  for (int i=1, j=1; i<=k; i++) {
    for (; b[j]; j++);
    a[i] = j;
    j++;
  }
  for (int i=k+1, j=1; i<=n; i++) {
    for (; !b[j]; j++);
    a[i] = j;
    j++;
  }

  for (int i=1, p=1; i<=n; i++) {
    printf("%d ", p>k);
    p = a[p];
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
