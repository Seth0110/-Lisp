# µLisp

## Overview

µLisp, or Micro Lisp, is an implementation of Lisp as defined by the [Lisp 1.5 Programmer's Manual](http://web.cse.ohio-state.edu/~rountev.1/6341/pdf/Manual.pdf).

## Dependencies

This program depends upon BSD editline,
which can be installed on Debian-based distros via the `libedit-dev` package.

## Building and Running

Use `make` and `./repl` to run the interactive prompt.

To run a µLisp file, pipe via stdin: `<test.ul ./repl`

## Todo

- [x] Implement Pure Lisp
- [x] Finish Parser
- [ ] Complete 1.5 Manual implementation
- [ ] Additional libraries
- [ ] Testing for core Lisp and libraries
