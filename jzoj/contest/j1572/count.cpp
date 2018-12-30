#define DEBUG
#include <cstdio>
#define MAXN 200000
#define MAXS 10000

using namespace std;

void sort(int *a, int l, int r) {
  int i=l, j=r, mid=a[(l+r)/2], temp;
  for (; i<=j; ) {
    for (; a[j]>mid; j--);
    for (; a[i]<mid; i++);
    if (i<=j) {
      temp = a[i], a[i] = a[j], a[j] = temp;
      i++, j--;
    }
  }
  if (i<r) {
    sort(a, i, r);
  }
  if (j>l) {
    sort(a, l, j);
  }
}

int main() {
  freopen("count.in", "r", stdin);
  freopen("count.out", "w", stdout);

  static int a[MAXN+1], ans[MAXS+1][2];
  int n;
  scanf("%d", &n);
  for (int i=1; i<=n; i++) {
    scanf("%d", a+i);
  }
  sort(a, 1, n);

  int p=0;
  ans[0][0] = -1;
  for (int i=1; i<=n; i++) {
    if (a[i]!=ans[p][0]) {
      ans[++p][0] = a[i];
    }
    ans[p][1]++;
  }
  for (int i=1; i<=p; i++) {
    printf("%d %d\n", ans[i][0], ans[i][1]);
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
