package com.synthesizer.Models;

public class SineWave implements AudioComponent {
    public double frequency;
    public int amplitude;
    //Make frequency and amplitudes DoubleProperties with bindings to
    //the sinewave and volume views
    public SineWave(){
        frequency = 440;
        amplitude = 10000;
    }
    public SineWave(int pitch, int amp){
        //SineWaveViewModel sineWaveViewModel = new SineWaveViewModel();
        frequency = pitch;
        amplitude = amp;
    };

    @Override
    public AudioClip getClip() {
        AudioClip ac = new AudioClip();
        for(int i = 0; i  < ac.sampleRate; i++) {
            ac.setSample(i, (short) (amplitude * Math.sin(2 * Math.PI * frequency * i / ac.sampleRate)));
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

    }
}
