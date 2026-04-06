#include <cstdlib>
#include "services/CardMatchService.h"

int CardMatchService::normalizeFace(int face) { return face; }

bool CardMatchService::canMatch(int cardFace, int topFace)
{
    if (std::abs(cardFace - topFace) == 1) return true;
    if ((cardFace == 0 && topFace == 12) || (cardFace == 12 && topFace == 0)) return true;
    return false;
}