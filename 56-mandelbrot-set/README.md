# MANDELBROT SET

## Compile
```
g++-7 --std=c++17 -O3 save_image.cpp utils.cpp main.cpp -lfreeimage -lsfml-graphics -lsfml-window -lsfml-system -lpthread
```

## Using
Change values in config.hpp to manipulate consts.
```
./a.out
```

<img src="images/app.gif" />

## Some Mandelbrot set zooms
<img src="images/mandelbrot.png" height="250" width="250" hscape="0" /><img src="images/mandelbrot3.png" height="250" width="250" hscape="0" /><img src="images/mandelbrot4.png" height="250" width="250" hscape="0" /><img src="images/mandelbrot5.png" height="250" width="250" hscape="0" /><img src="images/mandelbrot6.png" height="250" width="250" hscape="0" /><img src="images/mandelbrot7.png" height="250" width="250" hscape="0" />
