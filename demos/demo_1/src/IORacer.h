/**
 *  @defgroup io_racer IORacer
 *  IORacer game main class.
 */

/**
 *  @file
 *  @ingroup io_racer
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 20.03.17
 */

#ifndef _IORacer_H_
#define _IORacer_H_

#include <MainView.h>
#include <ExternalEvents.h>
#include <EventManager.h>
#include <ContextManager.h>

/**
 * Main game class object.
 */
class IORacer {
private:
    /// External events controller
    ExternalEvents external_events;
    /// Event manager
    EventManager event_manager;
    /// Game context manager
    ContextManager context_manager;

    /// Main view
    MainView main_view;

public:
    IORacer();

    ~IORacer();

    void ParseParams(int argc, char **argv);

    void Initialize();

    void Run();

    int Exit();

    bool IsOver();
};


#endif //_IORacer_H_
