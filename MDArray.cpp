#include "MDArray.H"
#include "Box.H"
#include <cassert>
#include <cmath>
#include <cstdio>

void MDArray::define(Box a_box) {
  m_box = a_box;
  if (m_data != nullptr) {
    delete[] m_data;
  }
  m_data = new float[m_box.sizeOf()];
  // init to zero
  for (int i = 0; i < m_box.sizeOf(); i++) {
    m_data[i] = 0;
  }
  m_isDefined = true;
}

MDArray::MDArray() {
  m_isDefined = false;
  m_data = nullptr;
}
MDArray::MDArray(Box a_box) {
  m_isDefined = false;
  m_data = nullptr;
  define(a_box);
}
MDArray &MDArray::operator=(const MDArray &a_MDArray) {
  if (this != &a_MDArray) {
    m_box = a_MDArray.m_box;
    m_isDefined = a_MDArray.m_isDefined;
    if (m_data != nullptr) {
      delete[] m_data;
    }
    m_data = new float[m_box.sizeOf()];
    for (int i = 0; i < m_box.sizeOf(); i++) {
      m_data[i] = a_MDArray.m_data[i];
    }
  }
  return *this;
}
MDArray::~MDArray() {
  if (m_data != nullptr) {
    delete[] m_data;
  }
}

/// a_rhs.box and this->box
void MDArray::operator+=(const MDArray &a_rhs) {
  if (!m_isDefined) {
    return;
  }
  Box intersection = m_box && a_rhs.m_box;
  if (intersection.sizeOf() != m_box.sizeOf()) {
    return;
  }
  for (int i = 0; i < m_box.sizeOf(); i++) {
    m_data[i] += a_rhs.m_data[i];
  }
}
/// pointwise subtraction operator.
void MDArray::operator-=(const MDArray &a_rhs) {
  if (!m_isDefined) {
    return;
  }
  Box intersection = m_box && a_rhs.m_box;
  if (intersection.sizeOf() != m_box.sizeOf()) {
    return;
  }
  for (int i = 0; i < m_box.sizeOf(); i++) {
    m_data[i] -= a_rhs.m_data[i];
  }
}
/// Pointwise multiplication operator.
void MDArray::operator*=(const MDArray &a_rhs) {
  if (!m_isDefined) {
    return;
  }
  Box intersection = m_box && a_rhs.m_box;
  if (intersection.sizeOf() != m_box.sizeOf()) {
    return;
  }
  for (int i = 0; i < m_box.sizeOf(); i++) {
    m_data[i] *= a_rhs.m_data[i];
  }
}
/// Pointwise division operator.
void MDArray::operator/=(const MDArray &a_rhs) {
  if (!m_isDefined) {
    return;
  }
  Box intersection = m_box && a_rhs.m_box;
  if (intersection.sizeOf() != m_box.sizeOf()) {
    return;
  }
  for (int i = 0; i < m_box.sizeOf(); i++) {
    m_data[i] /= a_rhs.m_data[i];
  }
}

/// Shift operator : general stencil form
MDArray &MDArray::shift(float weight, int a_dir, int a_distance) {
  MDArray temp(m_box);
  int tuple[DIM];
  for (int i = 0; i < m_box.sizeOf(); ++i) {
    m_box.tupleIndex(i, tuple);
    temp[tuple] = weight * indexShift(tuple, a_dir, a_distance);
    *this = temp;
  }
  return *this;
}
/// Shift operator : specialization for weight==1.0
MDArray &MDArray::shift(int a_dir, int a_distance) {
  return shift(1.0, a_dir, a_distance);
}

/// Indexing operator.
float &MDArray::operator[](int a_index[DIM]) const {
  assert(m_isDefined);
  return m_data[m_box.linearIndex(a_index)];
}

/// Indexing into 1D array representation of data.
float &MDArray::operator[](int a_linearIndex) const {
  assert(m_isDefined);
  return m_data[a_linearIndex];
}

/// Access the box.
const Box &MDArray::getBox() const { return m_box; }

/// Add a float to all elements.
void MDArray::operator+=(const float &a_rhs) {
  assert(m_isDefined);
  for (int i = 0; i < m_box.sizeOf(); i++) {
    m_data[i] += a_rhs;
  }
}
/// Subtract a float from all elements.
void MDArray::operator-=(const float &a_rhs) {
  if (!m_isDefined) {
    return;
  }
  for (int i = 0; i < m_box.sizeOf(); i++) {
    m_data[i] -= a_rhs;
  }
}
/// Multiply all elements by a scalar.
void MDArray::operator*=(const float &a_rhs) {
  if (!m_isDefined) {
    return;
  }
  for (int i = 0; i < m_box.sizeOf(); i++) {
    m_data[i] *= a_rhs;
  }
}
/// Divide all elements by a scalar.
void MDArray::operator/=(const float &a_rhs) {
  if (!m_isDefined) {
    return;
  }
  for (int i = 0; i < m_box.sizeOf(); i++) {
    m_data[i] /= a_rhs;
  }
}

/// a_rhs.box and this->box
MDArray MDArray::operator+(const MDArray &a_rhs) {
  MDArray retval;
  if (!m_isDefined) {
    return retval;
  }
  Box intersection = m_box && a_rhs.m_box;
  if (intersection.sizeOf() != m_box.sizeOf()) {
    return retval;
  }
  retval.define(m_box);

  for (int i = 0; i < m_box.sizeOf(); i++) {
    retval.m_data[i] = m_data[i] + a_rhs.m_data[i];
  }
}

float &MDArray::indexShift(const int a_tuple[DIM], const int &a_dir,
                           const int &a_shift) const {
  int shiftedTuple[DIM];
  for (int dir = 0; dir < DIM; dir++) {
    shiftedTuple[dir] = a_tuple[dir];
  }
  shiftedTuple[a_dir] += a_shift;
  return (*this)[shiftedTuple];
}
