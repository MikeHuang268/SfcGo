#ifndef __HCH_COMPLIE_ON_WIN__
#define __HCH_COMPLIE_ON_WIN__



#ifdef WIN32

#ifdef __cplusplus
extern "C" {
#endif

//����һЩwindows��û�еĺ����������ͣ�������vs��д����
typedef int pid_t;
typedef long key_t;
typedef unsigned long msgqnum_t;
typedef unsigned long msglen_t;
typedef unsigned int uint32_t;

typedef unsigned uid_t;
typedef unsigned gid_t;

#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <io.h>
#include <WinSock2.h>
#include <sys/stat.h>

#define __U32_TYPE            unsigned int
//typedef __U32_TYPE socklen_t;


struct ipc_perm
{
    int __key;
    int uid;
    int gid;
    int cuid;
    int cgid;
    unsigned short mode;
    unsigned short __pad1;
    unsigned short __seq;
    unsigned short __pad2;
    unsigned short __unused1;
    unsigned short __unused2;
};


/* semop flags */
#define SEM_UNDO        0x1000  /* undo the operation on exit */

/* semctl Command Definitions. */
#define GETPID  11       /* get sempid */
#define GETVAL  12       /* get semval */
#define GETALL  13       /* get all semval's */
#define GETNCNT 14       /* get semncnt */
#define GETZCNT 15       /* get semzcnt */
#define SETVAL  16       /* set semval */
#define SETALL  17       /* set all semval's */

/* ipcs ctl cmds */
#define SEM_STAT 18
#define SEM_INFO 19

struct shmid_ds {
    struct ipc_perm shm_perm;
    int shm_segsz;
    time_t shm_atme;
    time_t shm_dtime;
    time_t shm_ctime;
    pid_t shm_cpid;
    pid_t shm_lpid;
    unsigned short shm_nattch;
    unsigned short shm_unused;
    void *shm_unused2;
    void *shm_unused3;
};

struct tms
{
    clock_t tms_utime;
    clock_t tms_stime;
    clock_t tms_cutime;
    clock_t tms_cstime;
};

/* Structure used for argument to `semop' to describe operations.  */
struct sembuf
{
    unsigned short int sem_num;   /* semaphore number */
    short int sem_op;             /* semaphore operation */
    short int sem_flg;            /* operation flag */
};

int semop(int semid, struct sembuf *sops, unsigned nsops);

           struct msginfo {
                      int msgpool; /* Size in kibibytes of buffer pool
                                      used to hold message data;
                                      unused within kernel */
                      int msgmap;  /* Maximum number of entries in message
                                      map; unused within kernel */
                      int msgmax;  /* Maximum number of bytes that can be
                                      written in a single message */
                      int msgmnb;  /* Maximum number of bytes that can be
                                      written to queue; used to initialize
                                      msg_qbytes during queue creation
                                      (msgget(2)) */
                      int msgmni;  /* Maximum number of message queues */
                      int msgssz;  /* Message segment size;
                                      unused within kernel */
                      int msgtql;  /* Maximum number of messages on all queues
                                      in system; unused within kernel */
                      unsigned short int msgseg;
                                   /* Maximum number of segments;
                                      unused within kernel */
                  };
                  
           struct msqid_ds {
               struct ipc_perm msg_perm;     /* Ownership and permissions */
               time_t          msg_stime;    /* Time of last msgsnd(2) */
               time_t          msg_rtime;    /* Time of last msgrcv(2) */
               time_t          msg_ctime;    /* Time of last change */
               unsigned long   __msg_cbytes; /* Current number of bytes in
                                                queue (nonstandard) */
               msgqnum_t       msg_qnum;     /* Current number of messages
                                                in queue */
               msglen_t        msg_qbytes;   /* Maximum number of bytes
                                                allowed in queue */
               pid_t           msg_lspid;    /* PID of last msgsnd(2) */
               pid_t           msg_lrpid;    /* PID of last msgrcv(2) */
           };

//          struct ipc_perm {
//              key_t          __key;       /* Key supplied to msgget(2) */
//              uid_t          uid;         /* Effective UID of owner */
//              gid_t          gid;         /* Effective GID of owner */
//              uid_t          cuid;        /* Effective UID of creator */
//              gid_t          cgid;        /* Effective GID of creator */
//              unsigned short mode;        /* Permissions */
//              unsigned short __seq;       /* Sequence number */
//          };
           
           int msgctl(int msqid, int cmd, struct msqid_ds *buf);
           
int kill(pid_t, int);
unsigned sleep(int);
unsigned usleep(int);
pid_t wait (int *);
pid_t fork();
pid_t getpid();
int pipe(int *fd);
int getpgrp();
int killpg(int, int);
int gettimeofday(struct timeval *tp, void *tzp);
int random();
void srandom(unsigned int seed);
key_t ftok(const char *path_name, int proj_id);

int shmget(key_t key, size_t size, int shmflg);
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
void *shmat(int shmid, const void *shmaddr, int shmflg);
int shmdt(const void *shmaddr);

int msgget(key_t key, int msgflg);
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
size_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);

