package com.synthesizer.Factories;

import com.synthesizer.ViewModel.*;

public class ViewModelFactory {
    private SineWaveViewModel sineWaveViewModel;
    private SquareWaveViewModel squareWaveViewModel;
    private MixerViewModel mixerViewModel;
    private VolumeViewModel volumeViewModel;
    private ContainerViewModel containerViewModel;
    private SpeakerViewModel speakerViewModel;

    public ViewModelFactory(ModelFactory modelFactory){
        containerViewModel = new ContainerViewModel();
        sineWaveViewModel = new SineWaveViewModel(modelFactory.getSineWave());
        squareWaveViewModel = new SquareWaveViewModel(modelFactory.getSquareWave());
        mixerViewModel = new MixerViewModel(modelFactory.getMixer());
        volumeViewModel = new VolumeViewModel(modelFactory.getVolumeFilter());
        speakerViewModel = new SpeakerViewModel();
    }

    public ContainerViewModel getContainerViewModel(){return containerViewModel;}
    public SineWaveViewModel getSineWaveViewModel(){return sineWaveViewModel;}
    public SquareWaveViewModel getSquareWaveViewModel(){
        return squareWaveViewModel;
    }
    public MixerViewModel getMixerViewModel(){
        return mixerViewModel;
    }
    public VolumeViewModel getVolumeViewModel(){
        return volumeViewModel;
    }
    public SpeakerViewModel getSpeakerViewModel(){return speakerViewModel;}
}
