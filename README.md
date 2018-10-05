IEX Finance C++ Client
===

[![Build Status](https://travis-ci.org/rodolfobandeira/iex-cpp-client.svg?branch=master)](https://travis-ci.org/rodolfobandeira/iex-cpp-client)

C++ client to consume the [IEX Finance API](https://iextrading.com/developer).

## Usage

```
IEX C++ Client 

./main stock_symbol option
    ex: ./main AMZN -p 

 options:
   -c Company Information
   -l Company Logo
   -p Stock Latest Price
   -s Stock Statistics
   -r Stock Financial Reports
```

## Compilation

On Debian-based distributions you can install the required dependencies using the following command:

`sudo apt-get install libjsoncpp-dev libcurl4-gnutls-dev`

On MacOS using Homebrew:

`brew install jsoncpp; brew install curl`

`g++ -o main main.cpp -lcurl -ljsoncpp -std=c++11`

`./main AMZN -p`

```
Called Endpoint: https://api.iextrading.com/1.0/stock/AMZN/price
Stock Symbol: AMZN
Latest Price: $1952.07
```

### Compiling Using CMake

Compile this project using standing CMake:

```
mkdir build
cd build
cmake ..
make
./main AMZN
```

Or, for an optimized build:

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release
make
./main AMZN
```

## Contributing

See [CONTRIBUTING](CONTRIBUTING.md).

## Copyright and License

Copyright (c) 2018, [Rodolfo Bandeira](https://twitter.com/rodolfobandeira) and [Contributors](CHANGELOG.md).

This project is licensed under the [MIT License](LICENSE.md).

Data provided for free by [IEX](https://iextrading.com/developer), see [terms](https://iextrading.com/api-terms).
