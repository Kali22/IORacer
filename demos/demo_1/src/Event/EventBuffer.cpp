/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/27/17
 */

#include <EventBuffer.h>
#include <cstdio>

EventBuffer::EventBuffer() {
    /// @TODO temporary constant size
    buffer.resize(128);
    begin = 0;
    end = 0;
    size = 0;
}

EventBuffer::EventBuffer(std::size_t size) {
    buffer.resize(size);
    begin = 0;
    end = 0;
    this->size = 0;
}

EventBuffer::EventBuffer(const EventBuffer &buffer) {

}

EventBuffer &EventBuffer::operator=(const EventBuffer &buffer) {
    return *this;
}

void EventBuffer::Add(Event e) {
    if (size < buffer.size()) {
        buffer[end++] = e;
        size++;
        end = end % buffer.size();
        printf("Add event to buffer: %d, size: %d\n", e.event_type, size);
    } else {
        /// @TODO resize buffer
    }
}

bool EventBuffer::IsEmpty() {
    return size == 0;
}

bool EventBuffer::Get(Event &e) {
    printf("Get event! Size: %d\n", size);
    if (size == 0) {
        return false;
    } else {
        e = buffer[begin++];
        size--;
        begin = begin % buffer.size();
        printf("Get event: %d\n", e.event_type);
        return true;
    }
}
