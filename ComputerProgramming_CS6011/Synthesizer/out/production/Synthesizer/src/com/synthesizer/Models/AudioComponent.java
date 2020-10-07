package com.synthesizer.Models;

public interface AudioComponent {
    AudioClip getClip();
    int getNuminputs();
    String getInputName(int index);
    void connectInput(int index, AudioComponent input);




}
