#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
static int *a;
static int *n;
int main() {
  printf("Operating System\n");
  printf("Author : ThangDevAlone\n");
  a=(int*) malloc (100* sizeof (int));
  a= mmap(NULL, sizeof *a, PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  n= mmap(NULL, sizeof *n, PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  int k = 0;
  *n=1;
  pid_t pid;
  
  do {
    printf("Nhap so lon hon 0 de chay The Collatz Conjecture : ");
    scanf("%d", &k);
  } while (k <= 0);
  // phan luong
  pid = fork();

  if (pid == 0) {
    printf("Tien trinh con dang chay...\n");
    a[0]=k;
    int i = 1;
    while (k != 1) {
      if (k % 2 == 0) {
        k = k / 2;
        *n=*n+1;
        a[i++] = k;
      } else if (k % 2 == 1) {
        k = 3 * (k) + 1;
        *n=*n+1;
        a[i++] = k;
      }
    }
    printf("Tien trinh con xong.\n");
   
  } else {
    printf("Tien trinh cha dang doi tien trinh con..\n");
    /* wait(NULL) hay chính xác hơn là wait(0) có nghĩa là đợi cho đến khi một trạng thái thay đổi trong tiến trình con */
    wait(NULL);
     printf("Day so la: %d ",a[0]);
	for(int i=1;i<*n;i++){
	    printf("%d ", a[i]);
	}
    munmap(a, sizeof *a);
    munmap(n, sizeof *n);
    printf("\nTien trinh cha xong.\n");

  }
  return 0;
}