void *dlopen(const char *filename, int flag);
int dlclose(void *handle);
char *dlerror();
void *dlsym(void *hadle, const char *symbol);
unsigned int alarm(unsigned int seconds);
// int dup(int oldfd);
// int dup2(int oldfd, int newfd);

int mkdir(const char *path, int mode);

char *strsep(char **stringp, const char *delim);

#define dup2 _dup2

#define open _open
#define read _read
#define close _close
#define write _write

typedef void (*sighandler_t)(int);

sighandler_t sigset(int sig, sighandler_t disp);

int sighold(int sig);

int sigrelse(int sig);

int sigignore(int sig);


clock_t times(struct tms *buf);
#ifdef __cplusplus
}
#endif

#define snprintf _snprintf
#define popen _popen
#define pclose _pclose

//�źų���
/*
const int SIGHUP    = 15;
const int SIGQUIT    = 15;
const int SIGPWR    = 15;
const int SIGUSR2    = 15;
const int SIGALRM    = 15;

const int SIGUSR1 = 10; 
const int SIGURG = 30; 
const int SIGCHLD = 17;
const int SIGPIPE = 13;
*/
#ifndef RTLD_LAZY
#define  RTLD_LAZY 1
#endif
#ifndef EINTR
#define EINTR 4
#endif

#define SIGHUP 1
#define SIGINT 2
#define SIGQUIT 3
#define SIGILL 4
#define SIGTRAP 5
#ifndef SIGABRT
#define SIGABRT 6
#endif
#define SIGIOT 6
#define SIGBUS 7
#define SIGEPE 8
#define SIGKILL 9
#define SIGUSR1 10
#define SIGSEGV 11
#define SIGUSR2 12
#define SIGPIPE 13
#define SIGALRM 14
#define SIGTERM 15
#define SIGSTKFLT 16
#define SIGCHLD 17
#define SIGCLD SIGCHLD
#define SIGCONT 18
#define SIGSTOP 19
#define SIGTSTP 20
#define SIGTTIN 21
#define SIGTTOU 22
#define SIGURG 23
#define SIGXCPU 24
#define SIGXFSZ 25
#define SIGVTALRM 26
#define SIGPROF 27
#define SIGWINCH 28
#define SIGIO 29
#define SIGPWR 30
#define SIGSYS 31
#define SIGUNUSED 31
#define SIGRTMIN 32

#ifndef SIGEMT
#define SIGEMT 1122
#endif

#define R_OK 4
#define W_OK 2
#define X_OK 1
#define F_OK 0

#define IPC_STAT 0
#define IPC_SET 1
#define IPC_RMID 2

#define IPC_CREAT 01000
#define IPC_EXCL  02000
#define IPC_NOWAIT 00004000   /* return error on wait */
//#define IPC_RMID  0

#define SHM_RDONLY 010000

#define WNOHANG 0x00000001

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define close _close //����warning C4996����
#define access _access //����warning C4996����

void herror(const char *s); //gethostbyname����ʱ����
void bzero(void *s, size_t n);

#ifndef WIFEXITED
#define WIFEXITED(status)    (((status) & 0xff) == 0)
#endif /* !defined WIFEXITED */
#ifndef WEXITSTATUS
#define WEXITSTATUS(status)    (((status) >> 8) & 0xff)
#endif /* !defined WEXITSTATUS */
#ifndef WIFSIGNALED 
#define WIFSIGNALED(X) ((((X) & 255) != 0x255 && ((X) & 255) != 0)) 
#endif /* !defined WIFSIGNALED */
#ifndef WTERMSIG 
#define WTERMSIG(X) ((X) & 255) 
#endif /* !defined WTERMSIG */

struct  sockaddr_un {
    short   sun_family;             /* AF_UNIX */
    char    sun_path[108];          /* path name (gag) */
};


