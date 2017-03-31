/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/27/17
 */

#ifndef _EventBuffer_H_
#define _EventBuffer_H_

#include <vector>
#include <Event.h>

class EventBuffer {
private:
    /// Buffer content
    std::vector<Event> buffer;
    /// Begin
    std::size_t begin;
    /// End
    std::size_t end;
    /// Length
    std::size_t size;
public:
    /**
     * Create ringbuffer with default size.
     */
    EventBuffer();

    /**
     * Create ringbuffer with given size.
     * @param size size
     */
    EventBuffer(std::size_t size);

    /**
     * Copy buffer.
     * @param buffer
     */
    EventBuffer(const EventBuffer &buffer);

    /**
     * Copy assignment operator.
     * @param buffer
     * @return
     */
    EventBuffer &operator=(const EventBuffer &buffer);

    /**
     * Add element to buffer.
     * @param e
     */
    void Add(Event e);

    /**
     * Get element from buffer.
     */
    bool Get(Event &e);

    /**
     * Is empty?
     * @return just guess...
     */
    bool IsEmpty();
};


#endif //EventBuffer
