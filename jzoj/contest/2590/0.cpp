#define DEBUG
#include <cstdio>
#define MAXN 100000

using namespace std;

struct List {
  int p, n;
};

void push(List *l, int p, int v) {
  l[v].p = p;
  l[v].n = l[p].n;
  l[l[v].p].n = v;
  l[l[v].n].p = v;
}

void pop(List *l, int p) {
  l[l[p].p].n = l[p].n;
  l[l[p].n].p = l[p].p;
  l[p].n = l[p].p = 0;
}

int main() {
#ifdef DEBUG
  freopen("0.in", "r", stdin);
  freopen("0.out", "w", stdout);
#endif

  static List book[MAXN+1];
  static int a[MAXN+1];
  int n;
  scanf("%d", &n);
  for (int i=1; i<=n; i++) {
    scanf("%d", a+i);
    push(book, i-1, i);
  }

  // for (; book[0].n!=0;) {
  //   for (int i=book[0].n, j=book[0].n; j; i=j) {
  //     for (; j && ((a[i]|a[j])==a[i] || (a[i]|a[j])==a[j]); j=book[j].n);
  //     if (j) {
  // 	int x=a[i], y=a[j];
  // 	a[i] = x&y, a[j]=x|y;
  //     }
  //     pop(book, i);
  //   }
  // }

  for (int i=1; i<=n; i++) {
    for (int j=1; j<=n; j++) {
      if ((a[i]|a[j])!=a[i] && (a[i]|a[j])!=a[j]) {
	int x=a[i], y=a[j];
	a[i] = x|y, a[j]=x&y;
      }
    }
  }

  unsigned long long ans=0;
  for (int i=1; i<=n; i++) {
    ans += (unsigned long long)a[i]*a[i];
  }
  printf("%llu", ans);

  fcloseall();
  return 0;
}
