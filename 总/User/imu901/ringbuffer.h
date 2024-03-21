#ifndef _RINGBUFFER_H_
#define _RINGBUFFER_H_

/*环形缓冲区数据结构*/
#include "main.h"

typedef struct
{
  uint8_t *buffer;
  uint16_t size;
  uint16_t in;
  uint16_t out;
} ringbuffer_t;

void ringbuffer_init(ringbuffer_t *fifo, uint8_t *buffer, uint16_t size);

uint16_t ringbuffer_getUsedSize(ringbuffer_t *fifo);
uint16_t ringbuffer_getRemainSize(ringbuffer_t *fifo);
uint8_t ringbuffer_isEmpty(ringbuffer_t *fifo);

void ringbuffer_in(ringbuffer_t *fifo, uint8_t *data, uint16_t len);
uint8_t ringbuffer_in_check(ringbuffer_t *fifo, uint8_t *data, uint16_t len);
uint16_t ringbuffer_out(ringbuffer_t *fifo, uint8_t *buf, uint16_t len);
void ringbuffer_reset(ringbuffer_t *fifo);
void ringbuffer_push(ringbuffer_t *fifo, uint8_t *data, uint16_t len);

#endif /* _RINGBUFFER_H_ */
