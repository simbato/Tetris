#include "board.h"
#include <iostream>
// Vaš kod dolazi ovdje
Board::Board(): mGrid(sf::Lines),mUniformDist(0,100),mOriginX(100),mOriginY(100),mDx(40),mDy(40)
{
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 10; j++)
            mGridContent[i][j]=-1;
    
    mGrid.resize(150);
    
    for (int i = 0; i < 42; i += 2) {       
        mGrid[i].position=sf::Vector2f(100,100+20*i);
        mGrid[i+1].position=sf::Vector2f(500,100+20*i);
    }
        
    for (int i = 0; i < 22; i += 2) {       
        mGrid[i+42].position=sf::Vector2f(100+20*i,100);
        mGrid[i+1+42].position=sf::Vector2f(100+20*i,900); 
    }
}

Board::~Board(){

}

bool Board::checkSpace()
{
    int xCoordinate = (mPiece.mXposition - mLeftMargin) / mDx;
    int yCoordinate = (mPiece.mYposition - mTopMargin) / mDy;
    int next = (mPiece.mRotacija + 1)%4;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++){
            if (mPiece.mDijelovi[mPiece.mType][next][i][j] != 0 && (xCoordinate + j > 9 || 
                        yCoordinate + i > 19 || xCoordinate + j < 0) ) return false;
            if (mPiece.mDijelovi[mPiece.mType][next][i][j] != 0 && mGridContent[yCoordinate+i][xCoordinate+j] != -1 &&
                mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j] == 0) return false;
        }
    return true;
}
void Board::spawnPiece()
{
    mPiece.mRotacija = mUniformDist(mRNE) % 4;
    tip_tetrimina = mUniformDist(mRNE) % 7;
    switch (tip_tetrimina)
    {
        case 0:
            mPiece.mType = Tetrimino::Types(0);
            break;
        case 1:
            mPiece.mType = Tetrimino::Types(1);
            break;
        case 2:
            mPiece.mType = Tetrimino::Types(2);
            break;
        case 3:
            mPiece.mType = Tetrimino::Types(3);
            break;
        case 4:
            mPiece.mType = Tetrimino::Types(4);
            break;
        case 5:
            mPiece.mType = Tetrimino::Types(5);
            break;
        case 6:
            mPiece.mType = Tetrimino::Types(6);
            break;
        default:
            break;
    }
    
    for (int i = 0; i < 4; i++)
       for (int j = 3; j < 7; j++)
        {
            if(mGridContent[i][j] != -1)
            {
                mGameOver = true;
            }
            if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j-3] != 0)
                mGridContent[i][j] = tip_tetrimina;
        }
    
    mPiece.mXposition = mLeftMargin + 3*mDx;
    mPiece.mYposition = mTopMargin;
}
bool Board::movePiece(int x,int y)
{   
    int xCoordinate = (mPiece.mXposition - mLeftMargin) / mDx;
    int yCoordinate = (mPiece.mYposition - mTopMargin) / mDy;


    if(xCoordinate == 0 && x== -1*mDx)
        for (int i = 0; i < 4; i++)
            if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][0] != 0)
                return false;
                

    if(xCoordinate == -1 && x== -1*mDx)
        for (int i = 0; i < 4; i++)
            if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][1]!=0)
                return false;
                
    if(xCoordinate == -2 && x == -1*mDx) return false;

    if(xCoordinate == 6 && x == mDx)
        for (int i = 0; i < 4; i++)
            if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][3]!=0)
                return false;        
    
    if(xCoordinate == 7 && x == mDx)
        for (int i = 0; i < 4; i++)
            if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][2]!=0)
                return false;        
    
    if(xCoordinate == 8 && x == mDx) return false;
  


    //lijevo
    if ( x == -1*mDx){
        if (xCoordinate != 0) 
            for (int i = 0; i < 4; i++){ //prvi stupac
                if (mGridContent[yCoordinate + i][xCoordinate - 1] != -1 && 
                    mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][0] != 0) return false;
            }
        
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 3; j++) {
                if (mGridContent[yCoordinate + i][xCoordinate + j] == -1) continue;
                //1. pozicija je zauzeta
                if (mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j] != 0) continue;
                else if (mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j] == 0){
                    if (mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j+1] != 0) return false;
                    else continue;
                }

            }
        removePiece();
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j] != 0)
                    mGridContent[yCoordinate + i][xCoordinate - 1 + j] = mPiece.mType;
        mPiece.mXposition -= mDx;
        return true;
    }

    //desno
    if ( x == mDx){
        if (xCoordinate != 6) 
            for (int i = 0; i < 4; i++){ //zadnji stupac
                if (mGridContent[yCoordinate + i][xCoordinate + 4] != -1 && 
                    mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][3] != 0) return false;
            }
        
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 3; j++) {
                if (mGridContent[yCoordinate + i][xCoordinate - j + 3] == -1) continue;
                //4. pozicija je zauzeta
                if (mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][3-j] != 0) continue;
                else if (mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][3-j] == 0){
                    if (mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][3-j-1] != 0) return false;
                    else continue;
                }

            }
        removePiece();
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j] != 0)
                    mGridContent[yCoordinate + i][xCoordinate + 1 + j] = mPiece.mType;
        mPiece.mXposition += mDx;
        return true;
    }
    //doli
    if (y == mDy){
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++){
                if (yCoordinate + i > 20) return false;
                if (mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j] == 0) continue;
                else{
                    if (mGridContent[yCoordinate + i + 1][xCoordinate + j] != -1 && 
                        mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i+1][j] == 0) return false;
                }
            }
        removePiece();
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j] != 0)
                    mGridContent[yCoordinate + 1 + i][xCoordinate + j] = mPiece.mType;
        mPiece.mYposition += mDy;
        return true;
    }
}
void Board::update(int x,int y)
{

    if(x == 0 && y == 0 && checkSpace()){
        rotatePiece();
        return;
    }
    else if(y == 1 && !movePiece(x*mDx, y*mDy))
    {
        clearLines();
        if (!mGameOver)
            spawnPiece();
    }
    else if (y == 2)
    {
        while (movePiece(0, mDy));
    }
    
    else if(y != 1 && y != 2){
        movePiece(x*mDx, y*mDy);
    }
}
void Board::removePiece()
{
    int xCoordinate = (mPiece.mXposition - mLeftMargin) / mDx;
    int yCoordinate = (mPiece.mYposition - mTopMargin) / mDy;
    for (int i = 0; i < 4; i++)
        for(int j=0;j<4;j++)
            if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j]!=0 && mGridContent[yCoordinate+i][xCoordinate+j]!=-1)
                mGridContent[yCoordinate+i][xCoordinate+j]=-1;
        
}
bool Board::rotatePiece()
{
    removePiece();
    int xCoordinate = (mPiece.mXposition - mLeftMargin) / mDx;
    int yCoordinate = (mPiece.mYposition - mTopMargin) / mDy;
    int next = (mPiece.mRotacija + 1)%4;
    
    for (int i = 0; i < 4; i++)
        for(int j=0;j<4;j++)
            if(mPiece.mDijelovi[mPiece.mType][next][i][j] != 0)
                mGridContent[yCoordinate+i][xCoordinate+j] = mPiece.mType;
        
    mPiece.mRotacija = next;
    return true;   
}
bool Board::isLineFull(int y) const
{
    for (int j = 0; j < 10; j++)
        if(mGridContent[y][j]==-1) return false;

    return true;    
}
int Board::clearLines()
{
    int br = 0;
    for(int i = 0; i < 20; i++)
        {
            if(isLineFull(i))
            {
                for(int j = i-1; j >= 0; j--)
                {
                    for(int k = 0 ;k < 10; k++)
                        mGridContent[j+1][k]=mGridContent[j][k];
                }
                for(int j = 0; j < 10; j++)
                    mGridContent[0][j] = -1;
                br++;
            }
        }
    return br;
}
int Board::getNoLinesCompleted() const
{
    int br = 0;
    for(int i = 0; i < 20; i++)
            if(isLineFull(i)) br++;
        
    return br;
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states ) const
{
    states.transform *= getTransform();
    target.draw( mGrid, states );

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if(mGridContent[i][j]!=-1)
            {
                sf::RectangleShape rect;
                rect.setSize(sf::Vector2f(mDx - 2,mDy - 2));
                rect.setPosition(100 + mDx*j + 1,100 + mDy*i + 1);
                rect.setFillColor(mPiece.mColors[mGridContent[i][j] ]);
                target.draw(rect, states);
            }
        }        
    }
}

void Board::clearState(){
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 10; j++)
            mGridContent[i][j] = -1;
    mGameOver = false;
}