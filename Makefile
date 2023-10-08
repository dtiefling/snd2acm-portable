CXXFLAGS += -Wno-unused-result -Wno-stringop-overflow

all: bin/snd2acm bin/acm2wav bin/wavc2snd bin/wavc2wav bin/acm2snd bin/wav2acm bin/snd2wavc bin/wav2wavc

bin/snd2acm.bin: src/main-snd2acm.cpp src/snd2acm.cpp src/readers.cpp src/subband.cpp src/packer.cpp src/riffhdr.cpp src/bitstream.cpp src/unpacker.cpp src/decoder.cpp src/utils.cpp src/portable-utils.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ -lm

bin/snd2acm: bin/snd2acm.bin
	cp -f sh/snd2acm $@

bin/acm2snd.bin: src/main-acm2snd.cpp src/acm2snd.cpp src/riffhdr.cpp src/readers.cpp src/unpacker.cpp src/decoder.cpp src/portable-utils.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ -lm -lvorbis -lvorbisfile -logg

bin/acm2snd: bin/acm2snd.bin
	cp -f sh/acm2snd $@

bin/acm2wav: bin/snd2acm
	ln -sfr bin/snd2acm.bin $@.bin
	ln -sfr bin/snd2acm $@

bin/wavc2snd: bin/snd2acm
	ln -sfr bin/snd2acm.bin $@.bin
	ln -sfr bin/snd2acm $@

bin/wavc2wav: bin/snd2acm
	ln -sfr bin/snd2acm.bin $@.bin
	ln -sfr bin/snd2acm $@

bin/wav2acm: bin/acm2snd
	ln -sfr bin/acm2snd.bin $@.bin
	ln -sfr bin/acm2snd $@

bin/snd2wavc: bin/acm2snd
	ln -sfr bin/acm2snd.bin $@.bin
	ln -sfr bin/acm2snd $@

bin/wav2wavc: bin/acm2snd
	ln -sfr bin/acm2snd.bin $@.bin
	ln -sfr bin/acm2snd $@

clean:
	$(RM) bin/*
