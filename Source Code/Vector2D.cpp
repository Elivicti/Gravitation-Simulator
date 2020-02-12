#include "Vector2D.h"

int Vector2D::Decomposition(Vector2D& vecX, Vector2D& vecY, const Vector2D& CoorVec) const
{
    if (this->operator!=(CoorVec))
    {
        double cosine = this->angle_cos(CoorVec);

        //*  vecX = vec.direction() * this->length * cosine;
        vecX.setXY(CoorVec.pos.x / CoorVec.length * this->length * cosine, CoorVec.pos.y / CoorVec.length * this->length * cosine);

        //* vecY = (*this) - vecX;
        vecY.setXY(pos.x - vecX.pos.x, pos.y - vecX.pos.y);

        return 0;
    }
    else
        return -1;
}

