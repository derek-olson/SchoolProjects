package com.synthesizer.Views;

import com.synthesizer.Helpers.HandleConnectEvent;
import com.synthesizer.Helpers.HandleDragEvent;
import com.synthesizer.Helpers.HandleCableDraw;
import com.synthesizer.Models.SineWave;
import com.synthesizer.ViewModel.SineWaveViewModel;
import javafx.beans.property.DoubleProperty;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.EventHandler;
import javafx.event.EventTarget;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Bounds;
import javafx.scene.Node;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.*;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;

import java.io.IOException;

public class ContainerController {

    public ContainerController(){}
    @FXML
    BorderPane borderPane;

    @FXML
    Pane pane;

    @FXML
    AnchorPane anchorPane;

    @FXML
    VBox SineWave;

    @FXML
    public void addSineWaveController(javafx.event.ActionEvent actionEvent) throws IOException {
        VBox newSineWaveController = FXMLLoader.load(getClass().getResource("SineWave.fxml"));
        pane.getChildren().add(newSineWaveController);
        SineWave sineWave = new SineWave();
        SineWaveViewModel sineWaveViewModel = new SineWaveViewModel(sineWave);
    }
    @FXML
    public void addSquareWaveController(javafx.event.ActionEvent actionEvent) throws IOException {
        VBox newSquareWaveController = FXMLLoader.load(getClass().getResource("SquareWave.fxml"));
        pane.getChildren().add(newSquareWaveController);
    }
    @FXML
    public void addMixerController(javafx.event.ActionEvent actionEvent) throws IOException {
        VBox newMixerController = FXMLLoader.load(getClass().getResource("Mixer.fxml"));
        pane.getChildren().add(newMixerController);
    }
    @FXML
    public void addVolumeController(javafx.event.ActionEvent actionEvent) throws IOException {
        VBox newVolumeController = FXMLLoader.load(getClass().getResource("VolumeFilterController.fxml"));
        pane.getChildren().add(newVolumeController);
    }
    @FXML
    public void addSpeakerController(javafx.event.ActionEvent actionEvent) throws IOException {
        VBox newSpeakerController = FXMLLoader.load(getClass().getResource("Speaker.fxml"));
        pane.getChildren().add(newSpeakerController);
    }

    public void init() throws IOException {}

    @FXML
    public void connectAudioComponents(MouseEvent mouseEvent){
        pane.setOnMouseDragged((EventHandler<MouseEvent>) event -> {
            Line line = new Line();
            Node node = event.getPickResult().getIntersectedNode();
            if (node.getClass().toString().contains("Circle")) {
                Circle circle = (Circle) node;
                HandleCableDraw handleCableDraw = new HandleCableDraw();
                handleCableDraw.getLineBeginCoordinates(pane, circle, event);
                handleCableDraw.drawLine(line, circle, pane);
            }
        });
    }

    public void resumeDrag(MouseEvent mouseEvent) {
        HandleDragEvent.draggable = false;

        Node node = mouseEvent.getPickResult().getIntersectedNode();
        node.setOnMouseReleased((MouseEvent e) -> {
            EventTarget target = e.getTarget();
            if (target.toString().contains("Circle")) {
                Circle circle = (Circle) target;
                HandleConnectEvent handleConnectEvent = new HandleConnectEvent();
                handleConnectEvent.handleConnectEvent(target, circle);
            }
        });
    }

    private EventHandler<MouseEvent> filter = mouseEvent -> {
        System.out.println("Filtering out event " + mouseEvent.getEventType());
        mouseEvent.consume();
    };
}
