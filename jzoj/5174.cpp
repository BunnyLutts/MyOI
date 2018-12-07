#define DEBUG
#include <cstdio>
#include <algorithm>
#define MAXN 100000

using namespace std;

int n, linex[MAXN+1][3], liney[MAXN+1][3];

void qsort(int a[][3], int l, int r, int f, int s) {
  int i=l, j=r, mid1=a[(l+r)/2][f], mid2=a[(l+r)/2][s], temp;
  for (; i<=j; ) {
    for (; a[j][f]>mid1 || (a[j][f]==mid1 && a[j][s]>mid2); j--);
    for (; a[i][f]<mid1 || (a[i][f]==mid1 && a[i][s]<mid2); i++);
    if (i<=j) {
      for (int k=0; k<3; k++) {
	temp = a[i][k], a[i][k] = a[j][k], a[j][k] = temp;
      }
      i++, j--;
    }
  }
  if (i<r) {
    qsort(a, i, r, f, s);
  }
  if (j>l) {
    qsort(a, l, j, f, s);
  }
}

int main() {
#ifdef DEBUG

  freopen("5174.in", "r", stdin);
  freopen("5174.out", "w", stdout);

#endif // DEBUG

  scanf("%d", &n);
  for (int i=1; i<=n; i++) {
    int x1, y1, x2, y2, temp;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    if (y1==y2) {
      temp = ++linex[0][0];
      linex[temp][0] = y1, linex[temp][1] = x1, linex[temp][2] = x2;
    } else {
      temp = ++liney[0][0];
      liney[temp][0] = x1, liney[temp][1] = y1, liney[temp][2] = y2;
    }
  }
  qsort(linex, 1, linex[0][0], 0, 1);
  qsort(liney, 1, liney[0][0], 1, 2);

  int ans=0;
  for (int i=1, j=1; i<=linex[0][0] && j<=liney[0][0]; i++) {
    for (; j<=liney[0][0] && liney[j][2]<linex[i][0]; j++);
    for (int k=j; liney[k][1]<=linex[i][0] && liney[k][2]>=linex[i][0]; k++) {
      if (liney[k][0]>=linex[i][1] && liney[k][0]<=linex[i][2]) {
	int y=linex[i][0], x=liney[k][0];
	ans = max(ans, min(min(x-linex[i][1], linex[i][2]-x), min(y-liney[k][1], liney[k][2]-y)));
      }
    }
  }
  if (ans) {
    printf("%d", ans);
  } else {
    printf("Human intelligence is really terrible");
  }

  fclose(stdin);
  fclose(stdout);
}
