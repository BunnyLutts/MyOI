#define DEBUG
#include <cstdio>
#include <cstring>
#define MAXLENN 10001
#define MAXK 100000000
#define MAXLENK 8

using namespace std;

long long max(long long a, long long b) {
  return a>b ? a : b;
}

void copy(long long *a, long long *b) {
  for (long long i=0; i<=a[0]; i++) {
    b[i] = a[i];
  }
}

void add(long long *a, long long *b, long long *c) {
  long long len = max(a[0], b[0]);
  for (long long i=1; i<=len+1; i++) {
    c[i] = 0;
  }
  for (long long i=1; i<=len; i++) {
    if (i<=a[0]) {
      c[i] += a[i];
    }
    if (i<=b[0]) {
      c[i] += b[i];
    }
    c[i+1] += c[i]/MAXK;
    c[i] %= MAXK;
  }
  c[0] = c[len+1] ? len+1 : len;
}

void multi(long long *a, int b, long long *c) {
  for (long long i=1; i<=a[0]+1; i++) {
    c[i] = 0;
  }
  for (long long i=1; i<=a[0]; i++) {
    c[i] += a[i]*b;
    c[i+1] += c[i]/MAXK;
    c[i] %= MAXK;
  }
  c[0] = c[a[0]+1] ? a[0]+1 : a[0];
}

long long div(long long *a, int b, long long *c) {
  long long rest=0;
  bool flag=false;
  for (long long i=a[0]; i>0; i--) {
    rest = rest*MAXK+a[i];
    if (rest/b && !flag) {
      flag = true;
      c[0] = i;
    }
    c[i] = rest/b;
    rest %= b;
  }
  if (!flag) {
    c[0] = 0;
  }
  return rest;
}

int main() {
#ifdef DEBUG
  freopen("3771.in", "r", stdin);
  freopen("3771.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  for (int ti=1; ti<=t; ti++) {
    char s[MAXLENN+1];
    int m;
    scanf("%s %d", s, &m);
    static long long n[MAXLENN/MAXLENK+1000], ans[MAXLENN/MAXLENK+1000], temp[2][MAXLENN/MAXLENK+1000], one[MAXLENN/MAXLENK+1000];
    one[0] = one[1] = 1;
    memset(n, 0, sizeof(n));
    memset(ans, 0, sizeof(ans));
    for (int i=strlen(s)-1, j=0, t=1; i>=0; i--, j++) {
      t = j%MAXLENK ? t*10 : 1;
      n[j/MAXLENK+1] += (s[i]-'0')*t;
      n[0] = j/MAXLENK+1;
    }

    for (; n[0]>0; ) {
      div(n, 1<<(m-1), temp[0]);
      if (div(temp[0], 2, temp[1])) {
	add(temp[1], ans, temp[0]);
	add(temp[0], one, ans);
      } else {
	add(temp[1], ans, temp[0]);
	copy(temp[0], ans);
      }
      copy(temp[1], n);
    }

    printf("%lld", ans[ans[0]]);
    for (int i=ans[0]-1; i>0; i--) {
      printf("%08lld", ans[i]);
    }
    printf("\n");
  }

  fcloseall();
  return 0;
}
