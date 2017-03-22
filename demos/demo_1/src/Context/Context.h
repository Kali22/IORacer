/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 20.03.17
 */

#ifndef _Context_H_
#define _Context_H_

#include <ContextView.h>
#include <ContextEvents.h>
#include <ContextLogic.h>


class Context {
private:
    ContextView view;
    ContextEvents events;
    ContextLogic logic;
public:
    Context();

    ~Context();

    ContextView *GetView();

    void PushEvent(Event &event);

    void Process(EventManager &event_manager);

    const ContextView &GetContextView();
};


#endif //_Context_H_
