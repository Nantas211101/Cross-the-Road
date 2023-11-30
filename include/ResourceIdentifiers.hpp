#pragma once

namespace Textures{
    enum ID{
        none,
        chicken,
        penguin,
        sheep,
        mallard,
        background,
        TitleScreen,
        ChooseCharScreen,
        RightButton,
        LeftButton,
        ButtonNormal,
        ButtonPressed,
        ButtonSelected,
        InputButton1,
        LoginBG,
        RegisterBG,
        VisiblePassword,
        InvisiblePassword,
};
}

namespace Fonts{
    enum ID{
        Main,
        Label,
    };
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;