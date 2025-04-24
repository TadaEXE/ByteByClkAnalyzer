# Byte By Clock Analyzer (aka. BBC-Anal)

Byte by Clock is a low-level protocol analyzer for Saleae Logic 2 that evaluates a data channel bytewise based on a dedicated clock channel. Each bit is sampled precisely on the rising or falling edge of the clock, ensuring correct alignment even with irregular or non-uniform clock pulse widths. Designed for analyzing synchronous digital signals where data is defined relative to clock edges.

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
