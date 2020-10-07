package com.synthesizer.Factories;

import com.synthesizer.Models.*;

public class ModelFactory {
    private AudioClip audioClip;
    private SineWave sineWave;
    private SquareWave squareWave;
    private Mixer mixer;
    private VolumeFilter volumeFilter;
    private Speaker speaker;

    public ModelFactory(){
        audioClip = new AudioClip();
        sineWave = new SineWave();
        squareWave = new SquareWave();
        mixer = new Mixer();
        volumeFilter = new VolumeFilter();
        speaker = new Speaker();
    }

    public AudioClip getAudioClip() {
        if(audioClip == null){
            new AudioClip();
        }
        return audioClip;
    }

    public SineWave getSineWave() {
        if(sineWave == null){
            new SineWave();
        }
        return sineWave;
    }
    public SquareWave getSquareWave() {
        if(squareWave == null){
            new SquareWave();
        }
        return squareWave;
    }
    public Mixer getMixer() {
        if(mixer == null){
            new Mixer();
        }
        return mixer;
    }
    public VolumeFilter getVolumeFilter() {
        if(volumeFilter == null){
            new VolumeFilter();
        }
        return volumeFilter;
    }

}
