#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{

    int pids[30];
    int cpuBursts[30];
    int turnArounds[30];
    int waitings[30];
    memset(pids, 0, 30);
    memset(cpuBursts, 0, 30);
    memset(turnArounds, 0, 30);
    memset(waitings, 0, 30);

    int i, j, base_pid;

    changePolicy(2);

    base_pid = getpid();
    for (i = 1; i <= 30; i++)
        if (getpid() == base_pid)
        {
            fork();
            if (getpid() != base_pid)
            {
                printf(1, "\n %d -- > %d\n", setPriority((i / 5) + (i % 5 != 0)), getpid());
            }

        }

    if (getpid() != base_pid)
        for (j = 1; j <= 250; j++)
            printf(1, "  /%d/:/%d/  \n", getpid(), j);

    if (getpid() == base_pid)
        for (i = 0; i < 30; i++)
            pids[i] = setTimes(&cpuBursts[i], &turnArounds[i], &waitings[i]);
    else
        exit();

    printf(1, "\n\nid : TurnAround  CpuBurst  Waiting");
    for (i = 0; i < 30; i++)
        printf(1, "\n%d --> %d  :   %d       %d       %d", i,pids[i], turnArounds[i], cpuBursts[i], waitings[i]);


    int totalTurnAround = 0;
    int totalCpuBurst = 0;
    int totalWaiting = 0;
    int totalClassesTurnAround[6];
    int totalClassesCpuBurst[6];
    int totalClassesWaiting[6];
    memset(totalClassesTurnAround, 0, 6);
    memset(totalClassesCpuBurst, 0, 6);
    memset(totalClassesWaiting, 0, 6);

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 5; j++)
        {
            totalClassesTurnAround[i] += turnArounds[(i * 5) + j];
            totalClassesCpuBurst[i] += cpuBursts[(i * 5) + j];
            totalClassesWaiting[i] += waitings[(i * 5) + j];
        }
        printf(1, "\naverages of priority %d :   %d      %d        %d", i + 1, totalClassesTurnAround[i] / 5, totalClassesCpuBurst[i] / 5, totalClassesWaiting[i] / 5);
        totalTurnAround += totalClassesTurnAround[i];
        totalCpuBurst += totalClassesCpuBurst[i];
        totalWaiting += totalClassesWaiting[i];
    }
    printf(1, "\n\navgTurnAroundTotal => %d\navgCpuBurstTotal => %d\navgWaitingTotal => %d\n\n", totalTurnAround / 30, totalCpuBurst / 30, totalWaiting / 30);

    exit();
} 