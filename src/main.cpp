#include <Window.h>
#include <ActivityManager.h>
#include <PlayerSelector.h>
#include <Splash.h>
#include <NewRace.h>


int main(int argc, char **argv) {
    /*=============== Early inits. Core objects. ===============*/
    TextureManagerPtr textureManager = std::make_shared<TextureManager>();
    WindowPtr window = std::make_shared<Window>("IORacer");
    ActivityManagerPtr activityManager = std::make_shared<ActivityManager>(window, textureManager);

    /*=============== Activities and game logic. ===============*/
    SplashPtr splashScreen = std::make_shared<Splash>();
    PlayerSelectorPrt playerSelector = std::make_shared<PlayerSelector>();
    NewRacePtr newRace = std::make_shared<NewRace>();
    activityManager->AddActivity(splashScreen);
    activityManager->AddActivity(playerSelector);
    activityManager->AddActivity(newRace);
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
