# UAC Bypass via SPPLUAObject Class

This sample will use **SSPLUAObject** to set registry keys, and trigger UAC bypass.

To build and test code you will need **Visual Studio Build tools** 2013, 2015 or 2017, either standalone or one integrated with Visual Studio, and **cmake**:

* [Visual C++ 2015 Build tools](http://landinghub.visualstudio.com/visual-cpp-build-tools)
* [Build Tools for Visual Studio 2017](https://www.visualstudio.com/downloads/#build-tools-for-visual-studio-2017)
* [cmake](https://cmake.org/)

**SSPLUA Object** exposes interface which allows us to set any registry key : **SLLUARegKeySetValue**.

Code sets [Silent Process Exit Monitor](https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/registry-entries-for-silent-process-exit) registry keys and launches auto elevated process. On exit our code will be executed with **High integrity**.

**NOTE**: There are no advanced techniques inside. Only pure demonstration of this interface.
