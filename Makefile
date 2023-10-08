CXX = g++
CXXFLAGS += -Wno-unused-result -Wno-stringop-overflow

all: snd2acm.bin acm2snd.bin

snd2acm.bin: src/main-snd2acm.cpp src/snd2acm.cpp src/readers.cpp src/subband.cpp src/packer.cpp src/riffhdr.cpp src/bitstream.cpp src/unpacker.cpp src/decoder.cpp src/utils.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

acm2snd.bin: src/acm2snd.cpp src/riffhdr.cpp src/readers.cpp src/unpacker.cpp src/decoder.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ -lvorbis -lvorbisfile -logg

clean:
	rm -f *.bin
