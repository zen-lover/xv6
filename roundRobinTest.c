#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int pids[10];
    int cpuBursts[10];
    int turnArounds[10];
    int waitings[10];
    memset(pids, 0, 10);
    memset(cpuBursts, 0, 10);
    memset(turnArounds, 0, 10);
    memset(waitings, 0, 10);

    int i, base_pid;

    changePolicy(1);

    base_pid = getpid();
    for (i = 0; i < 10; i++)
        if (getpid() == base_pid)
            fork();

    if (getpid() != base_pid)
    {
        int j;
        for (j = 1; j <= 1000; j++)
            printf(1, "  /%d/:/%d/  \n", getpid(), j);
    }

    if (getpid() == base_pid)
        for (i = 0; i < 10; i++)
            pids[i] = setTimes(&cpuBursts[i], &turnArounds[i], &waitings[i]);
    else
        exit();

    printf(1, "\n\nid :TurnAround  CpuBurst  Waiting");
    for (i = 0; i < 10; i++)
        printf(1, "\n%d  :   %d       %d       %d", pids[i], turnArounds[i], cpuBursts[i], waitings[i]);

    int totalTurnAround = 0;
    int totalCpuBurst = 0;
    int totalWaiting = 0;
    for (i = 0; i < 10; i++)
    {
        totalTurnAround += turnArounds[i];
        totalCpuBurst += cpuBursts[i];
        totalWaiting += waitings[i];
    }

    printf(1,"\n\navgTurnAroundTotal => %d\navgCpuBurstTotal => %d\navgWaitingTotal => %d\n\n", totalTurnAround / 10, totalCpuBurst / 10, totalWaiting / 10);

    exit();
} 