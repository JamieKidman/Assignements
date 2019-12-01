#include  <thread.h>
#include  <synch.h>

#include  "buf-m-2.h"

#define   BUF_SIZE   5                  /* buffer size              */

static int   Buf[BUF_SIZE];             /* the actual buffer        */
static int   in;                        /* next empty location      */
static int   out;                       /* next filled location     */
static int   count;                     /* no. of items in buffer   */

static mutex_t  MonitorLock;            /* monitor lock             */

static cond_t   UntilNotFull;           /* wait until full cv       */
static cond_t   UntilNotEmpty;          /* wait until full cv       */

void  BufferInit(void)
{
     in = out = count = 0;

     mutex_init(&MonitorLock, USYNC_THREAD, (void *) NULL);

     cond_init(&UntilNotFull, USYNC_THREAD, (void *) NULL);
     cond_init(&UntilNotEmpty, USYNC_THREAD, (void *) NULL);
}

int  GET(void)
{
     int  value;

     mutex_lock(&MonitorLock);          /* lock the monitor         */
          while (count == 0)            /* while nothing in buffer  */
               cond_wait(&UntilNotEmpty, &MonitorLock); /* then wait*/
          value = Buf[out];             /* retrieve an item         */
          out = (out + 1) % BUF_SIZE;   /* advance out pointer      */
          count--;                      /* decrease counter         */
          cond_signal(&UntilNotFull);   /* signal consumers         */
     mutex_unlock(&MonitorLock);        /* release monitor          */
     return  value;                     /* return retrieved vague   */
}

int  PUT(int  value)
{
     mutex_lock(&MonitorLock);          /* lock the buffer          */
          while (count == BUF_SIZE)     /* while buffer is full     */
               cond_wait(&UntilNotFull, &MonitorLock); /* then wait */
          Buf[in] = value;              /* add the value to buffer  */
          in = (in + 1) % BUF_SIZE;     /* advance in pointer       */
          count++;                      /* increase count           */
          cond_signal(&UntilNotEmpty);  /* signal producers         */
     mutex_unlock(&MonitorLock);        /* release the lock         */
     return  value;                     /* return the value         */
}