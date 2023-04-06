//
// Created by liwbh on 05/04/23.
//

#ifndef PROYECTO_01_SO_SONIDO_H
#define PROYECTO_01_SO_SONIDO_H

#include <stdio.h>
#include <gst/gst.h>

/*

sudo apt-get update
sudo apt-get install libgstreamer1.0-dev
sudo apt-get install gstreamer1.0-plugins-bad

*/

void reproducirSonido(char* ruta){

    GstElement *pipeline;
    GstBus *bus;
    GstMessage *msg;

    /* Initialize GStreamer */
    gst_init (NULL, NULL);

    /* Create the elements */
    //pipeline = gst_parse_launch ("playbin uri=file:////home/liwbh/CLionProjects/Proyecto-01-SO/Sonidos/victoria.wav", NULL);
    pipeline = gst_parse_launch (ruta, NULL);

    /* Start playing */
    gst_element_set_state (pipeline, GST_STATE_PLAYING);

    /* Wait until error or EOS */
    bus = gst_element_get_bus (pipeline);
    msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    /* Free resources */
    if (msg != NULL)
        gst_message_unref (msg);
    gst_object_unref (bus);
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (pipeline);
}



#endif //PROYECTO_01_SO_SONIDO_H
