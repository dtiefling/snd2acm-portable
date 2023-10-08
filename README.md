# snd2acm-portable
Sound to ACM converter based on The DragonLance Total Conversion Editor Pro
(DLTCEP) code.

For DLTCEP info and chandes, see `readme.txt` of its
[full branch](https://github.com/TeoTwawki/dltcep).

## Requirements

To run any script that converts from `acm`, you should have `ogg`, `vorbis`
and `vorbisfile` libraries in your system. Which you probably do in a desktop
system.

When in doubt, do you system equivalent of:
`sudo apt install libogg0 libvorbis0a libvorbisfile3`

To run any script that converts into `acm`, you should also have `ffmpeg`
in your path.

## Building

You need to have `-lvorbis -lvorbisfile -logg` libraries available.

`make`

Then you should get a set of scripts and links in `bin` that you can copy
wherever you like.

## Usage

Syntax such as:

`snd2acm input.wav output.acm`

`acm2snd input.acm output.wav`

Works for all the included tools.
