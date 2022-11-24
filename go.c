#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>

#define TWOD_COPY_SYSCALL 451

void check_equal(float lhs[5][5], float rhs[5][5])
{
    int i;
    int j;
    for (i=0; i<5; i++){
        for (j=0; j<5; j++){
            if(lhs[i][j]!=rhs[i][j]){
                printf("Error : LHS[%d][%d] != RHS[%d][%d]\n", i, j, i, j);
                return;
            }
        }
    }
    printf("Message : Success LHS = RHS \n");
}
int main()
{
    float src_arr[5][5] = {{1.0,2.0,3.0,4.0,5.0},{6.0,7.0,8.0,9.0,10.0},{11.0,12.0,13.0,14.0,15.0},{16.0,17.0,18.0,19.0,20.0},{21.0,22.0,23.0,24.0,25.0}};
    float dest_arr[5][5]; 



    long sys_call_status;

    sys_call_status = syscall(TWOD_COPY_SYSCALL, src_arr, dest_arr, 5, 5);

    if (sys_call_status != EFAULT)
    {
        printf("Message : System Call 451 successfully invoked \n");
        check_equal(src_arr, dest_arr);
    }

    return 0;
}