#endif //WIN32

/*����绰֧���ر����*/
#ifdef WIN32
/*�����������ڴ�Ĵ�С*/
#ifdef GR_SHM_SIZE
#undef GR_SHM_SIZE
#endif

#define GR_SHM_SIZE     2048 + ( sizeof( DEVINFO ) * 2048 ) + ( sizeof( SOCKINFO ) * 256 )
#define ATMINFO_OFFSET  2048
#define DEVINFO_OFFSET  2048
#define SOCKINFO_OFFSET ATMINFO_OFFSET + sizeof( DEVINFO ) * 2048

/*����ǰ�û�����Ϣ��ֵ*/
#define KEYGET(A)       ftok( getenv( "HOME" ), A )

#define SHM_KEY         KEYGET( 10 )    /*ǰ�û��������Ĺ����ڴ�ļ�ֵ*/

#define CRD_KEY         KEYGET( 11 )    /*C�˶����еļ�ֵ -- ָǰ�˵��ȳ������*/
#define CWT_KEY         KEYGET( 12 )    /*C��д���еļ�ֵ -- ָǰ�˵��ȳ������*/
#define HRD_KEY         KEYGET( 13 )    /*H�˶����еļ�ֵ -- ָ��̨���ȳ������*/
#define HWT_KEY         KEYGET( 14 )    /*H��д���еļ�ֵ -- ָ��̨���ȳ������*/

#define MON_KEY         KEYGET( 15 )    /*Unix������ʾ���еļ�ֵ*/
#define TRN_MON_KEY     KEYGET( 16 )    /*�����Ϣ���ͷ�����еļ�ֵ*/
#define TRN_SHM_KEY     KEYGET( 17 )    /*�����Ϣ���ͷ������ڴ�ļ�ֵ*/

#define SHM_DICT_KEY    KEYGET( 18 )    /*�����ֵ�Ĺ����ڴ�ļ�ֵ*/
#define FIREWALL_KEY    KEYGET( 19 )    /*����ǽ��־�ļ�ֵ*/

#define CPROC_ID        KEYGET( 0  )    /*�ö˴���ϵͳ�ģɣģ�������*/
#define KPROC_ID        KEYGET( 1  )    /*�˶˴���ϵͳ�ģɣģ��������У�����û��*/
#define HPROC_ID        KEYGET( 2  )    /*�ȶ˴���ϵͳ�ģɣģ�������*/
#define MONITOR_ID      KEYGET( 3  )    /*�գ�����صģɣģ����п���*/
#define MONCLI_ID       KEYGET( 4  )    /*����ת��ϵͳ�ģɣģ����п���*/
#define SYSSEMP_KEY     KEYGET( 30 )    /*����ϵͳ�ź����ļ�ֵ*/

#define CRE_SHM_KEY     KEYGET( 40 )    /*�������ĵĹ����ڴ�ļ�ֵ*/
#define CLI_MON_KEY     KEYGET( 41 )    /*�������Ķ��еļ�ֵ*/

/*����ǰ�û�ϵͳXML�Ĺ̶�·���Ķ��壬�ض���ģ��������ļ�������Ϊ��ģ��������д��ĸ��ԭ����+��.XML��*/
#define DBGFLG          KEYGET( 127 )     /*������Ϣ�趨*/
#define SERVINFO_KEY    KEYGET( 126 )     /*ϵͳ��Ϣ*/
#define SERVINFO_SIZE   8192              /*���Ϊ255����Ϣ*/
#define DEVINFO_KEY     KEYGET( 125 )     /*�豸������Ϣ*/
#define SOCKINFO_KEY    KEYGET( 124 )     /*SOCKINFO��Ϣ�����ڳ�������*/
#define ACCESS_SN_KEY   KEYGET( 123 )     /*����ƽ̨��ˮ��KEY�������ź���*/
#define DEVINFO_SIZE    sizeof( DEVINFO ) * 2048
#define SOCKINFO_SIZE   sizeof( SOCKINFO ) * 256

/*����ƽ̨�¼ӵĶ���*/
#define DBGFILE         "GR_DEBUG_FILE"        /*ȱʡ�ĵ�����Ϣ�ļ�*/
#define GRSYSCONF       "GR_SYS_CONF"       /*ϵͳ����·���Ļ�������*/
#define GRDBGCONF       "GR_DEBUG_PATH"     /*������Ϣ���·���Ļ�������*/
#define GRLOGCONF       "GR_LOG_PATH"       /*LOG��־��ŵ�·���Ļ�������*/
#define TRTMP           "GR_TMP_PATH"       /*������ʱ�ļ���·��*/
#define GRFILE          "GR_FILES"          /*�ļ����ڵ�·��*/
#define GRBKFILE        "GR_BACKFILE"       /*�����ļ����ڵ�·��*/

