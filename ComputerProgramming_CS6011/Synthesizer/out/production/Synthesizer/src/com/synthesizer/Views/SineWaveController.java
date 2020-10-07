package com.synthesizer.Views;

import com.synthesizer.Helpers.*;
import com.synthesizer.ViewModel.MixerViewModel;
import com.synthesizer.ViewModel.SineWaveViewModel;
import javafx.beans.property.BooleanProperty;
import javafx.beans.property.DoubleProperty;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Bounds;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.input.InputEvent;
import javafx.scene.input.MouseDragEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;

import java.io.IOException;

public class SineWaveController{
    DoubleProperty frequency;
    DoubleProperty centerX;
    DoubleProperty centerY;

    public SineWaveController() {
        //super("SineWaveWidget");
        //this.slider.valueProperty().bindBidirectional(sineWaveViewModel.frequency);
    }

    @FXML
    VBox sinePane;

    @FXML
    Label label;

    @FXML
    Slider slider;

    @FXML
    Label value;

    @FXML
    Circle sineWaveOutputJack;


    Pane pane = new Pane();

    @FXML
    public void onSlideDetected(MouseEvent mouseEvent) {
        HandleSlideDetected handleSlideDetected = new HandleSlideDetected();
        handleSlideDetected.handleSlideDetected(slider, value);
    }

    @FXML
    public void connect(MouseEvent mouseEvent){

    }

    @FXML
    public void drag(MouseEvent mouseEvent) {
        HandleDragEvent handleDragEvent = new HandleDragEvent();
        handleDragEvent.handleMousePressed(mouseEvent);
        handleDragEvent.handleMouseDrag(mouseEvent, sinePane);
    }

    private EventHandler<MouseEvent> filter = mouseEvent -> {
        System.out.println("Filtering out event " + mouseEvent.getEventType());
        mouseEvent.consume();
    };

    public void consume(MouseEvent mouseEvent) {
        HandleDragEvent.draggable = true;
        mouseEvent.consume();
        System.out.println("Consume Here");
    }
}
