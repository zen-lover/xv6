#define NPROC        64  // maximum number of processes
#define KSTACKSIZE 4096  // size of per-process kernel stack
#define NCPU          8  // maximum number of CPUs
#define NOFILE       16  // open files per process
#define NFILE       100  // open files per system
#define NINODE       50  // maximum number of active i-nodes
#define NDEV         10  // maximum major device number
#define ROOTDEV       1  // device number of file system root disk
#define MAXARG       32  // max exec arguments
#define MAXOPBLOCKS  10  // max # of blocks any FS op writes
#define LOGSIZE      (MAXOPBLOCKS*3)  // max data blocks in on-disk log
#define NBUF         (MAXOPBLOCKS*3)  // size of disk block cache
#define FSSIZE       1000  // size of file system in blocks

#define HIGHPRIORITY  1 
#define LOWPRIORITY   6

#define DEFAULTSCHED    0
#define ROBINSCHED      1
#define PRIORITYSCHED   2
#define MULTISCHED      3

#define QUANTUM         10

// #define NOQUEUE           0
// #define  DEFAULTQUEUE     1
// #define  PRIORITYQUEUE    2
// #define  XPRIORITYQUEUE   3
// #define  ROUNDROBINQUEUE  4
