#define DEBUG
#include <cstdio>
#include <cstring>
#define INF 0x7ffffff
#define MAXM 100
#define MAXT 10

using namespace std;

int min(int a, int b) {
  return a<b ? a : b;
}

void qsort(int *a, int l, int r) {
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
    qsort(a, i, r);
  }
  if (j>l) {
    qsort(a, l, j);
  }
}

int main() {
  freopen("river.in", "r", stdin);
  freopen("river.out", "w", stdout);

  static int pos[MAXM+1], f[MAXM+1][MAXT];
  int l, s, t, m;
  scanf("%d %d %d %d", &l, &s, &t, &m);
  for (int i=1; i<=m; i++) {
    scanf("%d", pos+i);
  }

  int ans=INF;
  if (s==t) {
    ans=0;
    for (int i=1; i<=m; i++) {
      ans += pos[i]%s==0;
    }
    printf("%d\n", ans);
    return 0;
  }
  qsort(pos, 1, m);
  memset(f, 127, sizeof(f));
  f[0][0] = 0;
  pos[++m] = l;
  for (int i=1; i<=m; i++) {
    for (int j=0; j<s; j++) {
      for (int k=0; k<s; k++) {
	if (pos[i]+j==pos[i-1]+k) {
	  f[i][j] = min(f[i][j], f[i-1][k]);
	  f[i-1][k] = INF;
	} else if (pos[i]+j>=pos[i-1]+k+2*s || (pos[i]+j>=pos[i-1]+k+s && pos[i]+j<=pos[i-1]+k+t)) {
	  f[i][j] = min(f[i][j], f[i-1][k]);
	}
      }
    }
    if (i<m) {
      f[i][0]++;
    }
  }

  for (int i=0; i<s; i++) {
    ans = min(ans, f[m][i]);
  }
  printf("%d", ans);

  fclose(stdin);
  fclose(stdout);
  return 0;
}
