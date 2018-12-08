#include <cstdio>

using namespace std;

int main() {
  int n, k, d;
  scanf("%d %d %d", &n, &k, &d);
  if (k==2) {
   printf("%d", (n-1)*n/2-n+1);
  }
  return 0;
}
