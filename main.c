#include<stdio.h>

int main(){
    int n, r, i, j, total=0, deadlock=0;
    printf("Enter the number of chefs working in the kitchen: ");
    scanf("%d", &n);
    printf("Enter the maximum number of ingredients each chef can claim: ");
    scanf("%d", &r);
    int max[n][r], allocation[n][r], need[n][r], available[r];
    for(i=0;i<r;i++){
        printf("Enter the number of ingredients in jar %d: ", i+1);
        scanf("%d", &available[i]);
    }
    for(i=0;i<n;i++){
        printf("Enter the maximum number of ingredients chef %d needs: ", i+1);
        for(j=0;j<r;j++){
            scanf("%d", &max[i][j]);
            total += max[i][j];
        }
    }
    if(total > n*r){
        printf("Deadlock situation: Total number of ingredients required exceeds total number of ingredients available.\n");
        return 0;
    }
    for(i=0;i<n;i++){
        for(j=0;j<r;j++){
            allocation[i][j] = 0;
            need[i][j] = max[i][j];
        }
    }
    for(i=0;i<r;i++){
        available[i] -= allocation[0][i];
        need[0][i] -= allocation[0][i];
    }
    for(i=1;i<n;i++){
        int flag = 0;
        for(j=0;j<r;j++){
            if(need[i][j] > available[j]){
                flag = 1;
                break;
            }
        }
        if(flag == 1){
            deadlock = 1;
            break;
        }
        for(j=0;j<r;j++){
            available[j] -= allocation[i][j];
            need[i][j] -= allocation[i][j];
        }
    }
    if(deadlock == 1){
        printf("Deadlock situation: System is not in a safe state.\n");
        return 0;
    }
    for(i=0;i<n;i++){
        for(j=0;j<r;j++){
            if(need[i][j] > available[j]){
                deadlock = 1;
                break;
            }
            allocation[i][j] = max[i][j] - need[i][j];
            available[j] -= allocation[i][j];
        }
    }
    if(deadlock == 1){
        printf("Deadlock situation: System is not in a safe state.\n");
        return 0;
    }
    printf("Allocation matrix:\n");
    for(i=0;i<n;i++){
        for(j=0;j<r;j++){
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }
    return 0;
}
