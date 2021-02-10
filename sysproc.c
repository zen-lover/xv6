#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_getParentID(void)
{
  int pid;
  pid = myproc()->pid;
  return getParentID(pid);
}

int
sys_getChildren(void){
  int* children;
  if(argptr(0, (void *)&children,sizeof(*children)) < 0)
    return -1;
  return getChildren(children);
}

int
sys_getSyscallCounter(void)
{

  int syscall;
  if(argint(0, &syscall) < 0)
    return -1;
  int pid;
  pid = myproc()->pid;
  return syscallCounter(syscall, pid);
}

int
sys_setPriority(void)
{
  int priority;
  if(argint(0, &priority) < 0)
    return -1;
  int pid;
  pid = myproc()->pid;
  return setPriority(pid, priority);
}

int
sys_changePolicy(void)
{
  int policy;
  if(argint(0, &policy) < 0)
    return -1;
  return changePolicy(policy);
}

int
sys_setTimes(void)
{
  int *cpuBurstTime;
  int *turnAroundTime;
  int *waitingTime;

  if(argptr(0, (void *)&cpuBurstTime,10) < 0)
    return -1; 
  if(argptr(1, (void *)&turnAroundTime,20) < 0)
    return -1;
  if(argptr(2, (void *)&waitingTime,30) < 0)
    return -1;

  return setTimes(cpuBurstTime, turnAroundTime, waitingTime);
} 

int
sys_pushToQueue(void)
{
  int queueNumber;
  int pid;

  if(argint(0, &queueNumber) < 0)
    return -1;
  if(argint(1, &pid) < 0)
    return -1;

  return pushToQueue(queueNumber,pid);
} 