/*��ǿ�͵�����Ϣ*/
#define DBGOPEN         "GR_DEBUG_ON"       /*������Ϣ�Ƿ���0������*/
#define LOGOPEN         "GR_LOG_ON"         /*������Ϣ�Ƿ���0������*/
#define DBGLEVEL        "GR_DEBUG_LEVEL"    /*���������Ϣ�ļ���Ĭ�ϵ������Ϊ5����5��������е���Ϣ������ԭ���ĵ��Գ���*/
#define DBGL1FILE        "GR_DEBUG_L1"        /*���������Ϣһ�����ļ���*/
#define DBGL2FILE        "GR_DEBUG_L2"        /*���������Ϣ�������ļ���*/
#define DBGL3FILE        "GR_DEBUG_L3"        /*���������Ϣ�������ļ���*/
#define DBGL4FILE        "GR_DEBUG_L4"        /*���������Ϣ�ļ����ļ���*/
#define DBGL5FILE        "GR_DEBUG_L5"        /*���������Ϣ�弶���ļ���*/
/*#define WRITEBYDAY      "WRITEBYDAY"  */      /*�������������Ϣ*/

#define LOGLEVEL        "GR_LOG_LEVEL"      /*����LOG�ļ���*/
#define LOGL1FILE       "GR_LOG_L1"         /*����LOG��һ���ļ���*/
#define LOGL2FILE       "GR_LOG_L2"         /*����LOG�Ķ����ļ���*/
#define LOGL3FILE       "GR_LOG_L3"         /*����LOG�������ļ���*/
#define LOGL4FILE       "GR_LOG_L4"         /*����LOG���ļ��ļ���*/
#define LOGL5FILE       "GR_LOG_L5"         /*����LOG���弶�ļ���*/

/*����ϵͳ�й̶�������Ϣ�Ľڵ���*/
#define CFGROOT         "<GR>"              /*�����е������ļ��еĸ����*/
#define BRDADDR         "<BroadCastAddr>"  /*�㲥��ַ*/
#define BRDNAME         "<BroadName>"      /*�󶨹㲥�˿ڵķ���������/etc/services�����õ�����*/
#define SVRADDR         "<SvrAddr>"        /*���ױ�����Ҫд���IP��ַ����ģ���ͨѶ��IP��ַ*/
#define SVRPORT         "<SvrPort>"        /*���ױ��ļ���Ҫд��Ķ˿ڣ���ģ���ͨѶ�Ķ˿�*/
#define SVRTIMEOUT      "<SvrTimeOut>"     /*Server��д��ʱ����λΪ��*/
#define CLITIMEOUT      "<ClrTimeOut>"     /*Client��д��ʱ����λΪ��*/
#define SVRIDLE         "<SvrIDLETime>"    /*�����ʱ�䣬��λΪ��*/
#define CLIIDLE         "<CliIDLETime>"    /*Client�����ʱ�䣬��λΪ��*/
#define LNKSTYLE        "<LinkStyle>"      /*������������·��ʽ*/
#define ILLEGAL         "<NoneIP>"         /*�Ƿ��Ľ���*/
#define REFUSES         "<NotAllow>"       /*���������Ĵ���*/
#define SHMLOAD         "<ShmFile>"        /*װ�빲���ڴ���ļ���*/
#define FIXEDKEY        "<FixedKey>"       /*�̶�����Կ*/
#define LNCHKTIME       "<LnChkTime>"      /*��·���ʱ��*/

/*�ػ�������ʹ�õĲ���*/
#define SRVNAME         "<ServicesName>"    /*ǰ�û��󶨷���˿ڵķ���������/etc/services�����õ�����*/
#define FIREWALLEN      "<FireWallEnabled>"/*����ǽʹ�ܣ�1Ϊ�ܣ�0Ϊ����*/
#define MAXLNKCNT       "<MaxLinkCount>"   /*����������Ĭ��ֵΪ512����󲻳���2048*/
#define SOCKSEND        "<SockSendVal>"    /*ͨѶ��SOCKET�Ƿ񰴴�ֵ�����ӽ���*/
#define SCHEDULERFLG    "<SchFlag>"        /*�Ƿ����õ��ȳ�ʽ��־*/
#define SCHEDULERNAM    "<SchName>"        /*���Ƚ��̵�����*/

