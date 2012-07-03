/*-
 * Copyright (c) 2008-2010 Robert N. M. Watson
 * All rights reserved.
 *
 * This software was developed at the University of Cambridge Computer
 * Laboratory with support from a grant from Google, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/* The following is a copy-and-paste from FreeBSD; uncommenting capabilities
 * as I use them.
 *
 * TODO(meredydd) these should definitely live elsewhere in the long term.
 */

/* General file I/O. */
#define CAP_NONE                0x0000000000000000ULL   /* None required */
#define CAP_READ                0x0000000000000001ULL   /* read/recv */
#define CAP_WRITE               0x0000000000000002ULL   /* write/send */
#define CAP_MMAP                0x0000000000000004ULL   /* mmap */
#define CAP_MAPEXEC             0x0000000000000008ULL   /* mmap(2) as exec */
#define CAP_FEXECVE             0x0000000000000010ULL
#define CAP_FSYNC               0x0000000000000020ULL
#define CAP_FTRUNCATE           0x0000000000000040ULL
#define CAP_SEEK                0x0000000000000080ULL

/* VFS methods. */
#define CAP_FCHFLAGS            0x0000000000000100ULL
#define CAP_FCHDIR              0x0000000000000200ULL
#define CAP_FCHMOD              0x0000000000000400ULL
#define CAP_FCHOWN              0x0000000000000800ULL
#define CAP_FCNTL               0x0000000000001000ULL
#define CAP_FPATHCONF           0x0000000000002000ULL
#define CAP_FLOCK               0x0000000000004000ULL
#define CAP_FSCK                0x0000000000008000ULL
#define CAP_FSTAT               0x0000000000010000ULL
#define CAP_FSTATFS             0x0000000000020000ULL
#define CAP_FUTIMES             0x0000000000040000ULL
#define CAP_CREATE              0x0000000000080000ULL
#define CAP_DELETE              0x0000000000100000ULL
#define CAP_MKDIR               0x0000000000200000ULL
#define CAP_RMDIR               0x0000000000400000ULL
#define CAP_MKFIFO              0x0000000000800000ULL

/* Lookups - used to constrain *at() calls. */
#define CAP_LOOKUP              0x0000000001000000ULL

/* Extended attributes. */
#define CAP_EXTATTR_DELETE      0x0000000002000000ULL
#define CAP_EXTATTR_GET         0x0000000004000000ULL
#define CAP_EXTATTR_LIST        0x0000000008000000ULL
#define CAP_EXTATTR_SET         0x0000000010000000ULL

/* Access Control Lists. */
/*#define CAP_ACL_CHECK           0x0000000020000000ULL
#define CAP_ACL_DELETE          0x0000000040000000ULL
#define CAP_ACL_GET             0x0000000080000000ULL
#define CAP_ACL_SET             0x0000000100000000ULL
*/

/* Socket operations. */
#define CAP_ACCEPT              0x0000000200000000ULL
#define CAP_BIND                0x0000000400000000ULL
#define CAP_CONNECT             0x0000000800000000ULL
#define CAP_GETPEERNAME         0x0000001000000000ULL
#define CAP_GETSOCKNAME         0x0000002000000000ULL
#define CAP_GETSOCKOPT          0x0000004000000000ULL
#define CAP_LISTEN              0x0000008000000000ULL
#define CAP_PEELOFF             0x0000010000000000ULL
#define CAP_SETSOCKOPT          0x0000020000000000ULL
#define CAP_SHUTDOWN            0x0000040000000000ULL

#define CAP_SOCK_ALL \
	(CAP_ACCEPT | CAP_BIND | CAP_CONNECT \
	    | CAP_GETPEERNAME | CAP_GETSOCKNAME | CAP_GETSOCKOPT \
	    | CAP_LISTEN | CAP_PEELOFF | CAP_SETSOCKOPT | CAP_SHUTDOWN)

/* Mandatory Access Control. */
/*#define CAP_MAC_GET             0x0000080000000000ULL
#define CAP_MAC_SET             0x0000100000000000ULL*/

/* Methods on semaphores. */
/*#define CAP_SEM_GETVALUE        0x0000200000000000ULL
#define CAP_SEM_POST            0x0000400000000000ULL
#define CAP_SEM_WAIT            0x0000800000000000ULL*/

/* kqueue events. */
/*#define CAP_POLL_EVENT          0x0001000000000000ULL
#define CAP_POST_EVENT          0x0002000000000000ULL*/

/* These rights are extremely powerful, and allow things of global scope. */
#define CAP_IOCTL               0x0004000000000000ULL
/*#define CAP_TTYHOOK             0x0008000000000000ULL*/

/* Process management via process descriptors. */
/*#define CAP_PDGETPID            0x0010000000000000ULL
#define CAP_PDWAIT              0x0020000000000000ULL
#define CAP_PDKILL              0x0040000000000000ULL*/

/* The mask of all valid method rights. */
/*#define CAP_MASK_VALID          0x007fffffffffffffULL*/
