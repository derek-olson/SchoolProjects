package com.synthesizer.Helpers;

import com.synthesizer.Models.SineWave;
import com.synthesizer.Views.SineWaveController;
import javafx.beans.value.ChangeListener;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;

public class HandleSlideDetected {

    public HandleSlideDetected(){}

    public void handleSlideDetected(Slider slider, Label value){
        slider.setOnMouseReleased(event -> {
            System.out.println(slider.getValue());
        });

        slider.valueProperty().addListener((ChangeListener) (observableValue, o, t1) -> value.textProperty().setValue(
                String.valueOf((int) slider.getValue())));
    }
}
