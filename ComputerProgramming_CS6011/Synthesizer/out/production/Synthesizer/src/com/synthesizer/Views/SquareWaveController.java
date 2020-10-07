package com.synthesizer.Views;

import com.synthesizer.Helpers.HandleDragEvent;
import com.synthesizer.Helpers.HandleSlideDetected;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.VBox;

public class SquareWaveController extends BaseController {

    @FXML
    VBox squarePaneFrequencyControl;

    @FXML
    Label label;

    @FXML
    Slider slider;

    @FXML
    Label value;

    public int frequency;

    public SquareWaveController(){
        super("SquareWaveWidget");
    }

    public void onSlideDetected(MouseEvent mouseEvent) {
        HandleSlideDetected handleSlideDetected = new HandleSlideDetected();
        handleSlideDetected.handleSlideDetected(slider, value);
    }

    public void drag(MouseEvent mouseEvent){
        HandleDragEvent handleDragEvent = new HandleDragEvent();
        handleDragEvent.handleMousePressed(mouseEvent);
        handleDragEvent.handleMouseDrag(mouseEvent, squarePaneFrequencyControl);
    }

    public void consume(MouseEvent mouseEvent) {
        HandleDragEvent.draggable = true;
        mouseEvent.consume();
        System.out.println("Consume Here");
    }

}
