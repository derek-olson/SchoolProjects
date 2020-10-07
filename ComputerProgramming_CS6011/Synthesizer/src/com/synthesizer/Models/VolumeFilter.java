package com.synthesizer.Models;

public class VolumeFilter implements AudioComponent {
    public double scale;
    public AudioComponent input;

    public VolumeFilter(){
        scale = 1;
    }
    public VolumeFilter(double volume){
        scale = volume;
    };

    @Override
    public AudioClip getClip() {
        AudioClip ac = input.getClip();
        for(int i = 0; i  < ac.sampleRate; i++) {
            short sample = ac.getSample(i);
            ac.setSample(i,(short)(sample*scale));
        }
        return ac;
    }

    @Override
    public int getNuminputs() {
        return 0;
    }

    @Override
    public String getInputName(int index) {
        return null;
    }

    @Override
    public void connectInput(int index, AudioComponent input) {
        this.input = input;
    }
}
