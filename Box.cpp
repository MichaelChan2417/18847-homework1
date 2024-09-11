# include "Box.H"
#include <cassert>
#include <cstdio>

Box::Box()
{
  for (int dir = 0 ; dir < DIM ; dir++)
    {
      m_lowCorner[dir] = 0;     
      m_highCorner[dir] = -1;
    }
}

bool Box::isEmpty() const
{
  for(int dir=0; dir < DIM; dir++)
    {
      if(m_lowCorner[dir] > m_highCorner[dir]) return true;
    }
  return false;
}

bool Box::contains(const int a_tupleIndex[DIM]) const
{
  for(int i=0; i<DIM; i++)
    {
      if(a_tupleIndex[i] < m_lowCorner[i]) return false;
      if(a_tupleIndex[i] > m_highCorner[i]) return false;
    }
  return true;
}
