# µLisp

## Overview

µLisp is a simple Lisp implementation.

## Requirements

This program depends upon BSD editline,
which can be installed on Debian-based distros via the `libedit-dev` package.

## Installation

Run the following command to install µLisp:

`sudo make install`
	
## Running

Start the interactive prompt with `ulisp`.

To run a µLisp file, pipe via stdin.  
Example: `<test.ul ulisp`

## Attribution

µLisp at its core is a C implementation of Lisp as defined in [Structure and Interpretation of Computer Programs](https://mitpress.mit.edu/sites/default/files/sicp/full-text/book/book.html) by Ableson, Sussman, and Sussman, licensed under [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/).

## Todo

- [x] Implement Pure Lisp with Lisp 1.5 Programmer's Manual as reference
- [x] Finish Parser
- [x] Switch existing code to SICP implementation
- [x] All core operations functional
- [ ] Replace `int is_eq(lisp *, char *)` with `int is_eq(lisp *, lisp *)`
- [ ] Fix memory leaks
- [ ] Add support for multi-line expressions
- [ ] Add `let` and `define` syntactic sugar
- [ ] Refactor implementation to simplify
- [ ] Refactor primitives to use a data-directed method for easier modification
- [ ] Add support for mathematics
- [ ] Additional libraries as needed
- [ ] Full testing for core Lisp and libraries
