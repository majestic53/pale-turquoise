LIBPTCE
========

LIBPTCE (Pale Turquoise Chess Engine) is a lightwight chess bot, written in C++.

Table of Contents
===============

1. [Changelog](https://github.com/majestic53/pale-turquoise#changelog)
2. [Usage](https://github.com/majestic53/pale-turquoise#usage)
2. [License](https://github.com/majestic53/pale-turquoise#license)

Changelog
=========

###Version 0.1.1507
*Updated: 2/11/2015*

* Added cli interface
* Updated readme

*Updated: 2/9/2015*

* Added cli interface (partial)
* Added game manager unit tests
* Truncated changelog (1504 - before)

###Version 0.1.1506
*Updated: 2/8/2015*

* Added basic (random) gameplay

*Updated: 2/5/2015*

* Added generate move routine (partial)

*Updated: 2/3/2015*

* Added game manager client handler

*Updated: 2/2/2015*

* Added game manager client handler (partial)
* Minor bug fixes

###Version 0.1.1505
*Updated: 1/30/2015*

* Added game manager client handler (partial)
* Cropped changelist

*Updated: 1/29/2015*

* Added client connection handler (partial)
* Added additional chess move scoring tests

*Updated: 1/27/2015*

* Added chess move scoring heuristic
* Added chess move scoring tests (partial)

*Updated: 1/26/2015*

* Added chess game class (partial)
* Added chess game class tests (partial)
* Added static board score move set routine (partial)

*Entries below this point can be found in the file history*

Usage
=====

###Build

__Prereq__: Building this project requires the GNU and/or Clang c++ compilers (g++/clang++).

To build the entire project, simply run the command below in the projects root directory.

```
make
```

LIBPTCE is a terminal based server application, which can be invoked using the interface below:

###PTCE

```
ptce [-h | -v | -q | -b | -n] [-p PORT] [-c MAX CONN]
```

* _-c | --conn_		--- Maximum client connections (default: 5, max: 255)
* _-h | --help_		--- Display help
* _-p | --port_		--- Server port (default: 2000, max: 65536)
* _-q | --quiet_ 	--- Quiet mode
* _-b | --board_ 	--- Display game boards
* _-n | --net_ 		--- Display game network traffic
* _-v | --version_ 	--- Display version

License
======

Copyright(C) 2015 David Jolly <majestic53@gmail.com>

libptce is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

libptce is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
