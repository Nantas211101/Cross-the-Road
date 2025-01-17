#pragma once

namespace States{
    enum ID{
        None,
        Title,
        ChooseChar,
        Menu,
        Loading,
        Game,
        Settings,
        Pause,
        Login,
        Register,
        ConfirmRegister,
        DisplayCharState,
        GameOver,
        ChooseWorldState,
        ChooseLevelState,
        Victory,
        ReturnGame,
        Credits,
        ResetConfirm,
        ResetSuccess,
        PurchaseConfirm,
        PurchaseResult,
    };
}