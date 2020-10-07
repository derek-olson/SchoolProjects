package com.synthesizer.Models;

public class SquareWave implements AudioComponent {
    public float frequency;
    public int amplitude;

    public SquareWave(){
        frequency = 440;
        amplitude = 10000;
    }

    public SquareWave(int pitch, int amp){
        frequency = pitch;
        amplitude = amp;
    };

    @Override
    public AudioClip getClip() {
        AudioClip result = new AudioClip();
        for(int i = 0; i  < result.sampleRate; i++) {
            short sample = result.getSample(i);
            float interem = (frequency * i / result.sampleRate) % 1;
            if (interem > 0.5) {
                sample = (short) amplitude;
            } else {
                sample = (short) (amplitude * -1);
            }
            result.setSample(i, sample);
        }
        return result;
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

    }
}
