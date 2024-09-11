#include "MDArray.H"
#include "Box.H"
#include <cstdio>
#include <cmath>
#include <cassert>

MDArray::MDArray()
{
  m_isDefined = false;
  m_data = NULL;
}

float& MDArray::indexShift(const int a_tuple[DIM], const int& a_dir,const int& a_shift) const
{
  int shiftedTuple[DIM];
  for (int dir = 0; dir < DIM; dir++)
    {
      shiftedTuple[dir] = a_tuple[dir];
    }
  shiftedTuple[a_dir] += a_shift;
  return (*this)[shiftedTuple];
}

