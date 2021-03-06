#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "ShpFile.h"
#include "PaletteFile.h"
#include "ImageHeader.h"
#include "PaletteEntry.h"



TEST_CASE("Can read palette entries", "[SHP]") {
	// Given
	PaletteFile paletteFile(std::string("assets/temperat.pal"));

	// then
	REQUIRE(paletteFile.GetPaletteEntries().size() == 256);

	REQUIRE(paletteFile.GetPaletteEntries()[0]->GetRed() == 0);
	REQUIRE(paletteFile.GetPaletteEntries()[0]->GetGreen() == 0);
	REQUIRE(paletteFile.GetPaletteEntries()[0]->GetBlue() == 0);

	REQUIRE(paletteFile.GetPaletteEntries()[1]->GetRed() == 0x2a);
	REQUIRE(paletteFile.GetPaletteEntries()[1]->GetGreen() == 0);
	REQUIRE(paletteFile.GetPaletteEntries()[1]->GetBlue() == 0x2a);

	REQUIRE(paletteFile.GetPaletteEntries()[254]->GetRed() == 0x21);
	REQUIRE(paletteFile.GetPaletteEntries()[254]->GetGreen() == 0x22);
	REQUIRE(paletteFile.GetPaletteEntries()[254]->GetBlue() == 0x1d);

	REQUIRE(paletteFile.GetPaletteEntries()[255]->GetRed() == 0x3f);
	REQUIRE(paletteFile.GetPaletteEntries()[255]->GetGreen() == 0x3f);
	REQUIRE(paletteFile.GetPaletteEntries()[255]->GetBlue() == 0x3f);

}


TEST_CASE("Can parse width and height from SHP file", "[SHP]") {
	// Given
	ShpFile shpFile(std::string("assets/e1.shp"));

	// then
	REQUIRE(shpFile.Size() == 40105);
	REQUIRE(shpFile.NumberOfImages() == 532);
	REQUIRE(shpFile.Width() == 50);
	REQUIRE(shpFile.Height() == 39);

	REQUIRE(shpFile.ImageHeaders().size() == 532);

	REQUIRE(shpFile.ImageHeaders()[0]->GetFileOffset() == 4286);
	REQUIRE(shpFile.ImageHeaders()[0]->GetFormat() == LCW);
	REQUIRE(shpFile.ImageHeaders()[0]->GetRefOffset() == 0);
	REQUIRE(shpFile.ImageHeaders()[0]->GetRefFormat() == NONE);


	REQUIRE(shpFile.GetShpBytesFileOffset() == 4286);
	REQUIRE(shpFile.GetShpBytes().size() == 35819);
	REQUIRE(shpFile.GetShpBytes()[0] == 129);
	
	REQUIRE(shpFile.ImageHeaders()[0]->GetData().size() == 1950);
	REQUIRE(shpFile.ImageHeaders()[0]->GetData()[0] == 0);
	REQUIRE(shpFile.ImageHeaders()[0]->GetData()[474] == 179);
	REQUIRE(shpFile.ImageHeaders()[0]->GetData()[475] == 180);
	REQUIRE(shpFile.ImageHeaders()[0]->GetData()[524] == 180);
	REQUIRE(shpFile.ImageHeaders()[0]->GetData()[525] == 181);

	REQUIRE(shpFile.ImageHeaders()[0]->GetData()[974] == 13);
	REQUIRE(shpFile.ImageHeaders()[0]->GetData()[975] == 12);
	REQUIRE(shpFile.ImageHeaders()[0]->GetData()[976] == 13);

	REQUIRE(shpFile.ImageHeaders()[0]->GetData()[1948] == 0);
	REQUIRE(shpFile.ImageHeaders()[0]->GetData()[1949] == 0);


	REQUIRE(shpFile.ImageHeaders()[1]->GetFileOffset() == 4375);
	REQUIRE(shpFile.ImageHeaders()[1]->GetFormat() == XORLCW);
	REQUIRE(shpFile.ImageHeaders()[1]->GetRefOffset() == 4286);  
	REQUIRE(shpFile.ImageHeaders()[1]->GetRefFormat() == 32768);

	REQUIRE(shpFile.ImageHeaders()[1]->GetData().size() == 1950);
	REQUIRE(shpFile.ImageHeaders()[1]->GetData()[472] == 0);
	REQUIRE(shpFile.ImageHeaders()[1]->GetData()[473] == 180);
	REQUIRE(shpFile.ImageHeaders()[1]->GetData()[474] == 179);
	REQUIRE(shpFile.ImageHeaders()[1]->GetData()[475] == 0);
	REQUIRE(shpFile.ImageHeaders()[1]->GetData()[1030] == 4);


	REQUIRE(shpFile.ImageHeaders()[4]->GetFileOffset() == 4609);
	REQUIRE(shpFile.ImageHeaders()[4]->GetFormat() == XORLCW);
	REQUIRE(shpFile.ImageHeaders()[4]->GetRefOffset() == 4286);
	REQUIRE(shpFile.ImageHeaders()[4]->GetRefFormat() == 32768);

	REQUIRE(shpFile.ImageHeaders()[5]->GetFileOffset() == 4687);
	REQUIRE(shpFile.ImageHeaders()[5]->GetFormat() == XORPrev);
	REQUIRE(shpFile.ImageHeaders()[5]->GetRefOffset() == 4);
	REQUIRE(shpFile.ImageHeaders()[5]->GetRefFormat() == 18432);

	REQUIRE(shpFile.ImageHeaders()[5]->GetData().size() == 1950);
	REQUIRE(shpFile.ImageHeaders()[5]->GetData()[473] == 0);
	REQUIRE(shpFile.ImageHeaders()[5]->GetData()[474] == 179);
	REQUIRE(shpFile.ImageHeaders()[5]->GetData()[475] == 180);
	REQUIRE(shpFile.ImageHeaders()[5]->GetData()[476] == 0);

	REQUIRE(shpFile.ImageHeaders()[5]->GetData()[972] == 0);
	REQUIRE(shpFile.ImageHeaders()[5]->GetData()[973] == 12);
	REQUIRE(shpFile.ImageHeaders()[5]->GetData()[977] == 4);


	REQUIRE(shpFile.ImageHeaders()[531]->GetFileOffset() == 40021);
	REQUIRE(shpFile.ImageHeaders()[531]->GetFormat() == LCW);
	REQUIRE(shpFile.ImageHeaders()[531]->GetRefOffset() == 0);
	REQUIRE(shpFile.ImageHeaders()[531]->GetRefFormat() == NONE);

}


