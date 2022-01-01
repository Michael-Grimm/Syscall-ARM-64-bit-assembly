
/**
  System call 17
  int getCwd(char *buf, int buflen);  
  Stores the absolute pathname of the current working directory in the array
  pointed to by buf. buf has the size of buflen.
  Returns the size of the pathname.
  If the length of the absolute pathname exceeds buflen bytes, the negated value 
  (-34) of errno ERANGE is returned. 
  */
int getCwd(char *buf, int buflen);  
  
/**
  System call 56.
  int openAt(int dirfd, const char *pathname, int access_mode, ...);
  int openAt(int dirfd, const char *pathname, int access_mode, int permission_mode);
  Open/create a file for reading/writing...
  See: https://man7.org/linux/man-pages/man2/open.2.html
  
  The special value -100 in dirfd indicates that openat should use the current 
  working directory. This value can be found in:
  https://github.com/torvalds/linux/blob/master/include/uapi/linux/fcntl.h
  [#define AT_FDCWD -100"]
  
  Flags for access modes (read/write only...) are here: 
  https://github.com/torvalds/linux/blob/master/include/uapi/asm-generic/fcntl.h
  The values are in octal. 
  Examples:
  O_RDONLY	00000
  O_WRONLY	00001
  O_RDWR	00002
  O_CREAT	00100	 
  O_TRUNC	01000	 
  O_APPEND	02000
  ...
  O_DSYNC  010000
  ... 
  
  If the access mode contains O_CREAT (0100), the permission modes must be set.
  (the second function signature).
  Flags for the permission modes (rwx...) are in:
  https://github.com/torvalds/linux/blob/master/include/uapi/linux/stat.h
  The values of the flags are in octal (!): e.g. S_IRWXU = 0700, S_IRUSR 0400
  Values:
  octal binary permission
  0 	000 	none
  1 	001 	execute only
  2 	010 	write only
  3 	011 	write and execute
  4 	100 	read only
  5 	101 	read and execute
  6 	110 	read and write
  7 	111 	read, write, and execute (full permissions)
  Full permissions for user, group, others (read, write, execute): 0777
  Read+write for user, read only for group, no permissions for other: 0640
  
  On success, openat returns the new file descriptor (a nonnegative integer).
*/
  int openAt(int dirfd, const char *pathname, int access_mode, ...);
//int openAt(int dirfd, const char *pathname, int access_mode, int permission_mode);
  
/**
  System call 56.
  int openAtCwd(const char *pathname, int access_mode, ...);
  int openAtCwd(const char *pathname, int access_mode, int permission_mode);
  Open/create a file for reading/writing... in the current working directory.
  This is the same as int openat/create(-100, const char *path....).
 */
  int openAtCwd(const char *pathname, int access_mode, ...);
//int openAtCwd(const char *pathname, int access_mode, int permission_mode); 
 
/**
  Syscall 57
  int close(int fd);
  Closes a file descriptor, returns zero on success.
  See: https://man7.org/linux/man-pages/man2/close.2.html
*/
  int close(int fd);
 
/**
  Syscall 63
  int read(int fd, const char *buf, int count);
  Reads from a file into a buffer.
  If fd = 0, the in input is read from the keyboard (type ENTER ord CTRL-D 
  to finish input).
*/
  int read(int fd, const char *buf, int count);
 
/**
  Syscall 63
  int readIn(const char *buf, int count);
  Reads input from stdin into a buffer (type ENTER or CTRL-D to finish input).
  This is the same as int read(0, const char *buf, int count);
*/
  int readIn(const char *buf, int count);
 
/**
  Syscall 64
  int write(int fd, const char *buf, int count);
  Writes up to count bytes from the buffer starting at buf  to the file 
  referred to by the file descriptor fd. On success, the number of bytes 
  written is returned, otherwise a negative value (the negative errno). 
  If fd = 1, the output is directed to stdout.
  See: https://man7.org/linux/man-pages/man2/write.2.html
*/
  int write(int fd, const char *buf, int count);
  
/**
  Syscall 64
  int writeOut(const char *buf, int count)
  Writes up to count bytes from the buffer starting at buf to stdout. 
  On success, the number of bytes written is returned, otherwise a negative
  value (the negative errno). 
  This is the same as int write(1, const char *buf, int count); 
*/
  int writeOut(const char *buf, int count);

  
/**
  Syscall 64
  int writeZ(int fd, const char *asciiz);
  Writes a zero-terminated string to the file 
  referred to by the file descriptor fd. On success, the number of bytes 
  written is returned.
  If the char buffer 'asciiz' does not end with a zero, the result is 
  undetermined or can cause an error.
  If fd = 1, the output is directed to stdout.
 */
  int writeZ(int fd, const char *asciiz);

  
  
