gst-launch-1.0 ximagesrc num-buffers=100 ! videoscale ! video/x-raw,width=960,height=540 ! videoconvert ! x264enc ! h264parse ! mp4mux  ! filesink location=video.mp4

