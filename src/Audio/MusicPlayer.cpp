#include <MusicPlayer.hpp>

MusicPlayer::MusicPlayer()
: mMusic()
, mFilenames()
, mVolume(100.f)
, mCurrentTheme(Music::None)
{
    mFilenames[Music::MenuTheme] = "Media/Music/MenuTheme.ogg";
    mFilenames[Music::ChooseCharTheme] = "Media/Music/ChooseCharTheme.ogg";
    mFilenames[Music::CreditsTheme] = "Media/Music/Aquatic_Main.ogg";

    mFilenames[Music::GameTheme1Main] = "Media/Music/Theme1/Neon_City_Main.ogg";
    mFilenames[Music::GameTheme1Win] = "Media/Music/Theme1/Neon_City_Win.ogg";
    mFilenames[Music::GameTheme1Lose] = "Media/Music/Theme1/Neon_City_Lose.ogg";

    mFilenames[Music::GameTheme2Main] = "Media/Music/Theme2/Wintry_Embrace_Main.ogg";
    mFilenames[Music::GameTheme2Win] = "Media/Music/Theme2/Wintry_Embrace_Win.ogg";
    mFilenames[Music::GameTheme2Lose] = "Media/Music/Theme2/Wintry_Embrace_Lose.ogg";

    mFilenames[Music::GameTheme3Main] = "Media/Music/Theme3/Volcanic_Main.ogg";
    mFilenames[Music::GameTheme3Win] = "Media/Music/Theme3/Volcanic_Win.ogg";
    mFilenames[Music::GameTheme3Lose] = "Media/Music/Theme3/Volcanic_Lose.ogg";
}

void MusicPlayer::play(Music::ID theme, bool isLooped)
{
    if(theme == mCurrentTheme)
        return;

    mCurrentTheme = theme;
    
    std::string filename = mFilenames[theme];

    if(!mMusic.openFromFile(filename))
        throw std::runtime_error("Music " + filename + " could not be loaded");
    
    mMusic.setVolume(mVolume);
    mMusic.setLoop(isLooped);
    mMusic.play();
}

void MusicPlayer::stop()
{
    mMusic.stop();
}

void MusicPlayer::setPaused(bool paused)
{
    if(paused)
        mMusic.pause();
    else 
        mMusic.play();
}

void MusicPlayer::setVolume(float volume)
{
    setImmediateVolume(volume);
    mVolume = volume;
}

void MusicPlayer::setImmediateVolume(float volume)
{
    mMusic.setVolume(volume);
}

float MusicPlayer::getVolume() const
{
    return mVolume;
}