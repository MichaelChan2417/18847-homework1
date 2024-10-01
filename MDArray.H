#ifndef _MDARRAY_H_
#define _MDARRAY_H_
#include "Box.H"

/**
  A mapping from a Box to scalar floating-point values
*/
class MDArray {
public:
  /// Default constructor.
  MDArray();
  /// Constructs an MDArray over the Box a_Box;
  MDArray(Box a_box);
  /// Defines a default-constructed MDArray.
  void define(Box a_box);
  /// Destructor.
  ~MDArray();

  /// Pointwise addition operator. operation performed on intersection of
  /// a_rhs.box and this->box
  void operator+=(const MDArray &a_rhs);
  /// pointwise subtraction operator.
  void operator-=(const MDArray &a_rhs);
  /// Pointwise multiplication operator.
  void operator*=(const MDArray &a_rhs);
  /// Pointwise division operator.
  void operator/=(const MDArray &a_rhs);

  /// Shift operator : general stencil form
  MDArray &shift(float weight, int a_dir, int a_distance);
  /// Shift operator : specialization for weight==1.0
  MDArray &shift(int a_dir, int a_distance);
  /// Indexing operator.
  float &operator[](int a_index[DIM]) const;
  /// Indexing shifted operator.
  float &indexShift(const int a_tuple[DIM], const int &a_dir,
                    const int &a_shift) const;
  /// Indexing into 1D array representation of data.
  float &operator[](int a_linearIndex) const;
  /// Access the box.
  const Box &getBox() const;
  /// Add a float to all elements.
  void operator+=(const float &a_rhs);
  /// Subtract a float from all elements.
  void operator-=(const float &a_rhs);
  /// Multiply all elements by a scalar.
  void operator*=(const float &a_rhs);
  /// Divide all elements by a scalar.
  void operator/=(const float &a_rhs);

  /// Pointwise addition operator. operation performed on intersection of
  /// a_rhs.box and this->box
  MDArray operator+(const MDArray &a_rhs);

private:
  float *m_data;
  Box m_box;
  bool m_isDefined;
  /// we make copy constructors, assignment operators private to prevent their
  /// use.
  MDArray(const MDArray &a_MDArray);
  MDArray &operator=(const MDArray &a_MDArray);
};

#endif
