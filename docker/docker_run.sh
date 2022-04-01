#!/bin/bash
xhost +
docker run -it --rm --entrypoint="/bin/sh" \
	-e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix \
	gst-screen-record

