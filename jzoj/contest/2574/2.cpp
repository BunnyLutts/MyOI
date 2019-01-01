#define DEBUG
#include <cstdio>
#define MAXN 100000

using namespace std;

void sort(int *a, int l, int r) {
  int i=l, j=r, mid=a[(l+r)/2], temp;
  for (; i<=j; ) {
    for (; a[j]>mid; j--);
    for (; a[i]<mid; i++);
    if (i<=j) {
      temp=a[i], a[i]=a[j], a[j]=temp;
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

int max(int a, int b) {
  return a>b ? a : b;
}

int search(int *a, int t) {
  int ret=0;
  for (int l=1, r=a[0], mid; l<=r; ) {
    mid = (l+r)/2;
    if (a[mid]<=t) {
      ret = mid;
      l = mid+1;
    } else {
      r = mid-1;
    }
  }
  return ret;
}

void solve1(int *a, int *map, int n, int m) {
  static int f[3001][3001];
  for (int i=1; i<=n; i++) {
    int t = search(map, a[i]);
    for (int j=i; j<=n; j++) {
      f[j][t]++;
    }
  }

  for (int i=1; i<=m; i++) {
    int l, r;
    scanf("%d %d", &l, &r);
    int ans=0;
    for (int i=1; i<=map[0]; i++) {
      ans = max(ans, map[i]*(f[r][i]-f[l-1][i]));
    }
    printf("%d\n", ans);
  }
}

void solve2(int *a, int *map, int n, int m) {
  static int f[MAXN+1][51];
  for (int i=1; i<=n; i++) {
    int t = search(map, a[i]);
    for (int j=i; j<=n; j++) {
      f[j][t]++;
    }
  }

  for (int i=1; i<=m; i++) {
    int l, r;
    scanf("%d %d", &l, &r);
    int ans=0;
    for (int i=1; i<=map[0]; i++) {
      ans = max(ans, map[i]*(f[r][i]-f[l-1][i]));
    }
    printf("%d\n", ans);
  }
}

int main() {
#ifdef DEBUG
  freopen("2.in", "r", stdin);
  freopen("2.out", "w", stdout);
#endif

  static int a[MAXN+1], map[MAXN+1];
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i=1; i<=n; i++) {
    scanf("%d", a+i);
    map[i] = a[i];
  }
  sort(map, 1, n);
  for (int i=1; i<=n; i++) {
    if (map[map[0]]!=map[i]) {
      map[++map[0]] = map[i];
    }
  }

  if (n<=3000) {
    solve1(a, map, n, m);
  } else {
    solve2(a, map, n, m);
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
