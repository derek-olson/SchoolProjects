package com.synthesizer.ViewModel;

import com.synthesizer.Models.SineWave;
import javafx.beans.property.DoubleProperty;

public class SineWaveViewModel {
    //bound property
    public DoubleProperty frequency;

    //public double pitch = frequency.getValue();

    //create a reference to the model
    public SineWave sineWave = new SineWave(440, 10000);

    //constructor
    public SineWaveViewModel(SineWave sineWave){
        this.sineWave = sineWave;

    }

    public void getPitch(){
         sineWave.frequency = frequency.getValue();
    }




}
