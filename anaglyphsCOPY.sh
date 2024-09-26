g++ anaglyphsCOPY.cpp -fopenmp `pkg-config opencv4 --cflags` -c
g++ anaglyphsCOPY.o  -fopenmp `pkg-config opencv4 --libs` -lstdc++ -o anaglyphsCOPY

# Use this to run 
# ./anaglyphsCOPY "Gray Anaglyph"

