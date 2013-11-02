/*
 * System call permission table for Capsicum, a capability API for UNIX.
 *
 * Copyright (C) 2012 The Chromium OS Authors <chromium-os-dev@chromium.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2, as
 * published by the Free Software Foundation.
 */
#include <linux/audit.h>
#include <linux/mman.h>
#include <linux/prctl.h>
#include <asm/prctl.h>

static int check_mmap(struct capsicum_pending_syscall *pending,
		      int arch, int call, unsigned long *args)
{
	int prot = args[2];
	int flags = args[3];
	int fd = args[4];

	if (flags & MAP_ANONYMOUS)
		return 0;

	if (flags & ~(MAP_SHARED|MAP_PRIVATE|MAP_32BIT|MAP_FIXED|MAP_HUGETLB
			|MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK))
		return -ECAPMODE;

	return require_rights(pending, fd, CAP_MMAP)
		?: ((prot & PROT_READ) ? require_rights(pending, fd, CAP_READ) : 0)
		?: ((prot & PROT_WRITE) ? require_rights(pending, fd, CAP_WRITE) : 0)
		?: ((prot & PROT_EXEC) ? require_rights(pending, fd, CAP_MAPEXEC) : 0);
}

int capsicum_run_syscall_table(struct capsicum_pending_syscall *pending,
			       int arch, int call, unsigned long *args)
{
	if (arch != AUDIT_ARCH_X86_64)
		return -ECAPMODE;

	switch (call) {
	case (__NR_accept):
		return require_rights(pending, args[0], CAP_ACCEPT);

	case (__NR_accept4):
		return require_rights(pending, args[0], CAP_ACCEPT);

	case (__NR_sendto):
		return require_rights(pending, args[0], CAP_WRITE
					| (((void *)args[4] != NULL) ? CAP_CONNECT : 0));

	case (__NR_sendmsg):
		return require_rights(pending, args[0], CAP_WRITE | CAP_CONNECT);

	case (__NR_sendfile):
		return require_rights(pending, args[0], CAP_READ)
			?: require_rights(pending, args[1], CAP_WRITE);

	case (__NR_fremovexattr):
		return require_rights(pending, args[0], CAP_EXTATTR_DELETE);

	case (__NR_fgetxattr):
		return require_rights(pending, args[0], CAP_EXTATTR_GET);

	case (__NR_flistxattr):
		return require_rights(pending, args[0], CAP_EXTATTR_LIST);

	case (__NR_fsetxattr):
		return require_rights(pending, args[0], CAP_EXTATTR_SET);

	case (__NR_fchmod):
		return require_rights(pending, args[0], CAP_FCHMOD);

	case (__NR_fchown):
		return require_rights(pending, args[0], CAP_FCHOWN);

	case (__NR_fcntl):
		return require_rights(pending, args[0], CAP_FCNTL);

	case (__NR_flock):
		return require_rights(pending, args[0], CAP_FLOCK);

	case (__NR_fstat):
		return require_rights(pending, args[0], CAP_FSTAT);

	case (__NR_fstatfs):
		return require_rights(pending, args[0], CAP_FSTATFS);

	case (__NR_fsync):
		return require_rights(pending, args[0], CAP_FSYNC);

	case (__NR_sync):
		return 0;

	case (__NR_fdatasync):
		return require_rights(pending, args[0], CAP_FSYNC);

	case (__NR_ftruncate):
		return require_rights(pending, args[0], CAP_FTRUNCATE);

	case (__NR_utimensat):
		return require_rights(pending, args[0], CAP_FUTIMES
					| (((void *)args[1] != NULL) ? CAP_LOOKUP : 0));

	case (__NR_getpeername):
		return require_rights(pending, args[0], CAP_GETPEERNAME);

	case (__NR_getsockname):
		return require_rights(pending, args[0], CAP_GETSOCKNAME);

	case (__NR_getsockopt):
		return require_rights(pending, args[0], CAP_GETSOCKOPT);

	case (__NR_ioctl):
		return require_rights(pending, args[0], CAP_IOCTL);

	case (__NR_listen):
		return require_rights(pending, args[0], CAP_LISTEN);

	case (__NR_openat):
		return require_rights(pending, args[0], CAP_LOOKUP
					| (args[2] & O_WRONLY ? CAP_WRITE : CAP_READ)
					| (args[2] & O_RDWR ? CAP_READ|CAP_WRITE : 0)
					| (args[2] & O_CREAT ? CAP_WRITE : 0)
					| (args[2] & O_EXCL ? CAP_WRITE : 0)
					| (args[2] & O_TRUNC ? CAP_WRITE : 0))
			?: (args[2] & ~(O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_TRUNC|O_APPEND|FASYNC|O_CLOEXEC|O_DIRECT|O_DIRECTORY|O_LARGEFILE|O_NOATIME|O_NOCTTY|O_NOFOLLOW|O_NONBLOCK|O_SYNC) ? -ECAPMODE : 0);

	case (__NR_faccessat):
		return require_rights(pending, args[0], CAP_LOOKUP);

	case (__NR_fchmodat):
		return require_rights(pending, args[0], CAP_LOOKUP|CAP_FCHMOD);

	case (__NR_fchownat):
		return require_rights(pending, args[0], CAP_LOOKUP|CAP_FCHOWN);

	case (__NR_newfstatat):
		return require_rights(pending, args[0], CAP_LOOKUP|CAP_FSTAT);

	case (__NR_futimesat):
		return require_rights(pending, args[0], CAP_LOOKUP|CAP_FUTIMES);

	case (__NR_linkat):
		return require_rights(pending, args[0], CAP_LOOKUP)
			?: require_rights(pending, args[2], CAP_LOOKUP|CAP_CREATE);

	case (__NR_mkdirat):
		return require_rights(pending, args[0], CAP_LOOKUP|CAP_MKDIR);

	case (__NR_readlinkat):
		return require_rights(pending, args[0], CAP_LOOKUP|CAP_READ);

	case (__NR_renameat):
		return require_rights(pending, args[0], CAP_LOOKUP|CAP_DELETE)
			?: require_rights(pending, args[2], CAP_LOOKUP|CAP_CREATE);

	case (__NR_symlinkat):
		return require_rights(pending, args[1], CAP_LOOKUP|CAP_CREATE);

	case (__NR_unlinkat):
		return require_rights(pending, args[0], CAP_LOOKUP|CAP_DELETE);

	case (__NR_getdents):
		return require_rights(pending, args[0], CAP_READ|CAP_SEEK);

	case (__NR_mmap):
		return check_mmap(pending, arch, call, args);

	case (__NR_munmap):
		return 0;

	case (__NR_mlock):
		return 0;

	case (__NR_munlock):
		return 0;

	case (__NR_mlockall):
		return 0;

	case (__NR_munlockall):
		return 0;

	case (__NR_mprotect):
		return 0;

	case (__NR_msync):
		return 0;

	case (__NR_madvise):
		return 0;

	case (__NR_mincore):
		return 0;

	case (__NR_pread64):
		return require_rights(pending, args[0], CAP_READ);

	case (__NR_preadv):
		return require_rights(pending, args[0], CAP_READ);

	case (__NR_readv):
		return require_rights(pending, args[0], CAP_READ);

	case (__NR_read):
		return require_rights(pending, args[0], CAP_READ|CAP_SEEK);

	case (__NR_recvfrom):
		return require_rights(pending, args[0], CAP_READ);

	case (__NR_recvmsg):
		return require_rights(pending, args[0], CAP_READ);

	case (__NR_lseek):
		return require_rights(pending, args[0], CAP_SEEK);

	case (__NR_setsockopt):
		return require_rights(pending, args[0], CAP_SETSOCKOPT);

	case (__NR_shutdown):
		return require_rights(pending, args[0], CAP_SHUTDOWN);

	case (__NR_write):
		return require_rights(pending, args[0], CAP_WRITE|CAP_SEEK);

	case (__NR_pwrite64):
		return require_rights(pending, args[0], CAP_WRITE);

	case (__NR_pwritev):
		return require_rights(pending, args[0], CAP_WRITE);

	case (__NR_writev):
		return require_rights(pending, args[0], CAP_WRITE);

	case (__NR_dup):
		return 0;

	case (__NR_dup2):
		return 0;

	case (__NR_dup3):
		return 0;

	case (__NR_pipe):
		return 0;

	case (__NR_pipe2):
		return 0;

	case (__NR_uname):
		return 0;

	case (__NR_setsid):
		return 0;

	case (__NR_setuid):
		return 0;

	case (__NR_setgid):
		return 0;

	case (__NR_setfsuid):
		return 0;

	case (__NR_setfsgid):
		return 0;

	case (__NR_setreuid):
		return 0;

	case (__NR_setregid):
		return 0;

	case (__NR_setresuid):
		return 0;

	case (__NR_setresgid):
		return 0;

	case (__NR_brk):
		return 0;

	case (__NR_prctl):
		/* Allow through PR_GET_* calls */
		switch (args[0]) {
		case PR_CAPBSET_READ:
		case PR_CAPBSET_DROP:
		case PR_GET_DUMPABLE:
		case PR_GET_ENDIAN:
		case PR_GET_FPEMU:
		case PR_GET_KEEPCAPS:
		case PR_GET_NAME:
		case PR_GET_NO_NEW_PRIVS:
		case PR_GET_PDEATHSIG:
		case PR_GET_SECCOMP:
		case PR_GET_SECUREBITS:
		case PR_GET_TIMERSLACK:
		case PR_GET_TIMING:
		case PR_GET_TSC:
		case PR_GET_UNALIGN:
		case PR_MCE_KILL_GET:
			return 0;
		default:
			return -ECAPMODE;
		}

	case (__NR_arch_prctl):
		return (args[0] & ~(ARCH_SET_FS|ARCH_GET_FS|ARCH_SET_GS|ARCH_GET_GS) ? -ECAPMODE : 0);

	case (__NR_rt_sigaction):
		return 0;

	case (__NR_sigaltstack):
		return 0;

	case (__NR_fexecve):
		return require_rights(pending, args[0], CAP_FEXECVE);

	case (__NR_clone):
		return 0;

	case (__NR_fork):
		return 0;

	case (__NR_vfork):
		return 0;

	case (__NR_pdfork):
		return (args[1] & ~(0) ? -ECAPMODE : 0);

	case (__NR_pdkill):
		return 0;

	case (__NR_close):
		return 0;

	case (__NR_cap_new):
		return 0;

	case (__NR_cap_getrights):
		return 0;

	case (__NR_clock_getres):
		return 0;

	case (__NR_clock_gettime):
		return 0;

	case (__NR_exit):
		return 0;

	case (__NR_exit_group):
		return 0;

	case (__NR_getsid):
		return 0;

	case (__NR_getpid):
		return 0;

	case (__NR_getppid):
		return 0;

	case (__NR_getgid):
		return 0;

	case (__NR_getegid):
		return 0;

	case (__NR_getuid):
		return 0;

	case (__NR_geteuid):
		return 0;

	case (__NR_getpgid):
		return 0;

	case (__NR_getpgrp):
		return 0;

	case (__NR_getresgid):
		return 0;

	case (__NR_getresuid):
		return 0;

	case (__NR_getgroups):
		return 0;

	case (__NR_getitimer):
		return 0;

	case (__NR_setitimer):
		return 0;

	case (__NR_getpriority):
		return 0;

	case (__NR_setpriority):
		return 0;

	case (__NR_getrlimit):
		return 0;

	case (__NR_setrlimit):
		return 0;

	case (__NR_getrusage):
		return 0;

	case (__NR_gettimeofday):
		return 0;

	case (__NR_mknodat):
		return require_rights(pending, args[0], CAP_MKFIFO);

	case (__NR_nanosleep):
		return 0;

	case (__NR_sched_getparam):
		return 0;

	case (__NR_sched_get_priority_max):
		return 0;

	case (__NR_sched_get_priority_min):
		return 0;

	case (__NR_sched_getscheduler):
		return 0;

	case (__NR_sched_rr_get_interval):
		return 0;

	case (__NR_sched_setparam):
		return 0;

	case (__NR_sched_setscheduler):
		return 0;

	case (__NR_sched_yield):
		return 0;

	default:
		return -ECAPMODE;
	}
}
