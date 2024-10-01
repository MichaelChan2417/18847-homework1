#include "Box.H"
#include <cassert>
#include <cstdio>
#include <iostream>

// Constructors
Box::Box() {
  for (int dir = 0; dir < DIM; dir++) {
    m_lowCorner[dir] = 0;
    m_highCorner[dir] = -1;
  }
}
Box::Box(const int a_lowCorner[DIM], const int a_highCorner[DIM]) {
  for (int dir = 0; dir < DIM; dir++) {
    m_lowCorner[dir] = a_lowCorner[dir];
    m_highCorner[dir] = a_highCorner[dir];
  }
}
Box::Box(const Box &a_Box) {
  for (int dir = 0; dir < DIM; dir++) {
    m_lowCorner[dir] = a_Box.m_lowCorner[dir];
    m_highCorner[dir] = a_Box.m_highCorner[dir];
  }
}

Box Box::operator&&(const Box &a_rightBox) const {
  Box retval;
  for (int dir = 0; dir < DIM; dir++) {
    retval.m_lowCorner[dir] =
        intMax(m_lowCorner[dir], a_rightBox.m_lowCorner[dir]);
    retval.m_highCorner[dir] =
        intMin(m_highCorner[dir], a_rightBox.m_highCorner[dir]);
  }
  return retval;
}

Box Box::shift(int a_direction, int a_offset) const {
  Box retval(*this);

  retval.m_lowCorner[a_direction] += a_offset;
  retval.m_highCorner[a_direction] += a_offset;
  return retval;
}

Box Box::grow(int a_numpoints) {
  for (int dir = 0; dir < DIM; dir++) {
    m_lowCorner[dir] -= a_numpoints;
    m_highCorner[dir] += a_numpoints;
  }
  return *this;
}

// Access functions for low & high bounds of Box.
void Box::getLowCorner(int a_lowercorner[DIM]) const {
  for (int dir = 0; dir < DIM; dir++) {
    a_lowercorner[dir] = m_lowCorner[dir];
  }
}
void Box::getHighCorner(int a_highercorner[DIM]) const {
  for (int dir = 0; dir < DIM; dir++) {
    a_highercorner[dir] = m_highCorner[dir];
  }
}

int Box::linearIndex(const int a_tupleIndex[DIM]) const {
  int retval = 0;
  int mult = 1;
  for (int dir = 0; dir < DIM; dir++) {
    retval += mult * (a_tupleIndex[dir] - m_lowCorner[dir]);
    mult *= (m_highCorner[dir] - m_lowCorner[dir] + 1);
  }
  return retval;
}

void Box::tupleIndex(int a_linearIndex, int a_tupleIndex[DIM]) const {
  int mult = 1;
  for (int dir = 0; dir < DIM; dir++) {
    int cur_width = m_highCorner[dir] - m_lowCorner[dir] + 1;
    a_tupleIndex[dir] = m_lowCorner[dir] + (a_linearIndex / mult) % cur_width;
    mult *= cur_width;
  }
}

int Box::sizeOf() const {
  if (isEmpty())
    return 0;
  int retval = 1;
  for (int dir = 0; dir < DIM; dir++) {
    retval *= (m_highCorner[dir] - m_lowCorner[dir] + 1);
  }
  return retval;
}

bool Box::operator==(const Box &a_rhsBox) const {
  for (int dir = 0; dir < DIM; dir++) {
    if (m_lowCorner[dir] != a_rhsBox.m_lowCorner[dir])
      return false;
    if (m_highCorner[dir] != a_rhsBox.m_highCorner[dir])
      return false;
  }
  return true;
}

bool Box::isEmpty() const {
  for (int dir = 0; dir < DIM; dir++) {
    if (m_lowCorner[dir] > m_highCorner[dir])
      return true;
  }
  return false;
}

bool Box::contains(const int a_tupleIndex[DIM]) const {
  for (int i = 0; i < DIM; i++) {
    if (a_tupleIndex[i] < m_lowCorner[i])
      return false;
    if (a_tupleIndex[i] > m_highCorner[i])
      return false;
  }
  return true;
}

void Box::print() const {
  std::cout << "{ ";
  for (int dir = 0; dir < DIM; dir++) {
    std::cout << "[" << m_lowCorner[dir] << ", " << m_highCorner[dir] << "] ";
  }
  std::cout << "}" << std::endl;
}