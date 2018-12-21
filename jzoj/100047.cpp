#define DEBUG
#include <cstdio>
#include <cstring>
#define MAXN 20
#define MAXA 1048576
#define MAXLOGA 20

using namespace std;

int main () {
#ifdef DEBUG
  freopen("100047.in", "r", stdin);
  freopen("100047.out", "w", stdout);
#endif

  int n, q;
  scanf("%d %d", &n, &q);
  static int pool[MAXLOGA+MAXN+2];
  for (int i=1; i<=n; i++) {
    scanf("%d", &pool[i]);
  }
  for (int i=0; i<=MAXLOGA; i++) {
    pool[n+i+1] = 1<<i;
  }
  n += MAXLOGA+1;

  static int que[MAXA+1], f[MAXA+1];
  memset(f, 127, sizeof(f));
  f[0] = 0;
  que[1] = 0;
  for (int head=1, tail=1; head<=tail; ) {
    int x=que[head++];
    for (int i=1; i<=n; i++) {
      if ((x^pool[i])<=MAXA && f[x^pool[i]]>f[x]+1) {
	f[x^pool[i]] = f[x]+1;
	que[++tail] = x^pool[i];
      }
    }
  }

  for (int i=1; i<=q; i++) {
    int s, t;
    scanf("%d %d", &s, &t);
    printf("%d\n", f[s^t]);
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
