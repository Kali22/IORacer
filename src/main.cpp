#include <Window.h>
#include <ActivityManager.h>
#include <PlayerSelector.h>
#include <Splash.h>
#include <NewRace.h>
#include <TextureManager.h>
#include <CarComponentManager.h>
#include <PlayerManager.h>
#include <Workshop.h>


int main(int argc, char **argv) {
    /*=============== Early inits. Core objects. ===============*/
    TextureManagerPtr textureManager = std::make_shared<TextureManager>();
    CarComponentManagerPtr carComponentManager = std::make_shared<CarComponentManager>();
    PlayerManagerPtr playerManager = std::make_shared<PlayerManager>();
    WindowPtr window = std::make_shared<Window>("IORacer");
    ActivityManagerPtr activityManager = std::make_shared<ActivityManager>
            (window, textureManager, carComponentManager, playerManager);

    // TODO Use stored player - integrate with player branch.
    playerManager->SetActivePlayer("jacek");
    /*=============== Activities and game logic. ===============*/
    SplashPtr splashScreen = std::make_shared<Splash>();
    PlayerSelectorPrt playerSelector = std::make_shared<PlayerSelector>();
    NewRacePtr newRace = std::make_shared<NewRace>();
    WorkshopPtr workshop = std::make_shared<Workshop>();
    activityManager->AddActivity(splashScreen);
    activityManager->AddActivity(playerSelector);
    activityManager->AddActivity(newRace);
    activityManager->AddActivity(workshop);
    /* Set splash screen as game entry point. */
    activityManager->SetAsActive("splash");

    /*===============     Let's do your job...   ===============*/
    while (activityManager->IsRunning()) {
        /* Get events. */
        activityManager->Poll();
        /* Manage activities. */
        activityManager->Manage();
    }
    return 0;
}
