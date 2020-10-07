package com.synthesizer.ViewModel;

import com.synthesizer.Models.AudioComponent;
import com.synthesizer.Models.Mixer;
import com.synthesizer.Models.SineWave;

public class MixerViewModel {

    private SineWaveViewModel sineWaveViewModel;

    private AudioComponent mixer = new Mixer();
    private SineWave sineWave = new SineWave();

    public MixerViewModel(Mixer mixer){}

    public void connectModelToMixer(AudioComponent model){
        mixer.connectInput(0, model);
    }


}
