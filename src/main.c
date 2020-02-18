#include <genesis.h>
#include <string.h>

//------------------------------------------------------------------//
// FIELDS

// Text labels
const char MESSAGE_START[22] = "Press START to Begin!";
const char MESSAGE_RESET[22] = "Press START to Reset!";

// State
bool isGameOn = FALSE;

//------------------------------------------------------------------//
// HELPER FUNCTIONS

void showText (char text[])
{
    int x = (20 - strlen (text) / 2);
    VDP_drawText (text, x, 10);
}

void clearText ()
{
    VDP_clearText (0, 10, 32);
}

void startGame ()
{
    if (isGameOn == FALSE)
    {
        isGameOn = TRUE;
        clearText ();
    }
}

void endGame ()
{
    if (isGameOn == TRUE)
    {
        showText (MESSAGE_RESET);
        isGameOn = FALSE;
    }
}

void joystickHandler (u16 joystick, u16 wasChanged, u16 wasPressed)
{
    if (joystick == JOY_1)
    {
        // Inicializa jogo
        if (wasPressed & BUTTON_START)
        {
            if (isGameOn == FALSE)
            {
                startGame ();
            }
        }

        if (wasPressed & BUTTON_C)
        {

        }
    }
}

//------------------------------------------------------------------//
// MAIN

int main ()
{
    // Inicializa input
    JOY_init ();
    JOY_setEventHandler (&joystickHandler);

    showText (MESSAGE_START);

    // Loop do jogo
    while (1)
    {
        if (isGameOn == TRUE)
        {

        }
        
        VDP_waitVSync ();
    }

    return (0);
}
