# gxk
This is GXK - GTK XApp Toolkit - a GTK platform library for developing programs compliant with the XApps specification.

**Please note that this library is heavily WIP at the moment.**

## The Goal
The main aim of GXK is to provide an alternative platform library to *libadwaita*, one that hopes to be useful for developing applications that 'fit in' across various desktop environments using GTK (currently GTK4).

This includes:
  - Fitting in with the user's system theme
  - UI widgets targeted at the desktop rather than mobile
  - Potentially APIs for querying aspects about the DE that might be relevant for blending in

## Building
This project uses CMake as the build system.

### Building the library
The library source lives under `gxk/` and can be built as follows:
```
cd gxk
mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=ON ..
make -j$(nproc)
```

You can install the library by doing `sudo make install` which will usually plop it in `/usr/local` (or whatever the default prefix is for your distro).

### Building the samples
The samples live under the `samples/` directory and each can be built as follows (replace `<subdir>` with the subdirectory of the sample you want):
```
cd samples/<subdir>
mkdir build
cd build
cmake ..
make -j$(nproc)
```

## Contributing
Open an issue or discussion or something on GitHub and I'll take a look.

There is also the XApps channel on Matrix if you would like to chat about XApps with other developers: https://matrix.to/#/#xapp:matrix.org
