CPP = g++
MAGICK++_CONFIG = `Magick++-config --cppflags --cxxflags --ldflags --libs`
all: test

test: test.cpp
	$(CPP) test.cpp -o test $(MAGICK++_CONFIG)

clean:
	rm test
