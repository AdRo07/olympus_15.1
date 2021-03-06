/*
 * Copyright 2013: Olympus Kernel Project
 * <http://forum.xda-developers.com/showthread.php?t=2016837>
 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * simple ring buffer
 *
 * supports a concurrent reader and writer without locking
 */
#include <linux/slab.h>

struct ts27010_ringbuf {
	int len;
	int head;
	int tail;
	u8 buf[];
};


static inline struct ts27010_ringbuf *ts27010_ringbuf_alloc(int len)
{
	struct ts27010_ringbuf *rbuf;

	rbuf = kzalloc(sizeof(*rbuf) + len, GFP_KERNEL);
	if (rbuf == NULL)
		return NULL;

	rbuf->len = len;
	rbuf->head = 0;
	rbuf->tail = 0;

	return rbuf;
}

static inline void ts27010_ringbuf_free(struct ts27010_ringbuf *rbuf)
{
	kfree(rbuf);
}

static inline int ts27010_ringbuf_level(struct ts27010_ringbuf *rbuf)
{
	int level = rbuf->head - rbuf->tail;

	if (level < 0)
		level = rbuf->len + level;

	return level;
}

static inline int ts27010_ringbuf_room(struct ts27010_ringbuf *rbuf)
{
	return rbuf->len - ts27010_ringbuf_level(rbuf) - 1;
}

static inline u8 ts27010_ringbuf_peek(struct ts27010_ringbuf *rbuf, int i)
{
	return rbuf->buf[(rbuf->tail + i) % rbuf->len];
}

static inline int ts27010_ringbuf_consume(struct ts27010_ringbuf *rbuf,
					  int count)
{
	count = min(count, ts27010_ringbuf_level(rbuf));

	rbuf->tail = (rbuf->tail + count) % rbuf->len;

	return count;
}

static inline int ts27010_ringbuf_push(struct ts27010_ringbuf *rbuf, u8 datum)
{
	if (ts27010_ringbuf_room(rbuf) == 0)
		return 0;

	rbuf->buf[rbuf->head] = datum;
	rbuf->head = (rbuf->head + 1) % rbuf->len;

	return 1;
}

static inline int ts27010_ringbuf_write(struct ts27010_ringbuf *rbuf,
					const u8 *data, int len)
{
	int count = 0;
	int i;

	for (i = 0; i < len; i++)
		count += ts27010_ringbuf_push(rbuf, data[i]);

	return count;
}


