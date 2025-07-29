#!/bin/sh
docker run --platform linux/amd64 -it --rm -v $(pwd):/workspace ubuntu:latest
