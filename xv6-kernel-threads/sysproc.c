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
  return proc->pid;
}

int
sys_sbrk(void)
{
  // int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  // addr = proc->sz;
  // if(growproc(n) < 0)
  //   return -1;
  // return addr;
  
  // modified growproc to return old size
  // have to change the way we access the size 
  // as growproc is now synchronized
  return growproc(n);
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
    if(proc->killed){
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
sys_procdump(void)
{
  procdump();
  return 0;
}

int sys_kthread_create(void)
{
  int start; // an int holding address bits of the func
  int size;
  char *stack;
  if(argint(0, &start)<0 || argint(2, &size)<0
      || size<=0 || argptr(1, &stack, size)<0)
    return -1;
  
  return kthread_create((void*(*)())start, stack, size);
}

int sys_kthread_id(void)
{
  return kthread_id();
}

int sys_kthread_exit(void)
{
  kthread_exit();
  return 0;
}

int sys_kthread_join(void)
{
  int tid;
  if(argint(0, &tid) < 0)
    return -1;

  return kthread_join(tid);
}