
#ifndef rsdl_borgefors_h_
#define rsdl_borgefors_h_

// This is rpil/rsdl/rsdl_borgefors.h

//:
// \file
// \brief masked, templated borgefors distance map using 3-4 chamfer distance transform
// \author Charlene Tsai
// \date 5 May 2001
//
// Defines functions assocaited with a masked, templated borgefors 
// distance map. The user has the freedom to specify the map either masked or
// unmasked, and the data based on which the map is built is a vector 
// (should be changed to any stl container type later) of any 
// datatype with x() and y() functions defined. 

#include <vcl_stlfwd.h>
#include <vbl/vbl_array_2d.h>
#include <vil/vil_fwd.h>
#include <vil/vil_byte.h>

//: Defines functions assocaited with a masked, templated borgefors 
//  distance map. The user has the freedom to specify the map either masked or
//  unmasked, and the data based on which the map is built is a vector 
//  (should be changed to any stl container type later) of any 
//  datatype with x() and y() functions defined. 
//
//  The computation of the distance map is done using 3-4 chamfer distance 
//  transform. 
//
//  CAVEAT: 
//  To avoid data duplication, objects are stored as pointers in the map.
//  Classes having rsdl_borgefors as the internal data should recompute
//  the borgefor map when define the copy constructor and operator= 
//  To enforce this, the copy constructor and the operator= of rsdl_borgefors
//  are not implemented and are private member functions to avoid default ones
//  being generated by the compiler.
//   
template <class T>
class rsdl_borgefors {
  typedef vcl_vector<T>::iterator iterator_type;

public:
  //: \brief default constructor
  rsdl_borgefors();
  //: \brief constructor: constructs unmasked distance map, with dimensions set by size_x and size_y
  rsdl_borgefors(int org_x, int org_y, int size_x, int size_y, 
		  iterator_type begin, iterator_type end, bool release_dist_map = false);
  //: \brief sets distance and index maps, with dimensions set by size_x and size_y  
  //  \param start_x x-coord of the top left corner
  //  \param start_y y-coord of the top left corner
  //  \param size_x x dimension
  //  \param size_y y dimension
  //  \param begin begin ptr of the data vector
  //  \param end end ptr of the data vector
  void set(int org_x, int org_y, int size_x, int size_y, 
	   iterator_type begin, iterator_type end, bool release_dist_map = false);

  //: \brief sets all data members from the caller
  //  \param start_x x-coord of the top left corner
  //  \param start_y y-coord of the top left corner
  //  \param size_x x dimension
  //  \param size_y y dimension
  //  \param begin begin ptr of the data vector
  //  \param end end ptr of the data vector
  //  \param distance_map distance map
  //  \param index_map index map
  void set(int org_x, int org_y, int size_x, int size_y, 
	   iterator_type begin, iterator_type end,
	   vbl_array_2d<int> index_map,
           vbl_array_2d<int>* distance_map = 0 );

  //: \brief resets the data members
  void reset();
  //: \brief returns true if the map contains valid data
  bool is_valid() {return is_valid_;}

  //: \brief returns approximated distance to between (x,y) and 
  //  closest object in the map
  double distance(int x, int y) const;
  //: \brief verifies if (x,y) position is valid in the map
  bool in_map(int x, int y) const;
  //: \brief returns a pointer to the closest object to (x,y) in the map
  //  It aborts if (x,y) not in map. Should always check in_map(x,y) first.
  const iterator_type nearest(int x, int y) const;

  //: \brief returns width of the map
  int width() const {return size_x_; }
  //: \brief returns height of the map
  int height()const {return  size_y_; }

  //: \brief returns origin of the map
  void origin(int& start_x, int& start_y);

  const vbl_array_2d<int>& distance_map() const {return distance_map_; }
  const vbl_array_2d<int>& index_map() const {return index_map_; }

  //: \brief equal operator
  bool operator== (const rsdl_borgefors<T> & rhs) const;
  
private:
  //: \brief copy constructor, not implemented 
  rsdl_borgefors(const rsdl_borgefors<T>& old);  
  //: \brief assignment operator, not implemented 
  rsdl_borgefors<T>& operator=(const rsdl_borgefors<T>& rhs);   


  void initialize(iterator_type  begin, iterator_type end);
  void chamfer34();
  void forward_chamfer();
  void backward_chamfer();
  int minimum5(int,int,int,int,int);
  void mask_maps(const vil_memory_image_of<vil_byte>& mask);

private:
  bool is_valid_;
  int org_x_, org_y_, size_x_, size_y_;
  vbl_array_2d<int> distance_map_;
  vbl_array_2d<int> index_map_;
  vcl_vector<iterator_type> data_;
};

#endif
