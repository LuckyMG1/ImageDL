# ImageDL
## File downloader written in C
A purely C-based wget-like tool that downloads files from remote HTTP servers.

## Description
The core idea behind this project is to implement my own program with a behavior akin to *wget*, or *curl*.
First and foremost, the goal is to further familiarize myself with the POSIX standard, and, secondly, to build some form of a portfolio.

Future versions of the project will have support for HTTPS, and a universal file format, not just images.
If anyone is interested in developing this, which should not take excessively long, open a pull request.

## Installation

### Build from source
The project can be compiled directly from the Makefile:
```
git clone https://github.com/LuckyMG1/ImageDL.git
cd ImageDL
sudo make install
```
## Usage
The program downloads files by reading the url from STDIN:
```
imagedl <url>
```
## License
MIT License

Copyright (c) 2025 LuckyMG 
