#include "VideoRecorder.hpp"

VideoRecorder::VideoRecorder(unsigned short identifier) : id(identifier) {

    // create string identifier
    std::ostringstream ss;
    ss << std::setw(5) << std::setfill('0') << id;
    strId = ss.str();

    std::cout << "VideoRecorder" << strId << ": Constructor called." << std::endl;
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
        std::cout << "VideoRecorder" << strId << ": one of more elements could not be created" << std::endl;
  
    // Build the pipeline.
    gst_bin_add_many(GST_BIN(pipeline), source, scale, convert, encode, parse, mux, sink, NULL);
    if (!gst_element_link_many(source, scale, convert, encode, parse, mux, sink, NULL)) {
        std::cout << "VideoRecorder" << strId << ": Elements could not be linked." << std::endl;
        gst_object_unref(pipeline);
    }

    // Set the location to save video file
    filename = "video" + strId + ".mp4";
    g_object_set(sink, "location", filename.c_str(), NULL);
};

VideoRecorder::~VideoRecorder(){
    std::cout << "VideoRecorder" << strId << ": destructor called." << std::endl;
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (pipeline);
    if(saveFile)
        std::cout << "VideoRecorder" << strId << ": Saving file." << std::endl;
    else
        std::cout << "VideoRecorder" << strId << ": Deleting file." << std::endl;
}

void VideoRecorder::startRecording(){
    gboolean ret;
    // Start playing
    ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        std::cout << "VideoRecorder" << strId << ": unable to set the pipeline to playing state" << std::endl;
        gst_object_unref(pipeline);
    }
    else
        std::cout << "VideoRecorder" << strId << ": Video recording in progress." << std::endl;

};

void VideoRecorder::stopRecording(){
    gboolean res = gst_element_send_event(pipeline, gst_event_new_eos());
    if(!res) 
        std::cout << "VideoRecorder" << strId << ": end-of-stream signal cannot be sent!" << std::endl;
    // wait for eos signal to traverse pipeline
    GstBus *bus = gst_element_get_bus(pipeline);
    GstMessage *msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, static_cast<GstMessageType>(GST_MESSAGE_EOS | GST_MESSAGE_ERROR));
    if( GST_MESSAGE_TYPE (msg) == GST_MESSAGE_EOS)
	    std::cout << "VideoRecorder" << strId << ": Video recording complete." << std::endl;
    else
    	std::cout << "VideoRecorder" << strId << ": Unexpected message received." << std::endl;
};

void VideoRecorder::setSaveFile(){
    saveFile = true;
}



