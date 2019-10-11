/*
 * File:   fileio.h
 * Author: aric
 *
 * Created on February 10, 2009, 1:04 AM
 */

#ifndef _FILEIO_H
#define _FILEIO_H

#include "sys/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* IoBlock flags */
#define O_RDONLY (0x0001)
#define O_WRONLY (0x0002)
#define O_RDWR (0x0003)
#define O_NBLOCK (0x0004)
#define O_APPEND (0x0100)
#define O_CREAT (0x0200)
#define O_TRUNC (0x0400)
#define O_NOBUF (0x4000)
#define O_NOWAIT (0x8000)

#define FSCAN 0x1000

/* "whence" for seek functions */
#ifndef SEEK_SET
#define SEEK_SET 0
#endif
#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif
#ifndef SEEK_END
#define SEEK_END 2
#endif

/* device types */
/* for DeviceDriver.type */
#define DEV_TYPE_CHAR (1 << 0)  /* character device */
#define DEV_TYPE_TTY (1 << 1)   /* TTY/console */
#define DEV_TYPE_BLOCK (1 << 2) /* block device */
#define DEV_TYPE_RAW (1 << 3)   /* raw device that uses fs switch */
#define DEV_TYPE_FS (1 << 4)

/* device FIFO flags */
/* for device_fifo.flags */
#define DEV_FIFO_RAW (1 << 0)     /* don't interpret special chars */
#define DEV_FIFO_STOPPED (1 << 1) /* stop output */
#define DEV_FIFO_BREAK (1 << 2)   /* cntl-c raise console interrpt */

// sizeof() == 0x10C(268)
typedef struct st_device_fifo {
    uint32_t flags;  // 0x00 - see "device FIFO flags"
    char* wr_ptr;    // 0x04 - pointer to "write" position in FIFO.
    char* rd_ptr;    // 0x08 - pointer to "read" position in FIFO.
    char buf[256];   // 0x0C - FIFO buffer.
} device_fifo;

#define M_FIFO_PURGE(__fifo) ((__fifo)->rd_ptr = (__fifo)->wr_ptr = (__fifo)->buf)
#define M_IS_FIFO_EMPTY(__fifo) ((__fifo)->rd_ptr == (__fifo)->wr_ptr)
#define M_IS_FIFO_STOPPED(__fifo) ((__fifo)->flags & DEV_FIFO_STOPPED)
#define stdin (0)
#define stdout (1)

/* sizeof() == 0x2C(44) */
typedef struct st_PS1_IoBlock {
    int flags;                      // 0x00 - see IoBlock flags(TODO: fixme?)
    int dev_no;                     // 0x04 - ?
    char* buf;                      // 0x08 - address of the I/O buffer.
    uint32_t ccount;                // 0x0C - character count
    uint32_t cur_pos;               // 0x10 - current position in file.
    int fstype;                     // 0x14 - type of file system.
    int errno;                      // 0x18 - last "errno"
    struct st_DeviceDriver* dd;     // 0x1C - pointer to fsd
    uint32_t size;                  // 0x20 - file size?
    uint32_t head;                  // 0x24 - ?
    uint32_t fd;                    // 0x28 file descriptor
} IoBlock;

#warning "FIXME: add argument names to prototypes in DeviceDriver struct in fileio.h"
/* sizeof() == 0x50(80) */
typedef struct st_DeviceDriver {
    const char* name;     // 0x00 - pointer to unique name identifying device.
    uint32_t type;        // 0x04 - bitmask. see Device Types.
    uint32_t block_size;  // 0x08 - size, in bytes, of a block.
    const char* desc;     // 0x0C - pointer to ASCII-Z description of device.
    int (*init)(IoBlock *iob);        // 0x10 - pointer to "init" function. Called by AddDevice()
    int (*open)(IoBlock *iob, const char *fname, int mode);        // 0x14 - pointer to "open" function.
    int (*strategy)(IoBlock *iob, int cmd);    // 0x18 - pointer to "strategy" function.
    int (*close)(IoBlock *iob);       // 0x1C - pointer to "close" function.
    int (*ioctl)(IoBlock *iob, int cmd, int param);       // 0x20 - pointer to "ioctl" function.
    int (*read)(IoBlock *iob, void *p, int size);        // 0x24 - pointer to "read" function.
    int (*write)(IoBlock *iob, const void *p, int size);       // 0x28 - pointer to "write" function.
    int (*delete)(IoBlock *iob, const char *name);      // 0x2C - pointer to "delete" function.
    int (*undelete)(IoBlock *iob, const char *name);    // 0x30 - pointer to "undelete" function.
    int (*firstfile)();   // 0x34 - pointer to "firstfile" function.
    int (*nextfile)();    // 0x38 - pointer to "nextfile" function.
    int (*format)();      // 0x3C - pointer to "format" function.
    int (*chdir)(const char *path);       // 0x40 - pointer to "cd" function.
    int (*rename)(const char *oldname, const char *newname);      // 0x44 - pointer to "rename" function.
    int (*deinit)(IoBlock *iob);      // 0x48 - pointer to "deinit" function.  Called by RemDevice()
    int (*lseek)(IoBlock*iob, int pos, int whence);       // 0x4C - pointer to "lseek" function.
} DeviceDriver;

typedef struct st_DirEntry {
    char name[20];             // 0x00 - ASCII file name.
    uint32_t attr;             // 0x14 - file attributes.
    uint32_t size;             // 0x18 - file size, in bytes.
    struct st_DirEntry* next;  // 0x1C - pointer to next directory entry structure.
    uint32_t head;             // 0x20 - ???
    uint8_t system[4];         // 0x24 - ??? unused?
} DirEntry;

int AddDevice(const DeviceDriver* dd);
int DelDevice(const char* dev_name);

#warning "FIXME: add argument names to prototypes in fileio.h"
DirEntry* firstfile(const char*, DirEntry*);
DirEntry* nextfile(DirEntry*);

#ifdef __cplusplus
}
#endif

#endif /* _FILEIO_H */