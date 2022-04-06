#include "VideoRecorder.hpp"

VideoRecorder::VideoRecorder(){
    std::cout << "VideoRecorder: Constructor called." << std::endl;
    // Create the elements
    source = gst_element_factory_make("ximagesrc", "source");
    scale = gst_element_factory_make("videoscale", "scale");    
    convert = gst_element_factory_make("videoconvert", "convert");
    encode = gst_element_factory_make("x264enc", "encode");
    parse = gst_element_factory_make("h264parse", "parse");
    mux = gst_element_factory_make("mp4mux", "mux");
    sink = gst_element_factory_make("filesink", "sink");

    // Create the empty pipeline 
    pipeline = gst_pipeline_new("gstreamer-pipeline");

    if (!pipeline || !source || !scale || !convert || !encode || !parse || !mux || !sink) 
        std::cout << "VideoRecorder: one of more elements could not be created" << std::endl;
  
    // Build the pipeline.
    gst_bin_add_many(GST_BIN(pipeline), source, scale, convert, encode, parse, mux, sink, NULL);
    if (!gst_element_link_many(source, scale, convert, encode, parse, mux, sink, NULL)) {
	std::cout << "VideoRecorder: Elements could not be linked." << std::endl;
	gst_object_unref(pipeline);
    }

    // Set the location to save video file
    g_object_set(sink, "location", "video.mp4", NULL);
};

VideoRecorder::~VideoRecorder(){
    std::cout << "VideoRecorder: destructor called." << std::endl;
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (pipeline);
}

void VideoRecorder::startRecording(){
    gboolean ret;
    // Start playing
    ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        std::cout << "VideoRecorder: unable to set the pipeline to playing state" << std::endl;
        gst_object_unref(pipeline);
    }
    else
        std::cout << "VideoRecorder: Video recording in progress." << std::endl;
};

void VideoRecorder::stopRecording(){
    gboolean res = gst_element_send_event(pipeline, gst_event_new_eos());
    if(!res) 
        std::cout << "VideoRecorder: end-of-stream signal cannot be sent!" << std::endl;
    // wait for eos signal to traverse pipeline
    GstBus *bus = gst_element_get_bus(pipeline);
    GstMessage *msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, static_cast<GstMessageType>(GST_MESSAGE_EOS | GST_MESSAGE_ERROR));
    if( GST_MESSAGE_TYPE (msg) == GST_MESSAGE_EOS)
	std::cout << "VideoRecorder: Video recording complete." << std::endl;
    else
    	std::cout << "VideoRecorder: Unexpected message received." << std::endl;
};




