package com.synthesizer.Views;

import com.synthesizer.Helpers.HandleDragEvent;
import com.synthesizer.Models.Mixer;
import com.synthesizer.Models.AudioComponent;
import com.synthesizer.ViewModel.MixerViewModel;
import javafx.beans.property.BooleanProperty;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.input.DragEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.VBox;
import javafx.scene.shape.Circle;

public class MixerController extends BaseController {

    @FXML
    VBox mixerControl;

    @FXML
    Label label;

    @FXML
    Circle mixerJackInput;

    @FXML
    Circle mixerJackOutput;


    public MixerController() {
        super("MixerWidget");
    }

    @FXML
    public void drag(MouseEvent mouseEvent) {
        HandleDragEvent handleDragEvent = new HandleDragEvent();
        handleDragEvent.handleMousePressed(mouseEvent);
        handleDragEvent.handleMouseDrag(mouseEvent, mixerControl);
    }

    public void connect() {

    }

    public void consume(MouseEvent mouseEvent) {
        HandleDragEvent.draggable = true;
        mouseEvent.consume();
        System.out.println("Consume Here");
    }

    public void connectInput(DragEvent dragEvent) {
    }
}
