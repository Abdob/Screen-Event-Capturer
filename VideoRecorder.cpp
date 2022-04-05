#include <iostream>
#include <gst/gst.h>

/* Structure to contain all our information, so we can pass it to callbacks */
struct CustomData {
    GstElement *pipeline;
    GstElement *source;
    GstElement *scale;
    GstElement *convert;
    GstElement *encode;
    GstElement *parse;
    GstElement *mux;
    GstElement *sink;
};


int main(int arg, char *argv[]) {
    std::cout << "Gstreamer initiated" << std::endl;
    CustomData data{};
    GstBus *bus;
    GstMessage *msg;
    GstStateChangeReturn ret;
    gboolean terminate = false;
  
    /* Initialize GStreamer */
    gst_init(&arg, &argv);

    /* Create the elements */
    data.source = gst_element_factory_make("ximagesrc", "source");
    data.scale = gst_element_factory_make("videoscale", "scale");
    data.convert = gst_element_factory_make("videoconvert", "convert");
    data.encode = gst_element_factory_make("x264enc", "encode");
    data.parse = gst_element_factory_make("h264parse", "parse");
    data.mux = gst_element_factory_make("mp4mux", "mux");
    data.sink = gst_element_factory_make("filesink", "sink");


// gst-launch-1.0 ximagesrc num-buffers=100 ! videoscale ! video/x-raw,width=960,height=540 ! videoconvert ! x264enc ! h264parse ! mp4mux  ! filesink location=video.mp4

    /* Create the empty pipeline */
    data.pipeline = gst_pipeline_new("gstreamer-pipeline");

    if (!data.pipeline || !data.source || !data.scale || !data.convert || !data.encode || !data.parse || !data.mux || !data.sink) {
        g_printerr("Not elements could be created\n");
    }

    /* Build the pipeline. */
    gst_bin_add_many(GST_BIN(data.pipeline), data.source, data.scale, data.convert, data.encode, data.parse, data.mux, data.sink, NULL);
    if (!gst_element_link_many(data.source, data.scale, data.convert, data.encode, data.parse, data.mux, data.sink, NULL)) {
        g_printerr("Elements could not be linked");
        gst_object_unref(data.pipeline);
        return -1;
    }

    /* Set the number of buffers to 100 */
    g_object_set(data.source, "num-buffers", 100, NULL);

    /* Set the location to save video file */
    g_object_set(data.sink, "location", "video.mp4", NULL);

    /* Start playing */
    ret = gst_element_set_state(data.pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr("unable to set the pipeline to playing state");
        gst_object_unref(data.pipeline);
        return -1;
    }

    /* Listen to the bus */
    bus = gst_element_get_bus(data.pipeline);
    do {
        msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
                                         static_cast<GstMessageType>(GST_MESSAGE_STATE_CHANGED | GST_MESSAGE_ERROR |
                                                                     GST_MESSAGE_EOS));

        /* Parse message */
        if (msg != nullptr) {
            GError *err;
            gchar *debug_info;

            switch (GST_MESSAGE_TYPE (msg)) {
                case GST_MESSAGE_ERROR:
                    gst_message_parse_error(msg, &err, &debug_info);
                    g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
                    g_printerr("Debugging information: %s\n", debug_info ? debug_info : "none");
                    g_clear_error(&err);
                    g_free(debug_info);
                    terminate = TRUE;
                    break;
                case GST_MESSAGE_EOS:
                    g_print("End-Of-Stream reached.\n");
                    terminate = TRUE;
                    break;
                case GST_MESSAGE_STATE_CHANGED:
                    /* We are only interested in state-changed messages from the pipeline */
                    if (GST_MESSAGE_SRC (msg) == GST_OBJECT (data.pipeline)) {
                        GstState old_state, new_state, pending_state;
                        gst_message_parse_state_changed(msg, &old_state, &new_state, &pending_state);
                        g_print("Pipeline state changed from %s to %s:\n",
                                gst_element_state_get_name(old_state), gst_element_state_get_name(new_state));

                    }
                    break;
                default:
                    /* We should not reach here */
                    g_printerr("Unexpected message received.\n");
                    break;
            }
            gst_message_unref(msg);
        }
    } while (!terminate);
    GST_DEBUG_BIN_TO_DOT_FILE_WITH_TS(GST_BIN(data.pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "pipeline");

    /* Free resources */
    if (msg != NULL)
        gst_message_unref (msg);
    gst_object_unref (bus);
    gst_element_set_state (data.pipeline, GST_STATE_NULL);

    gst_object_unref (data.pipeline);
    return 0;
}

