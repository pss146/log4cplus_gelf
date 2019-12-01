## Package Status

[![Build Status](https://dev.azure.com/sperepelitsyn/conan-recipes/_apis/build/status/pss146.log4cplus_gelf?branchName=stable%2F0.1)](https://dev.azure.com/sperepelitsyn/conan-recipes/_build/latest?definitionId=7&branchName=stable%2F0.1)

# log4cplus_gelf
## GELF Appender for log4cplus.

* [log4cplus_gelf GitHub](https://github.com/pss146/log4cplus_gelf)

## Introduction
log4cplus_gelf is a [Graylog Extended Log Format (GELF)](http://docs.graylog.org/en/stable/pages/gelf.html) appender for log4cplus C++ logging library.
GELF is used by the open-source log management software [Graylog](https://www.graylog.org/).
It is able to send structured message log message into the system without the need to do expensive parsing.

## Requirements
* CMake >= 3.1
* C++14 compatible compiler
  * GCC >= 5.4.0
  * Clang >= 3.8.0
  * MSVC >= 14.2
* Conan

## Including log4cplus_gelf in your projects
Using Conan:
* Add pss146 remote repository:
  conan remote add <REMOTE> https://api.bintray.com/conan/pss146/public-conan

* Add in your Conan recipe:
def requirements(self):
      self.requires.add("log4cplus_gelf/0.1@pss146/stable")
