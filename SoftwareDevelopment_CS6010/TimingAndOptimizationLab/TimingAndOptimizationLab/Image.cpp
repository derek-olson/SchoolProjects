#include "Image.hpp"
#include <fstream>
#include <cassert>
#include <vector>

Image::Image(const std::string& filename){

  std::ifstream ins(filename, std::ios::binary);
  assert(ins.good());

  std::string magicNumber;
  ins >> magicNumber;
  assert(magicNumber == "P6" && "File must start with P6");

  ins >> width >> height;

  int maxColorVal;
  ins >> maxColorVal;
  assert(maxColorVal <= 255 && "We only work with 1-byte colors");

  ins.get(); //throw away the whitespace
  //need this many pixels
  data.resize(width*height);

  for(uint64_t row = 0; row < height; ++row){
	for(uint64_t col = 0; col < width; ++col){
	  RGB color;
	  color.r = ins.get();
	  color.g = ins.get();
	  color.b = ins.get();
	  setColor(row, col, color);
	}
  }
  
}

void Image::saveImage(const std::string& filename) const{
  std::ofstream outs(filename, std::ios::binary);

  outs << "P6\n" << width << ' ' << height << '\n' << 255 << '\n';
  for(uint64_t row = 0; row < height; ++row){
	for(uint64_t col = 0; col < width; ++col){
	  RGB color = getColor(row, col);
	  outs.put(color.r);
	  outs.put(color.g);
	  outs.put(color.b);
	}
  }
}



RGB Image::getColor(uint64_t row, uint64_t col) const{
  return data[row*width + col];
}

void Image::setColor(uint64_t row, uint64_t col, RGB color){
  data[row*width + col] = color;
}

DRGB Image::BlurredPixel(int row, int col) const{
    RGB out;
    DRGB blurred_value(out);
    DRGB color = getColor(row, col);
    int rowCoord = 0; int colCoord = 0;
    std::vector<int> rws = {-1,0,1};
    std::vector<int> cls = {-1,0,1};
    for (int r = 0; r < 3; r++){
        for (int c = 0; c < 3; c++){
            if (row + rws[r] < 0 || row + rws[r] > height){
                rowCoord = 0;
            }
            else if (col + cls[c] < 0 || col + cls[c] > width){
                colCoord = 0;
            }
            else{
                rowCoord = row + rws[r];
                colCoord = col + cls[c];
            }
            DRGB neighbor = getColor(rowCoord, colCoord);
            DRGB t = (0.5 * color) + (0.0625 * neighbor);
            blurred_value = RGB(t);
            //out = RGB(t);
        }
    }
//return out;
  return blurred_value;
}

//so you'll need to create and fill in a temporary vector and then replace the data member variable with it at the end of the method
void Image::blur(){
    RGB b;
    DRGB blurred(b);
    std::vector<RGB> tempVec;
    for (int row = 0; row < height; row++){
        for (int col = 0; col < width; col++){
            blurred = BlurredPixel(row, col);
            tempVec.push_back(RGB(blurred));
        }
    }
    data = tempVec;
}