TEST_CASE("Can parse data from multiple frames in SHP file", "[SHP]") {
	// Given
	ShpFile shpFile(std::string("assets/select.shp"));

	// then
	REQUIRE(shpFile.Size() == 383);
	REQUIRE(shpFile.NumberOfImages() == 4);
	REQUIRE(shpFile.Width() == 24);
	REQUIRE(shpFile.Height() == 21);

	REQUIRE(shpFile.ImageHeaders().size() == 4);

	REQUIRE(shpFile.ImageHeaders()[0]->GetFileOffset() == 62);
	REQUIRE(shpFile.ImageHeaders()[0]->GetFormat() == LCW);
	REQUIRE(shpFile.ImageHeaders()[0]->GetRefOffset() == 0);
	REQUIRE(shpFile.ImageHeaders()[0]->GetRefFormat() == NONE);

	REQUIRE(shpFile.ImageHeaders()[0]->GetData().size() == 504);
	REQUIRE(shpFile.ImageHeaders()[0]->GetData()[0] == 0);
	REQUIRE(shpFile.ImageHeaders()[0]->GetData()[81] == 0);
	REQUIRE(shpFile.ImageHeaders()[0]->GetData()[82] == 15);
	REQUIRE(shpFile.ImageHeaders()[0]->GetData()[83] == 15);
	REQUIRE(shpFile.ImageHeaders()[0]->GetData()[84] == 15);
	REQUIRE(shpFile.ImageHeaders()[0]->GetData()[85] == 0);


	REQUIRE(shpFile.ImageHeaders()[1]->GetFileOffset() == 100);
	REQUIRE(shpFile.ImageHeaders()[1]->GetFormat() == LCW);
	REQUIRE(shpFile.ImageHeaders()[1]->GetRefOffset() == 0);
	REQUIRE(shpFile.ImageHeaders()[1]->GetRefFormat() == NONE);

	REQUIRE(shpFile.ImageHeaders()[1]->GetData().size() == 504);
	REQUIRE(shpFile.ImageHeaders()[1]->GetData()[0] == 0);
	REQUIRE(shpFile.ImageHeaders()[1]->GetData()[54] == 0);
	REQUIRE(shpFile.ImageHeaders()[1]->GetData()[55] == 15);
	REQUIRE(shpFile.ImageHeaders()[1]->GetData()[56] == 15);
	REQUIRE(shpFile.ImageHeaders()[1]->GetData()[57] == 15);
	REQUIRE(shpFile.ImageHeaders()[1]->GetData()[58] == 15);
	REQUIRE(shpFile.ImageHeaders()[1]->GetData()[59] == 15);
	REQUIRE(shpFile.ImageHeaders()[1]->GetData()[60] == 0);



}




//  Examples
//
//SCENARIO("vectors can be sized and resized", "[vector]") {
//
//	GIVEN("A vector with some items") {
//		std::vector<int> v(5);
//
//		REQUIRE(v.size() == 5);
//		REQUIRE(v.capacity() >= 5);
//
//		WHEN("the size is increased") {
//			v.resize(10);
//
//			THEN("the size and capacity change") {
//				REQUIRE(v.size() == 10);
//				REQUIRE(v.capacity() >= 10);
//			}
//		}
//		WHEN("the size is reduced") {
//			v.resize(0);
//
//			THEN("the size changes but not capacity") {
//				REQUIRE(v.size() == 0);
//				REQUIRE(v.capacity() >= 5);
//			}
//		}
//		WHEN("more capacity is reserved") {
//			v.reserve(10);
//
//			THEN("the capacity changes but not the size") {
//				REQUIRE(v.size() == 5);
//				REQUIRE(v.capacity() >= 10);
//			}
//		}
//		WHEN("less capacity is reserved") {
//			v.reserve(0);
//
//			THEN("neither size nor capacity are changed") {
//				REQUIRE(v.size() == 5);
//				REQUIRE(v.capacity() >= 5);
//			}
//		}
//	}
//}



//unsigned int Factorial(unsigned int number);
//
//TEST_CASE("Factorials are computed", "[factorial]") {
//	REQUIRE(Factorial(1) == 1);
//	REQUIRE(Factorial(2) == 2);
//	REQUIRE(Factorial(3) == 6);
//	REQUIRE(Factorial(10) == 3628800);
//}
//
