# Imagelib

Short and simple static/shared library to create image

## Ready to start

```console
$ make dyn
$ make static
$ ./main
```

The main.c program is just an exemple of use. It can create 60 images in either BMP or PPM format


## Usefull command :

> To generate mp4 file :

```console
$ ffmpeg -i test_%02d.ppm -r 60 test.mp4
```

> To play the video in while :

```console
$ mpv test.mp4 --loop-file=yes
```
