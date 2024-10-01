#ifndef _BOX_H_
#define _BOX_H_

#ifndef DIM
#define DIM 2
#endif

/**
  A set of elements of Z^D that are contiguous in each dimension
*/
class Box {
public:
  /// Null Constructor
  Box();

  /// constructor for nontrivial Box.
  Box(const int a_lowCorner[DIM], const int a_highCorner[DIM]);

  /// copy constructor.
  Box(const Box &a_Box);

  ///  Computes the intersection of the Box with rightBox.
  Box operator&&(const Box &a_rightBox) const;

  /// Computes shifted Box by a_offset in direction a_direction.
  Box shift(int a_direction, int a_offset) const;

  /// Grow in all of the coordinate directions by a_numpoints.
  Box grow(int a_numpoints);

  /// Access functions for low bounds of Box.
  void getLowCorner(int a_lowercorner[DIM]) const;

  /// Access functions for high bounds of Box.
  void getHighCorner(int a_highercorner[DIM]) const;
  /// Computes a linear index corresponding to the input array.
  int linearIndex(const int a_tupleIndex[DIM]) const;

  /// Computes a tuple corresponding to a linear location.
  void tupleIndex(int a_linearIndex, int a_tupleIndex[DIM]) const;

  /// Computes the size of the Box.
  int sizeOf() const;

  /// true is both Boxes have identical low and high bounds
  bool operator==(const Box &a_rhsBox) const;
  /// prints Box to STDOUT.
  void print() const;

  /// This box is the empty set.  It has no points in the set Z^DIM
  bool isEmpty() const;

  /// is the tupleIndex in the set defined by this Box
  bool contains(const int tupleIndex[DIM]) const;

private:
  int m_lowCorner[DIM], m_highCorner[DIM];
};

inline int intMin(int a, int b) {
  if (a > b)
    return b;
  return a;
}

inline int intMax(int a, int b) {
  if (a > b)
    return a;
  return b;
}
#endif
