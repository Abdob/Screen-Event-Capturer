gst-launch-1.0 ximagesrc num-buffers=100 ! videoconvert ! x264enc ! h264parse ! qtmux ! filesink location=video.mp4
