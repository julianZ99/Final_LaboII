#include "sonidos.h"

#pragma comment(lib,"winmm.lib")

void jingleIntro()
{
    PlaySound("sonidos/jingle.wav", NULL, SND_FILENAME | SND_SYNC);
}
