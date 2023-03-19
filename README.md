# gabboy

A very basic Gameboy emulator for MacOS. Currently it can only run a specific version of the bootrom (DMG) and display LCD data (no sound).

For educational purposes only! Not for commercial use. (Not that it could ever be).

<img width="256" alt="image" src="https://user-images.githubusercontent.com/1648852/226152345-35df8a74-ae28-4308-99ec-218ae921d631.png">

## Why

I'm mostly experienced with high-level programming but I've always been interested in low-level stuff. However, it can be very daunting to start learning and documentation can be pretty obscure at times.

A few years ago, I [tried out](https://github.com/Lumbi/nand2tetris) the [From Nand to Tetris](https://www.nand2tetris.org/) course which really helped me understand how computers fundamentally work. I highly recommend it.

Fast-forward to now, while getting my hands dirty with C++ and optimization, my interest for low-level programming sparked again. With a bit of confidence and determination, I decided to take up the challenge and see how far I could go in implementing a Gameboy emulator.

## How

This is roughly how I went about it:

1. Read as much reference material as possible
2. Implement the instructions found in the bootrom one by one
3. Implement background tile map to LCD data mapping
4. Implement bridging to Swift and render

## Learnings

Implementing the instruction set was tedious but not too difficult in the end. Having tests helped immensely, especially when refactoring code.

I found that blindly implementing the instruction set is not enough. To fix bugs, I really had to understand what the bootrom was trying to do and how instructions played together. Understanding how the VRAM works and how the Gameboy handles graphic data was also crucial.

I'm very fortunate that there are so many good reference material out there nowadays. But there were sometimes discrepancies between documents so relying on the actual code itself was best.

## References:
- https://gekkio.fi/files/gb-docs/gbctr.pdf
- https://gbdev.io/gb-opcodes//optables/
- https://rylev.github.io/DMG-01/public/book/appendix/numbers.html
- https://www.chciken.com/tlmboy/2022/05/02/gameboy-boot.html
- https://github.com/ISSOtm/gb-bootroms
- https://gbdev.io/pandocs/Power_Up_Sequence.html
- https://gbdev.gg8.se/wiki/articles/Gameboy_Bootstrap_ROM
- https://gbdev.gg8.se/wiki/articles/Video_Display
- https://www.huderlem.com/demos/gameboy2bpp.html
- http://www.chebucto.ns.ca/~af380/z-80-g.htm
- https://www.copetti.org/writings/consoles/game-boy/

Special thanks to [gekkio](https://gekkio.fi/) for the useful technical reference manual with machine cycle timings.

Note: Game BoyTM, Game Boy PocketTM, Super Game BoyTM and Game Boy ColorTM are registered trademarks of Nintendo CO., LTD.
© 1989 to 1999 by Nintendo CO., LTD
