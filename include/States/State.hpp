#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include <Player.hpp>
#include <ResourceIdentifiers.hpp>
#include <StateIdentifiers.hpp>
#include <ResourceHolder.hpp>
#include <MusicPlayer.hpp>
#include <SoundPlayer.hpp>

class StateStack;  
class State{
    public:
        typedef std::unique_ptr<State> S_Ptr;
        struct Context{
            Context(sf::RenderWindow &window, TextureHolder &textures, FontHolder &fonts, Player& player, 
            MusicPlayer& music, SoundPlayer& sound, int& Theme, int& limitLevel, int& currentLevel, int& money,
            std::string& keyMoveUp, std::string& keyMoveDown, std::string& keyMoveLeft, std::string& keyMoveRight,
            std::string& keyUseAbility, int& currentMusicVolume, int& currentTotalVolume);
            
            sf::RenderWindow* window;
            TextureHolder* textures;
            FontHolder* fonts;
            Player* player;
            MusicPlayer* music;
            SoundPlayer* sounds;
            int* theme;
            int* limitLevel;
            int* currentLevel;
            int* money;
            std::string* keyMoveUp;
            std::string* keyMoveDown;
            std::string* keyMoveLeft;
            std::string* keyMoveRight;
            std::string* keyUseAbility;
            int* currentMusicVolume;
            int* currentTotalVolume;
        };
    
    public:
                        State(StateStack &stack, Context context);
        virtual         ~State();

        virtual void    draw() = 0;
        virtual bool    update(sf::Time dt) = 0;
        virtual bool    handleEvent(const sf::Event &event) = 0;

    protected:
        void requestStackPush(States::ID stateID);
        void requestStackPop();
        void requestStateClear();

        auto getContext() -> Context const;

    private:
        StateStack* mStack;
        Context mContext;
};

int convertFromLevelToMaskID(int Level);