#include "3D_Collision_Detection.h"

threeD_Collision_Detection::threeD_Collision_Detection(void)
{
    c1 = c2 = c3 = c4 = c5 = c6 = c7= c8 = c9 = c10 = c11 = c12= c13= c14= c15 = true;
}

threeD_Collision_Detection::~threeD_Collision_Detection(void)
{

}

void threeD_Collision_Detection::SATCheckCollision_3D(threeD_HitBox &BoxA, threeD_HitBox &BoxB, bool &collide)
{
    T = BoxB.Position - BoxA.Position;
    
    // case 1
    L = BoxA.unitVecX;
    if (abs(T.Dot(L)) > abs((BoxA.unitVecX * BoxA.HalfWidth).Dot(L)) + 
                        abs((BoxA.unitVecY * BoxA.HalfHeight).Dot(L)) +
                        abs((BoxA.unitVecZ * BoxA.HalfDepth).Dot(L)) +
                        abs((BoxB.unitVecX * BoxB.HalfWidth).Dot(L)) +
                        abs((BoxB.unitVecY * BoxB.HalfHeight).Dot(L))+
                        abs((BoxB.unitVecZ * BoxB.HalfDepth).Dot(L)))
    {
        c1 = true;
    }

    else
    {
        c1 = false;
    }

    // case 2
    L = BoxA.unitVecY;
    if (abs(T.Dot(L)) > abs((BoxA.unitVecX * BoxA.HalfWidth).Dot(L)) + 
                        abs((BoxA.unitVecY * BoxA.HalfHeight).Dot(L)) +
                        abs((BoxA.unitVecZ * BoxA.HalfDepth).Dot(L)) +
                        abs((BoxB.unitVecX * BoxB.HalfWidth).Dot(L)) +
                        abs((BoxB.unitVecY * BoxB.HalfHeight).Dot(L))+
                        abs((BoxB.unitVecZ * BoxB.HalfDepth).Dot(L)))
    {
        c2= true;
    }

    else
    {
        c2 = false;
    }

    // case 2
    L = BoxA.unitVecZ;
    if (abs(T.Dot(L)) > abs((BoxA.unitVecX * BoxA.HalfWidth).Dot(L)) + 
                        abs((BoxA.unitVecY * BoxA.HalfHeight).Dot(L)) +
                        abs((BoxA.unitVecZ * BoxA.HalfDepth).Dot(L)) +
                        abs((BoxB.unitVecX * BoxB.HalfWidth).Dot(L)) +
                        abs((BoxB.unitVecY * BoxB.HalfHeight).Dot(L))+
                        abs((BoxB.unitVecZ * BoxB.HalfDepth).Dot(L)))
    {
        c3 = true;
    }

    else
    {
        c3 = false;
    }

    // case 4
    L = BoxB.unitVecX;
    if (abs(T.Dot(L)) > abs((BoxA.unitVecX * BoxA.HalfWidth).Dot(L)) + 
                        abs((BoxA.unitVecY * BoxA.HalfHeight).Dot(L)) +
                        abs((BoxA.unitVecZ * BoxA.HalfDepth).Dot(L)) +
                        abs((BoxB.unitVecX * BoxB.HalfWidth).Dot(L)) +
                        abs((BoxB.unitVecY * BoxB.HalfHeight).Dot(L))+
                        abs((BoxB.unitVecZ * BoxB.HalfDepth).Dot(L)))
    {
        c4 = true;
    }

    else
    {
        c4 = false;
    }

    // case 5
    L = BoxB.unitVecY;
    if (abs(T.Dot(L)) > abs((BoxA.unitVecX * BoxA.HalfWidth).Dot(L)) + 
                        abs((BoxA.unitVecY * BoxA.HalfHeight).Dot(L)) +
                        abs((BoxA.unitVecZ * BoxA.HalfDepth).Dot(L)) +
                        abs((BoxB.unitVecX * BoxB.HalfWidth).Dot(L)) +
                        abs((BoxB.unitVecY * BoxB.HalfHeight).Dot(L))+
                        abs((BoxB.unitVecZ * BoxB.HalfDepth).Dot(L)))
    {
        c5 = true;
    }

    else
    {
        c5 = false;
    }

    // case 6
    L = BoxB.unitVecZ;
    if (abs(T.Dot(L)) > abs((BoxA.unitVecX * BoxA.HalfWidth).Dot(L)) + 
                        abs((BoxA.unitVecY * BoxA.HalfHeight).Dot(L)) +
                        abs((BoxA.unitVecZ * BoxA.HalfDepth).Dot(L)) +
                        abs((BoxB.unitVecX * BoxB.HalfWidth).Dot(L)) +
                        abs((BoxB.unitVecY * BoxB.HalfHeight).Dot(L))+
                        abs((BoxB.unitVecZ * BoxB.HalfDepth).Dot(L)))
    {
        c6 = true;
    }

    else
    {
        c6 = false;
    }

    // case 7
    L = BoxA.unitVecX.Cross(BoxB.unitVecX);
    if (abs(T.Dot(L)) > abs((BoxA.unitVecX * BoxA.HalfWidth).Dot(L)) + 
                        abs((BoxA.unitVecY * BoxA.HalfHeight).Dot(L)) +
                        abs((BoxA.unitVecZ * BoxA.HalfDepth).Dot(L)) +
                        abs((BoxB.unitVecX * BoxB.HalfWidth).Dot(L)) +
                        abs((BoxB.unitVecY * BoxB.HalfHeight).Dot(L))+
                        abs((BoxB.unitVecZ * BoxB.HalfDepth).Dot(L)))
    {
        c7 = true;
    }

    else
    {
        c7 = false;
    }

    // case 8
    L = BoxA.unitVecX.Cross(BoxB.unitVecY);
    if (abs(T.Dot(L)) > abs((BoxA.unitVecX * BoxA.HalfWidth).Dot(L)) + 
                        abs((BoxA.unitVecY * BoxA.HalfHeight).Dot(L)) +
                        abs((BoxA.unitVecZ * BoxA.HalfDepth).Dot(L)) +
                        abs((BoxB.unitVecX * BoxB.HalfWidth).Dot(L)) +
                        abs((BoxB.unitVecY * BoxB.HalfHeight).Dot(L))+
                        abs((BoxB.unitVecZ * BoxB.HalfDepth).Dot(L)))
    {
        c8 = true;
    }

    else
    {
        c8 = false;
    }









    if (c1 == false && c2 == false && c3 == false && c4 == false)
    {
        collide = true;
    }

    else
    {
        collide = false;
    }

}

float threeD_Collision_Detection::abs(float value)
{
    if (value < 0)
    {
        return value * (-1);
    }

    else
    {
        return value;
    }
}