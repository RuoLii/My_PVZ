#include "wallnutpush.h"

WallnutPush::WallnutPush(int row, int col)
{
    this->row = row;
    this->col = col;
    movie = new QMovie(":/new/prefix1/imag/wallnut.gif");
    this->setMovie(movie);
    movie->start();
}

WallnutPush::~WallnutPush()
{
    delete movie;
}
