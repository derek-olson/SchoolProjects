package com.synthesizer.Views;

import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.VBox;

public class SpeakerController extends BaseController {


    public SpeakerController() {
        super("SpeakerWidget");
    }

    @FXML
    VBox speakerControl;
    @FXML
    Label label;

    public void drag() {
        final double[] sceneX = new double[1];
        final double[] sceneY = new double[1];
        final double[] mouseX = new double[1];
        final double[] mouseY = new double[1];

        EventHandler<MouseEvent> onPressedEvent = new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent mouseEvent) {
                sceneX[0] = mouseEvent.getSceneX();
                sceneY[0] = mouseEvent.getSceneY();
                mouseX[0] = speakerControl.getTranslateX();
                mouseY[0] = speakerControl.getTranslateY();
            }
        };
        EventHandler<MouseEvent> onDragEvent = new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent mouseEvent) {
                double offsetX = mouseEvent.getSceneX() - sceneX[0];
                double offsetY = mouseEvent.getSceneY() - sceneY[0];
                double newTranslateX = mouseX[0] + offsetX;
                double newTranslateY = mouseY[0] + offsetY;

                speakerControl.setTranslateX(newTranslateX);
                speakerControl.setTranslateY(newTranslateY);
            }
        };
        speakerControl.setOnMousePressed(onPressedEvent);
        speakerControl.setOnMouseDragged(onDragEvent);

    }




//    Button playButton = new Button("Play");
//
//    SpeakerWidget() {
//        playButton.setStyle("-fx-border-color: #ff0000; -fx-border-width: 5px;");
//        playButton.setStyle("-fx-background-color: #00ff00");
//        playButton.setStyle("-fx-font-size: 2em; ");
//        playButton.setStyle("-fx-text-fill: #0000ff");
//
//        Tooltip tooltip1 = new Tooltip("Plays the audio sample");
//        playButton.setTooltip(tooltip1);
//    }
//


}
