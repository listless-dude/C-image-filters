# Image Filters in C
Trying to create some popular used filters in photos such as Grayscale, Sepia, Mirror, Blur, etc. in C language.

## Idea behind:

The simplest way of representing an image would be a grid of pixels (i.e. dots), each of which can be of different colour. For black-and-white images, we just need 1 bit per pixel, as 0 could represent black while 1 can represent white.

Then the image can be called a *bitmap* (a map of bits), 2d-array of pixels. For coloured images, we need more bits per pixel. For example, a 24-bit BMP uses 8-bits for RED, 8-bits for BLUE, and 8-bits for GREEN. We know the max values of R, G and B is 255 (or 0xff in hex).

A BMP files also contains some headers which stores metadata of the file ex. height, width, etc. In MS Bitmap 4.0 format, the first header is called **BITMAPFILEHEADER** is 14 bytes long. The second of these is called **BITMAPINFOHEADER** which is 40 bytes long. Immediately following these headers are the actually bitmap, i.e. array of bytes, triples of R,G,& B which represents pixel's colour. 


## Grayscale

The idea is that get the RGB values of each pixel and convert it to black, or white. However, we can't convert it to pure black or white. For each pixel the grayscale value should be the average of the RGB values of each pixel. And check if the value is not greater than 255.

## Sepia

Here, we set the RGB values of each pixel with the following equations:

```
    sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
    sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
    sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
```

And, since the values will be a floating point and can be greater than 255, we make sure it is capped to 255 if the value is greater than 255.

## Reflection (horizontally)

Here, we traverse the bitmap or 2D array to complete height, and half of the width and just swap the values. For example we have a 2d array: 
```
1 2 3 4 5
6 7 8 9 10
```

We want to reflect it, we want to set j = 0 to j = 4, and j = 4 to j = 0, i.e. just swap. We set j = width - j - 1


## Blur

We have implemented **BoxBlur** which just takes every pixel and sets value to average of its neighbouring pixels.
First, we created an temporary bitmap, a temporary counter to count the number of neighbouring pixels. W traverse from rows i - 1 to i + 1, i.e. if i = 0, runs from -1 to 1, if i = 2, runs from 1 to 3, and from columns j - 1 to j + 1, i.e. if j = 3, j runs from 2 to 4. And then check if the values are greater than or equals zero (since array index can't be negative) and less than height or width, incrementing count by one. Then set each pixel values to the average of the RGB values.

## Sobel Operator (Edge detection)

It is an edge detection algorithm used in image processing and computer vision. It is a discrete differentiation operator, computing an approximation of the gradient of the image intensity function. At each point in the image, the result of the Sobel–Feldman operator is either the corresponding gradient vector or the norm of this vector.

The Sobel operator computes the new value of each pixel by taking a weighted sum of the values for the surrounding pixels. And since edges between objects could take place in both a vertical and a horizontal direction, actually compute two weighted sums: one for detecting edges in the x direction, and one for detecting edges in the y direction. In particular, you’ll use the following two “kernels”:

Ref: https://en.wikipedia.org/wiki/Sobel_operator

![sobeloperator](https://cs50.harvard.edu/x/2021/psets/4/filter/more/sobel.png)

where we use 2d-convolution operation on the image each for Gx and Gy.

![sobeloperator](https://wikimedia.org/api/rest_v1/media/math/render/svg/23ae6772c5f58751fc6014b71d6adafb30a31c79)

In the Gx direction, for instance, we’re multiplying the pixels to the right of the target pixel by a positive number, and multiplying the pixels to the left of the target pixel by a negative number. When we take the sum, if the pixels on the right are a similar color to the pixels on the left, the result will be close to 0 (the numbers cancel out). But if the pixels on the right are very different from the pixels on the left, then the resulting value will be very positive or very negative, indicating a change in color that likely is the result of a boundary between objects. And a similar argument holds true for calculating edges in the y direction.


*Check the helpers.c file for the implementation*

`filter.c` contains the required FILE operations required for opening, checking if the file is BMP (every format type has the first few bytes unique, and headers as well), saving and closing.

`bmp.h` contains the custom data types required for Microsoft BMP 4.0 format.

`Makefile` is just the command-line code for compiling the code using `clang` compiler

#### Compiling:

```
make filter
```

#### Usage:

```
./filter -argument images/filename.bmp outfile.bmp
```

Replace -argument with `-g` for grayscale, `-s` for sepia, `-r` for reflection, `-b` for blur.

Examples:

```
./filter -g images/courtyard.bmp grayscale.bmp
```
![courtyard](/images/courtyard.bmp) `Original Image`
![grayscale](/grayscale.bmp) `Filtered with grayscale`

```
./filter -b images/courtyard.bmp grayscale.bmp
```

![courtyard](/images/stadium.bmp) `Original image`
![courtyard](/blur.bmp) `Filtered with blur`
