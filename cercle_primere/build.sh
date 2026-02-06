#!/bin/bash

set -xe

cc main.c graphique.c Imagefile.c -o main -Wextra

./main sansglib
