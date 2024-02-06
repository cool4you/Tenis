#include "Board.h"

USING_NS_CC;

int Board::getBoardSize()
{
    return boardPlusSize;
}

void Board::setBoardSize(int size)
{
    boardPlusSize = size;
}

void Board::setBoardVelocity(int value)
{
    boardVelocity = value;
}

int Board::getBoardVelocity()
{
    return boardVelocity;
}

Board* Board::createBoard(const std::string& filename)
{
    Board* board = new Board();
    if (board && board->initBoard(filename))
    {
        board->autorelease();
        return board;
    }
    CC_SAFE_DELETE(board);
    return nullptr;
}

bool Board::initBoard(const std::string& filename)
{
    if (!Sprite::initWithFile(filename))
    {
        return false;
    }

    boardPlusSize = 4;
    // Дополнительная инициализация доски (если необходимо)

    return true;
}
