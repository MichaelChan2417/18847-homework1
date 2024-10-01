CXX = g++
# CXX = clang++
CXXFLAGS = -g -DDIM=2
#CXXFLAGS = -O3 -DDIM=2

D1 = -DDIM=1 -Wno-macro-redefined
D3 = -DDIM=3 -Wno-macro-redefined

all:a.out boxTester.exe boxTester1D.exe boxTester3D.exe

run: all
	./boxTester.exe
	./boxTester1D.exe
	./boxTester3D.exe
	./a.out 16 16
	./a.out 32 32
	./a.out 64 64

a.out: MDArray.H Box.H MDArray.o Box.o mdarrayMain.o
	$(CXX) $(CXXFLAGS) MDArray.o Box.o mdarrayMain.o

boxTester.exe:Box.o boxTester.o
	$(CXX) $(CXXFLAGS) -o boxTester.exe Box.o boxTester.o 

boxTester.o:Box.H boxTester.cpp
	$(CXX) $(CXXFLAGS) -c -o boxTester.o boxTester.cpp

MDArray.o: MDArray.H Box.H MDArray.cpp
	$(CXX) $(CXXFLAGS) -c -g -o MDArray.o MDArray.cpp

Box.o: Box.H Box.cpp
	$(CXX) $(CXXFLAGS) -c -g -o Box.o Box.cpp

mdarrayMain.o: mdarrayMain.cpp Box.H MDArray.H
	$(CXX) $(CXXFLAGS) -c -g -o mdarrayMain.o mdarrayMain.cpp

Box1D.o: Box.H Box.cpp
	$(CXX) $(CXXFLAGS) $(D1) -c -g -o Box1D.o Box.cpp

boxTester1D.o:Box.H boxTester.cpp
	$(CXX) $(CXXFLAGS) $(D1) -c -o boxTester1D.o boxTester.cpp

boxTester1D.exe:Box1D.o boxTester1D.o
	$(CXX) $(CXXFLAGS) -o boxTester1D.exe Box1D.o boxTester1D.o 

Box3D.o: Box.H Box.cpp
	$(CXX) $(CXXFLAGS) $(D3) -c -g -o Box3D.o Box.cpp

boxTester3D.o:Box.H boxTester.cpp
	$(CXX) $(CXXFLAGS) $(D3) -c -o boxTester3D.o boxTester.cpp

boxTester3D.exe:Box3D.o boxTester3D.o
	$(CXX) $(CXXFLAGS) -o boxTester3D.exe Box3D.o boxTester3D.o 

docs: Box.H MDArray.H doxygen.config
	doxygen doxygen.config
clean:
	rm *.o a.out *.exe
