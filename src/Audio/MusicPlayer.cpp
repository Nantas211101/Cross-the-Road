#include <MusicPlayer.hpp>

MusicPlayer::MusicPlayer()
: mMusic()
, mFilenames()
, mVolume(100.f)
, mCurrentTheme(Music::None)
{
    mFilenames[Music::MenuTheme] = "Media/Music/MenuTheme.ogg";
    mFilenames[Music::ChooseCharTheme] = "Media/Music/ChooseCharTheme.ogg";
}

void MusicPlayer::play(Music::ID theme)
{
    if(theme == mCurrentTheme)
        return;

    mCurrentTheme = theme;
    
    std::string filename = mFilenames[theme];

    if(!mMusic.openFromFile(filename))
        throw std::runtime_error("Music " + filename + " could not be loaded");
    
    mMusic.setVolume(mVolume);
    mMusic.setLoop(true);
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