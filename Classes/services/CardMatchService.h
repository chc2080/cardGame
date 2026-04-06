#ifndef __CARD_MATCH_SERVICE_H__
#define __CARD_MATCH_SERVICE_H__

class CardMatchService
{
public:
    // 判定两张牌是否符合接龙规则
    static bool canMatch(int cardFace, int topFace);

private:
    static int normalizeFace(int face);
};

#endif // __CARD_MATCH_SERVICE_H__