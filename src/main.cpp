#include <PlayerManager.h>
#include <TextureManager.h>
#include <CarComponentManager.h>
#include <Window.h>
#include <ActivityManager.h>
#include <Splash.h>
#include <PlayerSelector.h>
#include <NewPlayer.h>
#include <MainMenu.h>
#include <NewRace.h>


int main(int argc, char **argv) {
    /*=============== Early inits. Core objects. ===============*/
    CarComponentManagerPtr carComponentManager = std::make_shared<CarComponentManager>();
    TextureManagerPtr textureManager = std::make_shared<TextureManager>();
    PlayerManagerPtr playerManager = std::make_shared<PlayerManager>(carComponentManager);
    WindowPtr window = std::make_shared<Window>("IORacer");
    ActivityManagerPtr activityManager = std::make_shared<ActivityManager>(window, textureManager, playerManager, carComponentManager);

    /*=============== Activities and game logic. ===============*/
    SplashPtr splashScreen = std::make_shared<Splash>();
    PlayerSelectorPtr playerSelector = std::make_shared<PlayerSelector>();
    NewPlayerPtr newPlayer = std::make_shared<NewPlayer>();
    MainMenuPtr mainMenu = std::make_shared<MainMenu>();
    NewRacePtr newRace = std::make_shared<NewRace>();

    activityManager->AddActivity(splashScreen);
    activityManager->AddActivity(playerSelector);
    activityManager->AddActivity(newPlayer);
    activityManager->AddActivity(mainMenu);
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
    playerManager->SaveGame(); //TODO nie uruchamia sie w destruktorze?
    return 0;
}