/**
  Syscall 64
  int writeZOut(const char *asciiz);
  Writes a zero-terminated string to stdout
  On success, the number of bytes 
  written is returned.
  If the char buffer 'asciiz' does not end with \0, the result is undetermined 
  or can cause an error.
 */
  int writeZOut(const char *asciiz);
  
  
/**
  Syscall 64
  int writeHex(int fd, long long value);
  int writeHexOut(long long value);
  Write the value in hexadecimal to a file or to stdout.
  On success, the number of bytes (16) written is returned, otherwise a negative
  value (the negative errno).  
*/
  int writeHex(int fd, long long value);
  int writeHexOut(long long value);
  
/**
  Syscall 64
  int newLine();
  writes a newline character to stdout.
  On success, the number of bytes (16) written is returned, otherwise a negative
  value (the negative errno).
*/
  int newLine();

/**
  Syscall 93
  noreturn void exit(int status);
  terminates the calling process.
  A status of zero signals the regular end of the process.
  See: https://man7.org/linux/man-pages/man2/exit.2.html
*/
  void exit(int status);
 
 
/**
  Syscall 169
  long long time[2];
  void getTimeOfDay(time);
  stores the number of seconds (in time[0]) and microseconds (in time[1]) since 
  the Epoch 1970-01-01 00:00:00 +0000 (UTC).
  See: https://man7.org/linux/man-pages/man2/gettimeofday.2.html
 */
 void getTimeOfDay(long long *time);
 
 /**
  Syscall 113
  long long getClockXXXXXXXX();
  The following functions retrieve the times of different clocks.
  See: https://man7.org/linux/man-pages/man3/clock_gettime.3.html
  Returns the time in nanoseconds (or a negative errno).
  */
 long long getClockRealtime();
 long long getClockRealtimeCoarse();
 long long getClockMonotonic();
 long long getClockMonotonicCoarse();
 long long getClockMonotonicRaw();
 long long getClockProcessCpuTime(); 
 long long getClockThreadCpuTime();
 long long getClockBootTime();
 
 
 /**
  Syscall 221
  extern char **environ;
  int execve(const char *filename, const char *const *argv,	const char *const *envp);
  See: https://man7.org/linux/man-pages/man2/execve.2.html
  */
  int execve(char *filename, char **argv,	char **envp);
 
 
  

 
 
#define PROT_READ	0x1		
#define PROT_WRITE	0x2		 
#define MAP_SHARED  0x1
//For other constants see: 
//https://github.com/torvalds/linux/blob/master/include/uapi/asm-generic/mman-common.h
//or ...asm-generic/mman.h

/**
 Syscall 222
 long long int mmap(long long *addr, int length, int prot, int flags, int fd, int offset);
 Creates a new shared mapping in the virtual address space of the calling process.
 Input: addr - hint for the starting address, if 0, kernel chooses the address 
               for the mapping
        length - the length of the mapping in bytes  > 0
        prot - desired memory protection of the mapping, not conflicting with 
               the open mode of the file. Constants; PROT_x
        flags - visibility of mapping for other processes etc., Constants: MAP_x
        fd - a valid filedescriptor
        offset - the offset in the file
 Returns the memory address of the mapping.
 See: https://man7.org/linux/man-pages/man2/mmap.2.html
 */  
 long long int mmap(long long *addr, int length, int prot, int flags, int fd, int offset);
  
  
 /**
 Syscall 222
 long long int mmap_rws(int fd, int length, int offset);
 Creates a new shared mapping with read/write access in the virtual address 
 space of the calling process.
 Input: fd - a valid filedescriptor referring to a file with read/write open mode.
        length - the length of the mapping in bytes > 0
        offset - the offset in the file
 The kernel chooses the page-aligned address at which to create the mapping.
 Returns the memory address of the mapping.
 See: https://man7.org/linux/man-pages/man2/mmap.2.html
 */ 
 long long int mmap_rws(int fd, int length, int offset); 
 
 /**
 Syscall 215
 int munmap(long long int address, int length); 
 Unmaps the mapping created with mmap
 Input: address - memory address of the mapping
        length - the length of the mapping in bytes
 Returns 0 or negative error number
 */
 int munmap(long long int address, int length); 
  
 /**
  Syscall 1071
  int vfork();
  See: https://man7.org/linux/man-pages/man2/vfork.2.html
  */
  int vfork();
   
