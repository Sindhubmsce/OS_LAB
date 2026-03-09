#include <stdio.h>
struct process{
    int pid,at,bt,ct,tat,wt,rt};
int main(){
    int n,i,j,time=0;
    struct process p[10],temp;
    float avgwt=0,avgtat=0;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        printf("\nEnter Arrival Time for P%d: ",i+1);
        scanf("%d",&p[i].at);

        printf("Enter Burst Time for P%d: ",i+1);
        scanf("%d",&p[i].bt);

        p[i].pid=i+1;
    }

    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(p[i].bt > p[j].bt){
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;

    for(i=0;i<n;i++){

        if(time < p[i].at)
            time = p[i].at;

        time = time + p[i].bt;
        p[i].ct = time;

        p[i].tat = p[i].ct - p[i].at;

        p[i].wt = p[i].tat - p[i].bt;

        avgwt += p[i].wt;
        avgtat += p[i].tat;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f",avgwt/n);
    printf("\nAverage Turnaround Time = %.2f",avgtat/n);

    return 0;
}
