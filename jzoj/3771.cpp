#define DEBUG
#include <cstdio>
#include <cstring>
#define MAXLENN 10001
#define MAXK 1000000000
#define MAXLENK 9

using namespace std;

typedef unsigned long long ull;

ull max(ull a, ull b) {
  return a>b ? a : b;
}

void copy(ull *a, ull *b) {
  for (ull i=0; i<=a[0]; i++) {
    b[i] = a[i];
  }
}

void add(ull *a, ull *b, ull *c) {
  ull len = max(a[0], b[0]);
  for (ull i=1; i<=len+1; i++) {
    c[i] = 0;
  }
  for (ull i=1; i<=len; i++) {
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

ull div(ull *a, ull b, ull *c) {
  ull rest=0;
  bool flag=false;
  for (int i=a[0]; i>0; i--) {
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
    static ull n[2][MAXLENN/MAXLENK+10], ans[MAXLENN/MAXLENK+10], temp[2][MAXLENN/MAXLENK+10];
    n[0][0] = ans[0] = 0;
    for (int i=strlen(s)-1, j=0, t=1; i>=0; i--, j++) {
      t = j%MAXLENK ? t*10 : 1;
      n[0][j/MAXLENK+1] = (j%MAXLENK ? n[0][j/MAXLENK+1] : 0)+(s[i]-'0')*t;
      n[0][0] = j/MAXLENK+1;
    }

    div(n[0], 1<<(m-1), n[1]);
    for (int i=1; n[i][0]>0; i=(i+1)%2) {
      ull rest = div(n[i], 2, temp[0]);
      div(n[i], 1<<m, n[(i+1)%2]);
      copy(ans, temp[1]);
      add(temp[1], temp[0], ans);
      if (rest) {
	ans[1]++;
	for (int j=1; ans[j]>=MAXK; j++) {
	  ans[j+1] += ans[j]/MAXK;
	  ans[j] %= MAXK;
	}
	ans[0] = ans[ans[0]+1] ? ans[0]+1 : ans[0];
      }
    }

    printf("%llu", ans[ans[0]]);
    for (int i=ans[0]-1; i>0; i--) {
      printf("%09llu", ans[i]);
    }
    printf("\n");
  }

  fcloseall();
  return 0;
}
