# STEGANOGRAPHY C++

Appliaction to encode and decode data in images.

## Building
```
g++-7 --std=c++17 main.cpp -o app.e -Wall -Wextra -Wpedantic -O3 -Wno-address -lsfml-graphics -lsfml-window -lsfml-system
```

## Using
To encode:
```
./app.e --encode image.png data.txt output.png
```

To decode:
```
./app.e --decode image.png output.txt
```

## Result
Image without encoded data on right and with encoded data on left.<br/>
<img src="tests/image2.png" alt="Without encoded data" /><img src="tests/output2.png" alt="With encoded data" />
