// the registers xv6 will save and restore
// to stop and subsequently restart a process
struct context {
  int eip;
  int esp;
  int ebx;
  int ecx;
  int edx;
  int esi;
  int edi;
  int ebp;
};
// the different states a process can be in
enum proc_state { UNUSED, EMBRYO, SLEEPING,
                  RUNNABLE, RUNNING, ZOMBIE };
// the information xv6 tracks about each process
// including its register context and state
struct proc {
  char *mem;                  // Start of process memory
  uint sz;                    // Size of process memory
  char *kstack;               // Bottom of kernel stack
                              // for this process
  enum proc_state state;      // Process state
  int pid;                    // Process ID
  struct proc *parent;        // Parent process
  void *chan;                 // If !zero, sleeping on chan
  int killed;                 // If !zero, has been killed
  struct file *ofile[NOFILE]; // Open files
  struct inode *cwd;          // Current directory
  struct context context;     // Switch here to run process
  struct trapframe *tf;       // Trap frame for the
                              // current interrupt
};
// From the snippet above, you can see a couple of important pieces of information the OS tracks about a process.
//  The register context will hold, for a stopped process, the contents of its registers.
//   When a process is stopped, its registers will be saved to this memory location; by restoring these registers 
//   (i.e., placing their values back into the actual physical registers), the OS can resume running the process. 

// You can also see from the snippet that there are some other states a process can be in,
//  beyond running, ready, and blocked. Sometimes a system will have an initial state that the process is in when it is being created. 
//  Also, a process could be placed in a final state where it has exited but has not yet been cleaned up (in UNIX-based systems, 
//  this is called the zombie state). 
//  This final state can be useful as it allows other processes (usually the parent that created the process) to examine the 
//  return code of the process and see if the just-finished process executed successfully (usually, 
//  programs return zero in UNIX-based systems when they have accomplished a task successfully, and non-zero otherwise). 
//  When finished, the parent will make one final call (e.g., wait()) to wait for the completion of the child,
//   and to also indicate to the OS that it can clean up any relevant data structures that referred to the now-extinct process.