//#include "tbitfield.h"
//#include <time.h>
#include <iostream>
//#include <chrono>

//#define OR

int main()
{
//	TBitField A100(100);
//	TBitField B100(100);
//	for(int i = 0; i < 100; i++)
//		if (i % 2 == 0)
//		{
//			A100.SetBit(i);
//			B100.SetBit(i);
//		}
//	TBitField A1000(1000);
//	TBitField B1000(1000);
//	for (int i = 0; i < 1000; i++)
//		if (i % 2 == 0)
//		{
//			A1000.SetBit(i);
//			B1000.SetBit(i);
//		}
//	TBitField A10000(10000);
//	TBitField B10000(10000);
//	for (int i = 0; i < 10000; i++)
//		if (i % 2 == 0)
//		{
//			A10000.SetBit(i);
//			B10000.SetBit(i);
//		}
//	TBitField A100000(100000);
//	TBitField B100000(100000);
//	for (int i = 0; i < 100000; i++)
//		if (i % 2 == 0)
//		{
//			A100000.SetBit(i);
//			B100000.SetBit(i);
//		}
	#ifdef OR
	auto begin = std::chrono::high_resolution_clock::now();
	A100 & B100;
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "100 elements - " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "ns" << std::endl;
	begin = std::chrono::high_resolution_clock::now();
	A1000 & B1000;
	end = std::chrono::high_resolution_clock::now();
	std::cout << "1000 elements - " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "ns" << std::endl;
	begin = std::chrono::high_resolution_clock::now();
	A10000 & B10000;
	end = std::chrono::high_resolution_clock::now();
	std::cout << "10000 elements - " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "ns" << std::endl;
	begin = std::chrono::high_resolution_clock::now();
	A100000 & B100000;
	end = std::chrono::high_resolution_clock::now();
	std::cout << "100000 elements - " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "ns" << std::endl;
	//#else
	auto begin = std::chrono::high_resolution_clock::now();
	~A100;
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "100 elements - " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "ns" << std::endl;
	begin = std::chrono::high_resolution_clock::now();
	~A1000;
	end = std::chrono::high_resolution_clock::now();
	std::cout << "1000 elements - " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "ns" << std::endl;
	begin = std::chrono::high_resolution_clock::now();
	~A10000;
	end = std::chrono::high_resolution_clock::now();
	std::cout << "10000 elements - " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "ns" << std::endl;
	begin = std::chrono::high_resolution_clock::now();
	~A100000;
	end = std::chrono::high_resolution_clock::now();
	std::cout << "100000 elements - " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "ns" << std::endl;
	#endif
    return 0;
}