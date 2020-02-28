#include <genesis.h>
#include <string.h>
#include "../res/resources.h"

//------------------------------------------------------------------//
// FIELDS

// Text labels
const char MESSAGE_START[22] = "Press START to Begin!";
const char MESSAGE_RESET[22] = "Press START to Reset!";

const int SCROLL_SPEED = 2;

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

    // Define o tamanho do plano dos tiles
    VDP_setPlanSize (32, 32);

    // Permite usar scrolling no plano horizonal e vertical
    VDP_setScrollingMode (HSCROLL_PLANE, VSCROLL_PLANE);

    // Carrega tiles
    VDP_loadTileSet (floorImage.tileset, 1, DMA);
    VDP_loadTileSet (wallImage.tileset, 2, DMA);
    VDP_loadTileSet (lightPoleImage.tileset, 3, DMA);

    VDP_setPalette (PAL1, lightPoleImage.palette -> data);

    // Define paleta de cores do background baseado numa cor de valor hexadecimal
    VDP_setPaletteColor (0, RGB24_TO_VDPCOLOR (0x6dc2ca));

    showText (MESSAGE_START);

    // Adiciona linha de tiles
    VDP_fillTileMapRect (PLAN_B, TILE_ATTR_FULL (PAL1, 0, FALSE, FALSE, 1), 0, 16, 32, 1);
    VDP_fillTileMapRect (PLAN_B, TILE_ATTR_FULL (PAL1, 0, FALSE, TRUE, 2), 0, 17, 32, 14);

    // Parecido com fillTileMapRect, mas calcula quantos tiles serao necessarios
    VDP_fillTileMapRectInc (PLAN_B, TILE_ATTR_FULL (PAL1, 0, FALSE, FALSE, 3), 15, 13, 2, 3);

    int offset = 0;

    // Loop do jogo
    while (1)
    {
        if (isGameOn == TRUE)
        {

        }

        // Realiza um scroll horizontal no Plano B com base no valor offset de distancia de frame para frame
        VDP_setHorizontalScroll (PLAN_B, offset -= SCROLL_SPEED);

        if (offset <= -256) 
        {
            offset = 0;
        }

        VDP_waitVSync ();
    }

    return (0);
}
