This wraps VRPN functionality in a C module. Originally developed by Alex Hill for the [UART](https://research.cc.gatech.edu/uart/content/vrpnwrapper)-project.

## Unity3D-plugin

Unity3D [native plugins](http://docs.unity3d.com/Documentation/Manual/Plugins.html) have to provide a C-interface and a native *.dll* or *.bundle*. At the moment Unity plugins have to be compiled for 32-bit.

### Mac OS

- Compile libusb:

        wget http://sourceforge.net/projects/libusb/files/libusb-1.0/libusb-1.0.16-rc10/libusb-1.0.16-rc10.tar.bz2
        tar -xf libusb-1.0.16-rc10.tar.bz2
        cd libusb-1.0.16-rc10
        ./configure --build=i386-apple-darwin12.3.0 "CFLAGS=-m32" "CXXFLAGS=-m32" "LDFLAGS=-m32" --prefix=[libusb-installation-dir]

- Compile  VRPN:

        cd vrpn
        git submodule init c_module
        git submodule update
        mkdir build
        cd build
        cmake .. -DVRPN_USE_C_MODULE=ON -DCMAKE_OSX_ARCHITECTURES=i386 -DLIBUSB1_ROOT_DIR=[libusb-installation-dir]
