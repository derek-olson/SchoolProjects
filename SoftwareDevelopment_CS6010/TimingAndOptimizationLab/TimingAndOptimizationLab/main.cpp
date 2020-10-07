#include "Image.hpp"
#include <iostream>



//uint64_t getBrightness(Image im){
//
//  uint64_t count = 0;
//  for(uint64_t col = 0; col < im.getCols(); ++col){
//    for(uint64_t row = 0; row < im.getRows(); ++row){
//
//      RGB color = im.getColor(row, col);
//      count += color.r;
//    }
//  }
//  for(uint64_t col = 0; col < im.getCols(); ++col){
//    for(uint64_t row = 0; row < im.getRows(); ++row){
//
//      RGB color = im.getColor(row, col);
//      count += color.g;
//    }
//  }
//  for(uint64_t col = 0; col < im.getCols(); ++col){
//    for(uint64_t row = 0; row < im.getRows(); ++row){
//
//      RGB color = im.getColor(row, col);
//      count += color.b;
//    }
//  }
//
//
//  return static_cast<uint8_t>(static_cast<double>(count)/(3*im.getRows()*im.getCols()));
//}


uint64_t getBrightness2(const Image& im){
    uint64_t count = 0;
    for(uint64_t row = 0; row < im.getRows(); ++row){
        for(uint64_t col = 0; col < im.getCols(); ++col){
            
            RGB color = im.getColor(row, col);
            count += color.r;
            count += color.g;
            count += color.b;
        }
    }
    return static_cast<uint8_t>(static_cast<double>(count)/(3*im.getRows()*im.getCols()));
}

void halfDomeTests(){
 Image image("HalfDomeBinary.ppm");
 //repeat 20x so that it's easier to profile
// double brightness = 0;
 double brightness2 = 0;
 for(int i = 0; i < 20; ++i){
//   brightness += getBrightness(image);
   brightness2 += getBrightness2(image);
 }
 
// std::cout << "avg brightness: " << brightness/20 << std::endl;
 std::cout << "avg brightness: " << brightness2/20 << std::endl;
}

void POMTest(){

  Image image("POM.ppm");
  for(int i = 0; i < 60; ++i){
	std::cout << "blur pass " << i << std::endl;
	image.blur();
  }
  image.saveImage("POMOut.ppm"); 
}


int main(){

  //halfDomeTests();
  POMTest();

  return 0;
}
