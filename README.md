# BMP-Photo-Manipulation

Adjusting the brightness and contrast of a BMP
Image automatically.

The main goal of this project is to develop a program that allows
us to automatically adjust the brightness and contrast of a BMP
image. There are several steps so that required results can be
obtained. In order to change the brightness of the image, we
need to subtract the minimum values of all RGB pixels. Moving
to maximum contrast, in order to obtain that, we need to multiply
all the pixels by maximizing factor. (*Maximizing factors can be
obtained by dividing max. brightness by max. RGB values.)


Valid Usage <br/>
complie :<br/>
gcc autoadjust.c -o autoadjust<br/>

run:<br/>
./autoadjust source.bmp -o destination.bmp<br/>

If you need help, use "-h" flag. <br/>
./autoadjust -h
