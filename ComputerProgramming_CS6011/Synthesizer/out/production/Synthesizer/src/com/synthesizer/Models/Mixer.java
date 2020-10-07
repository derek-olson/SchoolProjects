package com.synthesizer.Models;

import java.util.ArrayList;

public class Mixer implements AudioComponent {
    ArrayList<AudioComponent> audioComponents = new ArrayList<>();

    public Mixer(){};

    @Override
    public AudioClip getClip() {
        AudioClip result = new AudioClip();
        for(AudioComponent ac : audioComponents) {
            AudioClip clip = ac.getClip();
            for (int i = 0; i < 44100; i++) {
                int sum = clip.getSample(i) + result.getSample(i);
                result.setSample(i, (short)sum);
            }
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
        audioComponents.add(input);
    }
}
