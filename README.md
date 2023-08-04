# BFCD
BFCD (Basic File Comressor and Decompressor)

In future BFCD Project is going to have not only Compression/Decompression algorithms, but many Cryptographic algorithms.

## How to build BFCD

To build the project we need to have some c++ compiler, Conan 2.0+ and cmake 3.15+

---
We need a Conan profile to build our project. Conan profiles allow users to define a configuration set for things like the compiler, build configuration, architecture, shared or static libraries, etc. Conan, by default, will not try to detect a profile automatically, so we need to create one. To let Conan try to guess the profile, based on the current operating system and installed tools, please run:

```
$ conan profile detect --force
```
This will detect the operating system, build architecture and compiler settings based on the environment. It will also set the build configuration as Release by default. The generated profile will be stored in the Conan home folder with name default and will be used by Conan in all commands by default unless another profile is specified via the command line. An example of the output of this command for MacOS would be:

```
$ conan profile detect --force
Found apple-clang 14.0
apple-clang>=13, using the major as version
Detected profile:
[settings]
arch=x86_64
build_type=Release
compiler=apple-clang
compiler.cppstd=gnu17
compiler.libcxx=libc++
compiler.version=14
os=Macos
```

BFCD uses Boost library, to generate files needed with conan we execute this command:

```
$ conan install . --output-folder=build
```

If everything generates correctly we execute commands below:

```
$ cd build
# You might have to find the conan_toolchain.cmake file and change the -DCMAKE_TOOLCHAIN_FILE to correct PATH if the below command doesn't find it with the path given below.
$ cmake .. -DCMAKE_TOOLCHAIN_FILE=$pwd/build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
$ make
```

Now to run the project we just run the executable:

```
./BFCD
```
