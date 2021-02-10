#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{

    int pids[40];
    int cpuBursts[40];
    int turnArounds[40];
    int waitings[40];
    memset(pids, 0, 40);
    memset(cpuBursts, 0, 40);
    memset(turnArounds, 0, 40);
    memset(waitings, 0, 40);

    int i, j, base_pid;

    changePolicy(3);
    pushToQueue(0, getpid());
    base_pid = getpid();
    for (i = 1; i <= 40; i++)
        if (getpid() == base_pid)
        {
            fork();
            if (getpid() != base_pid)
            {
                if (i > 10 && i < 31)
                {
                    setPriority((i % 6) + 1);
                }
                pushToQueue((i / 10) + (i % 10 != 0), getpid());
            }
        }

    if (getpid() != base_pid)
        for (j = 1; j <= 200; j++)
            printf(1, "  /%d/:/%d/  \n", getpid(), j);

    if (getpid() == base_pid)
        for (i = 0; i < 40; i++)
            pids[i] = setTimes(&cpuBursts[i], &turnArounds[i], &waitings[i]);
    else
        exit();

    printf(1, "\n\n       id : TurnAround  CpuBurst  Waiting");
    for (i = 0; i < 40; i++)
        printf(1, "\n%d -->  %d  :   %d       %d       %d", i, pids[i], turnArounds[i], cpuBursts[i], waitings[i]);

    int totalTurnAround = 0;
    int totalCpuBurst = 0;
    int totalWaiting = 0;
    int totalClassesTurnAround[4];
    int totalClassesCpuBurst[4];
    int totalClassesWaiting[4];
    memset(totalClassesTurnAround, 0, 4);
    memset(totalClassesCpuBurst, 0, 4);
    memset(totalClassesWaiting, 0, 4);

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 10; j++)
        {
            totalClassesTurnAround[i] += turnArounds[(i * 10) + j];
            totalClassesCpuBurst[i] += cpuBursts[(i * 10) + j];
            totalClassesWaiting[i] += waitings[(i * 10) + j];
        }
        printf(1, "\navg queque%d :   %d      %d      %d", i + 1, totalClassesTurnAround[i] / 10, totalClassesCpuBurst[i] / 10, totalClassesWaiting[i] / 10);
        totalTurnAround += totalClassesTurnAround[i];
        totalCpuBurst += totalClassesCpuBurst[i];
        totalWaiting += totalClassesWaiting[i];
    }
    printf(1, "\n\navgTurnAroundTotal => %d\navgCpuBurstTotal => %d\navgWaitingTotal => %d\n\n", totalTurnAround / 40, totalCpuBurst / 40, totalWaiting / 40);
    changePolicy(0);
    exit();
} 