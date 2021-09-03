# µLisp

## Overview

µLisp is a simple Lisp implementation written in C.
Its aim is to be as small as possible while maintaining code readability,
as well as a new language for future personal projects.

## Requirements

This program depends upon BSD editline,
which can be installed on Debian-based distros via the `libedit-dev` package.

## Installation

Run the following command to install µLisp:

`sudo make install`

Run the following command to uninstall µLisp:

`sudo make uninstall`
	
## Running

Start the interactive prompt with `ulisp`.

To run a µLisp file, pipe via stdin.  
Example: `<test.ul ulisp`

## Todo

- Add `let` syntactic sugar
- More error handling, program should never segfault
- Fix memory leaks... Or build a garbage collector
- Automatically import a base library
- Implement SICP analyze function
- Comprehensive testing suite
- Homebrew readline library, to remove the dependency and to support 'λ'!
- Tail recursion
- R7RS-small compatibility
- geiser-ulisp emacs package

## Known Bugs

- Define within define is still global
- ' doesn't parse correctly
- Recursion doesn't carry over environment

## Attribution

µLisp at its core is a C implementation of Lisp as defined in [Structure and Interpretation of Computer Programs](https://mitpress.mit.edu/sites/default/files/sicp/full-text/book/book.html) by Ableson, Sussman, and Sussman, licensed under [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/).
