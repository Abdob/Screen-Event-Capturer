#!/bin/bash
xhost +
docker run -it --rm --entrypoint="/bin/sh" \
	-e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix \
	-v /home/$USER/Videos:/home/Videos \
	-v /home/$USER/gstreamer_screen_record:/home/gstreamer_screen_record \
	gst-screen-record