/*���׵���ϵͳ���õĲ��� CScheduler.c���õ�����Ϣ*/
#define SNDMON          "<Datagram>/<MonTag>"       /*�Ƿ������*/
#define CODESW          "<Datagram>/<DgCodeChg>"    /*�ַ���ת��ģʽ*/
#define CODEDLL         "<Datagram>/<DgExtChgLib>"  /*����ת����ʽ�Ŀ���*/

#define DGTYPE          "<Datagram>/<DgType>"       /*��������*/
#define DGHDLEN         "<Datagram>/<DgHeadLen>"    /*����ͷ����*/
#define DGVERIFY        "<Datagram>/<DgVerify>"     /*����ͷ�Ƿ���֤*/
#define DGCONFIRM       "<Datagram>/<DgConfirm>"    /*����ͷ��֤��Ϣ*/
#define DGLNSTA         "<Datagram>/<DgLenStyle>"   /*���ĳ��ȱ�ʶ*/
#define DGFLAG          "<Datagram>/<DgFlag>"       /*���ľ���Ϣ���糤�ȡ���������*/
#define TRSTYLE         "<Datagram>/<TrStyle>"      /*��������ص�*/
#define TRPOS           "<Datagram>/<TrStartPos>"   /*���������ʼλ��*/
#define TRLEN           "<Datagram>/<TrCodeLen>"    /*������ĳ���*/

#define COMMTYPE        "<COMMTYPE%d>"              /*����ͨѶ����*/

/*---------TransInfo----------*/
#define ANSTYPE         "<T%s>/<MustAnswer>"        /*�˽����Ƿ���뷵������*/
#define ANSTRCODE       "<T%s>/<AnswerCode>"        /*���׵�Ӧ������*/
#define ANSRTNAME       "<T%s>/<RootName>"          /*Ӧ���׵�XML���ĵĸ��ڵ�*/
#define TRPROC          "<T%s>/<Proc>"              /*���׺���ģ��ĺ�����*/
#define TRCORR          "<T%s>/<AutoCorection>"     /*�Զ�������־*/
#define TSWLIB          "<T%s>/<TSWLib>"            /*���״���Ķ�̬����*/
#define TRCRPROC        "<T%s>/<CorProc>"           /*�����Զ������ĺ�����*/

#define MKNODE( BUFF, NODE, TRANS ) sprintf( BUFF, NODE, TRANS ) /*���콻����Ϣ�ڵ���*/

#if 0
struct timeb
{
    time_t time;
    unsigned short millitm;
    short timezone;
    short dstflag;
};

int ftime(struct timeb *tp);
#endif


# define FAPPEND        O_APPEND
# define FFSYNC         O_FSYNC
# define FASYNC         O_ASYNC
# define FNONBLOCK      O_NONBLOCK
# define FNDELAY        O_NDELAY


#ifndef _ASM_GENERIC_FCNTL_H
#define _ASM_GENERIC_FCNTL_H

/*
 * FMODE_EXEC is 0x20
 * FMODE_NONOTIFY is 0x1000000
 * These cannot be used by userspace O_* until internal and external open
 * flags are split.
 * -Eric Paris
 */

/*
 * When introducing new O_* bits, please check its uniqueness in fcntl_init().
 */

#define O_ACCMODE       00000003
#define O_RDONLY        00000000
#define O_WRONLY        00000001
#define O_RDWR          00000002
#ifndef O_CREAT
#define O_CREAT         00000100        /* not fcntl */
#endif
#ifndef O_EXCL
#define O_EXCL          00000200        /* not fcntl */
#endif
#ifndef O_NOCTTY
#define O_NOCTTY        00000400        /* not fcntl */
#endif
#ifndef O_TRUNC
#define O_TRUNC         00001000        /* not fcntl */
#endif
#ifndef O_APPEND
#define O_APPEND        00002000
#endif
#ifndef O_NONBLOCK
#define O_NONBLOCK      00004000
#endif
#ifndef O_DSYNC
#define O_DSYNC         00010000        /* used to be O_SYNC, see below */
#endif
#ifndef FASYNC
#define FASYNC          00020000        /* fcntl, for BSD compatibility */
#endif
#ifndef O_DIRECT
#define O_DIRECT        00040000        /* direct disk access hint */
#endif
#ifndef O_LARGEFILE
#define O_LARGEFILE     00100000
#endif
#ifndef O_DIRECTORY
#define O_DIRECTORY     00200000        /* must be a directory */
#endif
#ifndef O_NOFOLLOW
#define O_NOFOLLOW      00400000        /* don't follow links */
#endif
#ifndef O_NOATIME
#define O_NOATIME       01000000
#endif
#ifndef O_CLOEXEC
#define O_CLOEXEC       02000000        /* set close_on_exec */
#endif

