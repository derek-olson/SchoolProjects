//author Ben Jones

#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <cmath>

//some structs and functions that deal with image processing


//this ia forward declaration.  We can take a const DRGB& parameter
//in the RGB Constructor now that we've seen the name

struct DRGB; 
//a color stored as RGB
struct RGB{
  uint8_t r, g, b;
  //3 value constructor
  RGB(uint8_t _r, uint8_t _g, uint8_t _b)
	:r(_r), g(_g), b(_b) {}
  //create from a DRGB (see below)
  RGB(const DRGB& drgb);
  //defualt constructor = black
  RGB() :r(0), g(0), b(0) {}
};

//use doubles for more accurate math
struct DRGB {
  double r, g, b;
  DRGB(RGB rhs)
	:r(rhs.r), g(rhs.g), b(rhs.b)
  {}

  //scale
  DRGB& operator*=(double s){
	r*= s;
	g*= s;
	b*= s;
	return *this;
  }
  //add
  DRGB& operator+=(DRGB rhs){
	r += rhs.r;
	g += rhs.g;
	b += rhs.b;
	return *this;
  }
};

//other useful operator overloads overloads
inline DRGB operator*(DRGB c, double s){
  c *= s;
  return c;
}
inline DRGB operator*(double s, DRGB c){
  c *= s;
  return c;
}

inline DRGB operator+(DRGB lhs, DRGB rhs){
  lhs += rhs;
  return lhs;
}

//round the doubles to get ints to output
inline RGB::RGB(const DRGB& drgb)
  :r(std::round(drgb.r)), g(std::round(drgb.g)), b(std::round(drgb.b))
{}



class Image{

public:
  Image(const std::string& filename);

  void saveImage(const std::string& filename) const;

  //fill these in as outlined in the assignment description
  DRGB BlurredPixel(int row, int col) const;
  void blur();
  
  //could oveload operator() for this
  //can't use operator [] because we need to specify row and col
  RGB getColor(uint64_t row, uint64_t col) const;
  void setColor(uint64_t row, uint64_t col, RGB color);

  uint64_t getRows() const { return height;}
  uint64_t getCols() const { return width;}
  

private:
  uint64_t width, height;
  std::vector<RGB> data;

};


