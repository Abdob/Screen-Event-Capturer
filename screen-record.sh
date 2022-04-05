gst-launch-1.0 -vvv ximagesrc num-buffers=100 ! videoscale ! video/x-raw,width=640,height=360 ! videoconvert ! x264enc ! h264parse ! mp4mux  ! filesink location=/home/Videos/video.mp4