/*
 * Before Linux 2.6.33 only O_DSYNC semantics were implemented, but using
 * the O_SYNC flag.  We continue to use the existing numerical value
 * for O_DSYNC semantics now, but using the correct symbolic name for it.
 * This new value is used to request true Posix O_SYNC semantics.  It is
 * defined in this strange way to make sure applications compiled against
 * new headers get at least O_DSYNC semantics on older kernels.
 *
 * This has the nice side-effect that we can simply test for O_DSYNC
 * wherever we do not care if O_DSYNC or O_SYNC is used.
 *
 * Note: __O_SYNC must never be used directly.
 */
#ifndef O_SYNC
#define __O_SYNC        04000000
#define O_SYNC          (__O_SYNC|O_DSYNC)
#endif

#ifndef O_PATH
#define O_PATH          010000000
#endif

#ifndef O_NDELAY
#define O_NDELAY        O_NONBLOCK
#endif

#define F_DUPFD         0       /* dup */
#define F_GETFD         1       /* get close_on_exec */
#define F_SETFD         2       /* set/clear close_on_exec */
#define F_GETFL         3       /* get file->f_flags */
#define F_SETFL         4       /* set file->f_flags */
#ifndef F_GETLK
#define F_GETLK         5
#define F_SETLK         6
#define F_SETLKW        7
#endif
#ifndef F_SETOWN
#define F_SETOWN        8       /* for sockets. */
#define F_GETOWN        9       /* for sockets. */
#endif
#ifndef F_SETSIG
#define F_SETSIG        10      /* for sockets. */
#define F_GETSIG        11      /* for sockets. */
#endif

#ifndef CONFIG_64BIT
#ifndef F_GETLK64
#define F_GETLK64       12      /*  using 'struct flock64' */
#define F_SETLK64       13
#define F_SETLKW64      14
#endif
#endif

#ifndef F_SETOWN_EX
#define F_SETOWN_EX     15
#define F_GETOWN_EX     16
#endif

#ifndef F_GETOWNER_UIDS
#define F_GETOWNER_UIDS 17
#endif

#define F_OWNER_TID     0
#define F_OWNER_PID     1
#define F_OWNER_PGRP    2


/* for F_[GET|SET]FL */
#define FD_CLOEXEC      1       /* actually anything with low bit set goes */

/* for posix fcntl() and lockf() */
#ifndef F_RDLCK
#define F_RDLCK         0
#define F_WRLCK         1
#define F_UNLCK         2
#endif

struct flock {
    short   l_type;
    short   l_whence;
    size_t  l_start;
    size_t  l_len;
    size_t  l_pid;
};

/* for old implementation of bsd flock () */
#ifndef F_EXLCK
#define F_EXLCK         4       /* or 3 */
#define F_SHLCK         8       /* or 4 */
#endif

/* operations for bsd flock(), also used by the kernel implementation */
#define LOCK_SH         1       /* shared lock */
#define LOCK_EX         2       /* exclusive lock */
#define LOCK_NB         4       /* or'd with one of the above to prevent
                                   blocking */
#define LOCK_UN         8       /* remove lock */

#define LOCK_MAND       32      /* This is a mandatory flock ... */
#define LOCK_READ       64      /* which allows concurrent read operations */
#define LOCK_WRITE      128     /* which allows concurrent write operations */
#define LOCK_RW         192     /* which allows concurrent read & write ops */

#define F_LINUX_SPECIFIC_BASE   1024



#endif /* _ASM_GENERIC_FCNTL_H */

#else

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#ifdef _XOPEN_SOURCE
#include <sys/ipc.h> 
#endif
#include <netinet/in.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/timeb.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/times.h>
#include <sys/select.h>
#include <sys/un.h>
#include <sys/ipc.h>
#include <sys/msg.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#include <sys/socket.h>


#endif //WIN32

#define XML_INDEX_TEST 1
#define Sleep SleepCustom

#endif //__HCH_COMPLIE_ON_WIN__