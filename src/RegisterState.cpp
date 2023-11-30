#include "RegisterState.hpp"
#include "Utility.hpp"
#include "TextureManipulate.hpp"
#include "GUI_InputButton.hpp"
#include "GUI_Button.hpp"

#include <fstream>

const std::string Main_text = "Register your account";
const std::string Error_Username_Taken = "Username is already taken!\n Please try again!";
const std::string Error_Username_Too_Short = "Username is too short!\n Please try again!";
const std::string Error_Password_Too_Short = "Password is too short!\n Please try again!";
const std::string Error_Password_Not_Match = "Password does not match!\n Please try again!";

const std::string Path_SaveAccount = "Private/AccountSaving.txt";

RegisterState::RegisterState(StateStack &stack, Context context)
: State(stack, context)
, mGUIContainer()
, mBackground()
, mText(Main_text, context.fonts->get(Fonts::Main), 75)
, mTextUsername()
, mTextPassword()
{
    
}