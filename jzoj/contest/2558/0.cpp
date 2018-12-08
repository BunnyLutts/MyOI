#define DEBUG
#include <cstdio>
#include <algorithm>
#define MODS 10000007
#define MAXN 100000

using namespace std;

class Matrix {
public:
  int n, m;
  long long a[2][2];

  Matrix operator* (Matrix a) {
    Matrix ret;
    if (m!=a.n) {
      throw "Cannot calc sum.";
    }
    ret.n=n, ret.m=a.m;
    for (int i=0; i<ret.n; i++) {
      for (int j=0; j<ret.m; j++) {
	ret.a[i][j] = 0;
	for (int k=0; k<m; k++) {
	  ret.a[i][j] = (ret.a[i][j]+(this->a[i][k]*a.a[k][j])%MODS)%MODS;
	}
      }
    }

    return ret;
  }
};

Matrix qpower(Matrix a, int n) {
  Matrix s = {.n=a.n, .m=a.m, .a={{1, 0}, {0, 1}}};
  for (; n>1; n/=2) {
    if (n%2) {
      s = s*a;
    }
    a = a*a;
  }
  return s*a;
}

int main() {
#ifdef DEBUG
  freopen("0.in", "r", stdin);
  freopen("0.out", "w", stdout);
#endif

  int n, k;
  scanf("%d %d", &n, &k);
  static int s[MAXN+1];
  for (int i=1; i<=n; i++) {
    scanf("%d", s+i);
  }
  sort(s+1, s+n+1);
  long long ans=0, a, b;
  for (int i=1; i<=n-2; i++) {
    ans = ((ans+s[i])%MODS+MODS)%MODS;
  }
  if (s[n-1]<0) {
    int t=(s[n-1]/-s[n])+1;
    ans += ((s[n-1]+(s[n-1]+s[n]*(t-1)))*t/2)%MODS;
    a=s[n-1]+s[n]*t, b=s[n];
    k-= t;
  } else {
    a=s[n-1], b=s[n];
  }

  Matrix temp, q;
  temp = {.n=2, .m=2, .a={{0, 1}, {1, 1}}};
  q = {.n=1, .m=2, .a={{1 ,1}}};
  q = q*qpower(temp, k+1);
  ans = (ans+(a*q.a[0][0])%MODS+(b*((q.a[0][1]+MODS-1)%MODS))%MODS)%MODS;
  printf("%lld", ans);

  fclose(stdin);
  fclose(stdout);
  return 0;
}
