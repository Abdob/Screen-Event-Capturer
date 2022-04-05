gst-launch-1.0 -vvv ximagesrc num-buffers=100 ! videoconvert ! x264enc ! h264parse ! mp4mux  ! filesink location=/home/Videos/video.mp4
