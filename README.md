# LibPGEN

master [![Build Status](https://travis-ci.org/slankdev/libpgen.svg?branch=master)](https://travis-ci.org/slankdev/libpgen)

develop [![Build Status](https://travis-ci.org/slankdev/libpgen.svg?branch=develop)](https://travis-ci.org/slankdev/libpgen)


LibPGEN is Packet GENerator library.  
Please see the libpgen official WEB-site http://libpgen.org

## Description

Latest version is [libpgen version 1.1](https://github.com/slankdev/libpgen/tree/v1.1). Now, I am developing new version, 2.0. It has no version1.1's compatible.
If you want to need more information about version2.0, please access to libpgen's official page

 - [about version 2.0 -- libgpgen.org](http://libpgen.org/2016/02/14/about-version2-0)


LibPGEN is a library that runs on Linux and BSD for C/C++.  
This library can analize network pakcets easily.




## Environment
Developers have been tested in Ubuntu-Gnome14.04LTS, ArchLinux, Linux Mint17.1 and OSX10.10.5  
We don't have been tested other Linux and BSD but maybe available.

 

## Future
* Support more protocols  
* Become easy to extension 


## Developer
Handlename  : Slank  
Fullname    : Hiroki Shirokura  
Country     : Japan  
E-mail      : slank.dev@gmail.com  
Web-Site    : http://slankdev.net  
Twitter     : @slankdev  


## Support Protocol
Ethernet, ARP, IP, ICMP, TCP, UDP.  
We stoped supporting DNS, DHCP and AR_Drone, for refactoring. 


## Sample Code

Please see.
 - http://libpgen.org/documentation/samples/
 - lib/module/README.md
 - lib/core/README.md




## Install

	$ cd libpgen
	$ make
	$ sudo make install

## Uninstall 

	$ cd libpgen
	$ sudo make uninstall


## LICENCE

GNU GPL v2.0 https://www.gnu.org/licenses/gpl-2.0.html 
