#include "RecordManager.hpp"

int main(int arg, char *argv[]) {

    // Initialize GStreamer
    gst_init(&arg, &argv);

    // Create and run record manager
    RecordManager recordManager;
    recordManager.run();

    return 0;
}
