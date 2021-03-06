#define DEBUG
#include <cstdio>
#define MAXN 10000

using namespace std;

int a[MAXN+1][2], b[MAXN+1][2], n;

void swap(int a[2], int b[2]) {
  static int temp;
  temp = a[0], a[0] = b[0], b[0] = temp;
  temp = a[1], a[1] = b[1], b[1] = temp;
}

void mySort() {
  for (int i=1, j=n; i<j; ) {
    for (; a[i][0]==0; i++);
    for (; a[j][0]==1; j--);
    if (i<j) {
      swap(a[i], a[j]);
      i++, j--;
    }
  }
  for (int i=1, j=a[0][0]; i<j; ) {
    for (; a[i][1]==0; i++);
    for (; a[j][1]==1; j--);
    if (i<j) {
      swap(a[i], a[j]);
      i++, j--;
    }
  }
  for (int i=a[0][0]+1, j=n; i<j; ) {
    for (; a[i][1]==0; i++);
    for (; a[j][1]==1; j--);
    if (i<j) {
      swap(a[i], a[j]);
      i++, j--;
    }
  }
}

void getAns() {
  mySort();
  b[1][0] = a[1][0];
  b[1][1] = a[1][1];
  for (int i=2, j=2, k=a[0][0]+1; i<=n; i++) {
    if (j<=a[0][0] && a[j][0]==b[i-1][1]) {
      b[i][0] = a[j][0];
      b[i][1] = a[j][1];
      j++;
    } else {
      b[i][0] = a[k][0];
      b[i][1] = a[k][1];
      k++;
    }
  }
}

int main() {
#ifdef DEBUG
  freopen("0.in", "r", stdin);
  freopen("0.out", "w", stdout);
#endif

  scanf("%d", &n);
  for (int i=1; i<=n; i++) {
    scanf("%d", &a[i][0]);
    a[0][a[i][0]]++;
  }
  for (int i=1; i<=a[0][0]; i++) {
    a[i][1] = 0;
  }
  for (int i=a[0][0]+1; i<=n; i++) {
    a[i][1] = 1;
  }

  getAns();
  for (int i=1; i<=n; i++) {
    printf("%d ", b[i][0]);
  }

  fclose(stdin);
  fclose(stdin);
  return 0;
}
