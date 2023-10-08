# snd2acm-portable
Sound to ACM converter based on The DragonLance Total Conversion Editor Pro
(DLTCEP) code.

For DLTCEP info and chandes, see `readme.txt` of its
[full branch](https://github.com/TeoTwawki/dltcep).

## Requirements

You need to have `-lvorbis -lvorbisfile -logg` libraries available.

To run any script that converts into `acm`, you should also have `ffmpeg`
in your path.

## Building

`make`

Then you should get a set of scripts and links in `bin` that you can copy
wherever you like.

## Usage

Syntax such as:

`snd2acm input.wav output.acm`
`acm2snd input.acm output.wav`

Works for all the included tools.
