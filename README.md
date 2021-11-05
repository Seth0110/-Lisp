# µLisp

## Overview

µLisp is a simple Lisp implementation written in C.
Its aim is to have as small of an implementation language corpus as possible (without code obfuscation),
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
- More error handling, program should never segfault!
- Garbage collection
- (load "module.scm") function
- Automatically import a base library
- Comprehensive testing suite
- Homebrew readline library, to remove the dependency and to support 'λ'!
- Tail recursion
- More optimization from SICP
- geiser-ulisp emacs package
- Full R7RS-small compatibility

## Known Bugs

- MANY memory leaks
- ' only works for atoms
- Definitions with closures only return "ok"

## Attribution

µLisp at its core is a C implementation of Lisp as defined in [Structure and Interpretation of Computer Programs](https://mitpress.mit.edu/sites/default/files/sicp/full-text/book/book.html) by Ableson, Sussman, and Sussman, licensed under [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/).
