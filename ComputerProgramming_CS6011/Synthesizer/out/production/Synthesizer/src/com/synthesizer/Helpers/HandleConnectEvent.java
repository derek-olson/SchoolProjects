package com.synthesizer.Helpers;

import com.synthesizer.Models.*;
import javafx.event.Event;
import javafx.event.EventTarget;
import javafx.scene.Node;
import javafx.scene.input.MouseEvent;
import javafx.scene.shape.Circle;

public class HandleConnectEvent {

    public HandleConnectEvent() {
    }

    public void handleConnectEvent(EventTarget target, Node inNode) {
        inNode.setOnMouseDragReleased((MouseEvent e) -> {
            if (target.toString().contains("Circle")) {
                String inNodeID = inNode.getId();
                System.out.println(inNode.getClass().toString());
                System.out.println(inNodeID);
                //handle all possible output jacks
                if (inNodeID == "mixerInputJack") {
                    //mixer.connectInput(0, sineWave);
                    //call the draw method?
                } else if (inNodeID == "volumeInputJack") {
                    //volumeFilter.connectInput(0, sineWave);
                    //call the draw method?
                } else if (inNodeID == "speakerInputJack") {
                    //can the audio component bypass the volume filter?
                    //call the draw method?
                } else {
                    // do nothing, print to console, or add a label to the container that will communicate
                }
                if (inNodeID == "mixerInputJack") {
                    //mixer.connectInput(0, squareWave);
                    //call the draw method?
                } else if (inNodeID == "volumeInputJack") {
                    //volumeFilter.connectInput(0, squareWave);
                    //call the draw method?
                } else if (inNodeID == "speakerInputJack") {
                    //can the audio component bypass the volume filter?
                    //call the draw method?
                } else {
                    // do nothing, print to console, or add a label to the container that will communicate
                }
                if (inNodeID == "volumeInputJack") {
                    //volumeFilter.connectInput(0, mixer);
                    //call the draw method?
                } else if (inNodeID == "speakerInputJack") {
                    //can the audio component bypass the volume filter?
                    //call the draw method?
                } else {
                    // do nothing, print to console, or add a label to the container that will communicate
                }
                if (inNodeID == "speakerInputJack") {
                    //can the audio component bypass the volume filter?
                    //call the draw method?
                } else {
                    // do nothing, print to console, or add a label to the container that will communicate
                }

            }
        });
    }
}

