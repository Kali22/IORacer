#include <PlayerManager.h>
#include <TextureManager.h>
#include <CarComponentManager.h>
#include <Window.h>
#include <ActivityManager.h>
#include <PlayerSelector.h>
#include <Splash.h>
#include <PlayerSelector.h>
#include <NewPlayer.h>
#include <MainMenu.h>
#include <NewRace.h>
#include <TextureManager.h>
#include <CarComponentManager.h>
#include <PlayerManager.h>
#include <Workshop.h>


int main(int argc, char **argv) {
    /*=============== Early inits. Core objects. ===============*/
    TextureManagerPtr textureManager = std::make_shared<TextureManager>();
    CarComponentManagerPtr carComponentManager = std::make_shared<CarComponentManager>();
    PlayerManagerPtr playerManager = std::make_shared<PlayerManager>(carComponentManager);
    WindowPtr window = std::make_shared<Window>("IORacer");
    ActivityManagerPtr activityManager = std::make_shared<ActivityManager>
            (window, textureManager, carComponentManager, playerManager);

    playerManager->SetActivePlayer("jacek");
    /*=============== Activities and game logic. ===============*/
    SplashPtr splashScreen = std::make_shared<Splash>();
    PlayerSelectorPtr playerSelector = std::make_shared<PlayerSelector>(FIRST_PLAYER);
    MainMenuPtr mainMenu = std::make_shared<MainMenu>();

    activityManager->AddActivity(splashScreen);
    activityManager->AddActivity(playerSelector);
    activityManager->AddActivity(mainMenu);
    /* Set splash screen as game entry point. */
    activityManager->SetAsActive("splash");

    /*===============     Let's do your job...   ===============*/
    while (activityManager->IsRunning()) {
        /* Get events. */
        activityManager->Poll();
        /* Manage activities. */
        activityManager->Manage();
    }
    playerManager->SaveGame(); //TODO nie uruchamia sie w destruktorze?
    return 0;
}
