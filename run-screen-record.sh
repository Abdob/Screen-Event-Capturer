gst-launch-1.0 ximagesrc num-buffers=100 ! videoconvert ! x264enc ! qtmux ! h264parse ! filesink location=/home/Videos/video.mp4
