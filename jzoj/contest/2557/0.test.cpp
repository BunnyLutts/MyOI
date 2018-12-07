#define DEBUG
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#define MAXN 7

using namespace std;

int n;

class Array{
public:
  int v[MAXN+1];

  static int cmp(Array x, Array y) {
    for (int i=1; i<=n; i++) {
      if (x.v[i]!=y.v[i]) {
	return x.v[i]<y.v[i];
      }
    }
    return false;
  }
};

void test() {
  static Array a[MAXN+1];
  for (int i=1; i<=n; i++) {
    a[1].v[i] = rand()%2;
  }
  for (int i=2; i<=n; i++) {
    for (int j=1; j<=n; j++) {
      a[i].v[j] = a[1].v[(j+i-2)%n+1];
    }
  }
  sort(a+1, a+n+1, Array::cmp);

  FILE *f = fopen("0.in", "w");
  fprintf(f, "%d\n", n);
  for (int i=1; i<=n; i++) {
    fprintf(f, "%d ", a[i].v[n]);
  }
  fclose(f);

  f = fopen("0.test.out", "w");
  for (int i=1; i<=n; i++) {
    fprintf(f, "%d ", a[1].v[i]);
  }
  fclose(f);

  if (system("./0") || system("./0.bf") || system("cmp 0.out 0.bf.out")) {
    printf("Error\n");
    exit(-1);
  }
}

int main() {
  srand(time(NULL));

  int t;
  scanf("%d", &t);
  for (int i=1; i<=t; i++) {
    n = rand()%(MAXN-1)+1;
    test();
  }

  fclose(stdin);
  fclose(stdout);
}
