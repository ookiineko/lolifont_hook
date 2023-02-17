# lolifont_hook

[![GLWTPL](https://img.shields.io/badge/GLWT-Public_License-red.svg)](https://github.com/me-shaon/GLWTPL)

replace fonts with lolita ones

## Usage

set LD_PRELOAD to the shared library and execute the target program

## How it works

by hooking FreeType functions

## Bugs

- probably cannot replace all the fonts in some apps for some reason
- cannot handle font fallbacks (special characters may break due to this)

## Reference

[the original answer from a GitHub issue](https://github.com/ysc3839/FontMod/issues/6#issuecomment-343681260)
