#ifndef __BOARD_H__
#define __BOARD_H__

#include "cocos2d.h"

class Board : public cocos2d::Sprite
{
public:

    int getBoardSize();
    void setBoardSize(int size);
    void setBoardVelocity(int value);
    int getBoardVelocity();

    static Board* createBoard(const std::string& filename);
    bool initBoard(const std::string& filename);
private:

    int boardPlusSize;
    int boardVelocity;
};

#endif // __BOARD_H__
