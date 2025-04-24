# Tadas BBC-Analyzer (Byte By Clock)

This is a simple low level analyzer for Saleae Logic 2.
It can take any clock signal (even maleformed or modulated ones) and map your corresponding data signal bytewise (it's actually bitwise but I already chose the name).

## Building

### Windows

```bat
mkdir build
cd build
cmake .. -A x64
cmake --build .
:: built analyzer will be located at SampleAnalyzer\build\Analyzers\Debug\SimpleSerialAnalyzer.dll
:: use the release build when sharing your analyzer! debug builds only work on your machine.
cmake --build . --config Release
:: release built analyzer will be located at SampleAnalyzer\build\Analyzers\Release\SimpleSerialAnalyzer.dll
```

### MacOS

```bash
mkdir build
cd build
cmake ..
cmake --build .
# built analyzer will be located at SampleAnalyzer/build/Analyzers/libSimpleSerialAnalyzer.so
```

### Linux

```bash
mkdir build
cd build
cmake ..
cmake --build .
# built analyzer will be located at SampleAnalyzer/build/Analyzers/libSimpleSerialAnalyzer.so
```

## Using

To use the analyzer:
- Build it
- Open Logic 2
- Go to `Edit`->`Settings`->`Custom Low Level Analyzers`->`Browse for the 'Analyzers' dir in the build folder`
