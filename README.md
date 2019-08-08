# AngelsenCppWeb - Demo
## About
This project is a demonstration of a method to use C++ as logic for websites. My own personal website is used as the example.
The method simply uses the following:
* An HTTP/HTTPS server
* An HTML Template Library
* Simple classes for logic

The page is live here: https://angelsensoftware.com

## Libraries
The demonstration uses copies of the following libraries (to enable plug-and-play):
* https://gitlab.com/eidheim/Simple-Web-Server
* https://github.com/hughperkins/Jinja2CppLight

And a copy of standalone boost asio.

The project is using HTTPS, so the OpenSSL libraries are required.

## Install and test

1. git clone https://github.com/stianang/angelsenCppWeb.git
2. cd angelsenCppWeb
3. mkdir build
4. cd build
5. cmake ..
6. make
7. ./Angelsen/Angelsen -config ../Angelsen/config.json

