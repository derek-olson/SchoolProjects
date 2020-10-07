package com.synthesizer;


import com.synthesizer.Models.*;
import com.synthesizer.Models.AudioClip;

import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.LineUnavailableException;

public class Main {

    public static void main(String[] args) throws LineUnavailableException {


        //get properties from the system about samples rates, etc
        Clip c = AudioSystem.getClip(); //terrible name

        //This is the format that we're following, 44.1KHz mono audio, 16 bits per sample
        AudioFormat format16 = new AudioFormat(44100, 16, 1, true, false);

        AudioComponent sin1 = new SineWave(440, 10000);
        AudioComponent sin2 = new SineWave(40, 15000);

        AudioComponent square1 = new SquareWave(440, 10000);
        AudioComponent square2 = new SquareWave(40, 15000);

        AudioComponent mixer = new Mixer();

        mixer.connectInput(0, square1);
        mixer.connectInput(0, square2);

        AudioComponent vol = new VolumeFilter(3);

        vol.connectInput(0, mixer);

        AudioClip clip = vol.getClip();

        c.open(format16, clip.getData(), 0, clip.getData().length); //reads data from my byte array to play it

        System.out.println("about to play");
        c.start(); //plays it
        c.loop(2); //plays it 2 more times if desired, so 3 seconds total

        //makes sure the program doesn't quit before the sound plays
        while(c.getFramePosition() < AudioClip.TOTAL_SAMPLES || c.isActive() || c.isRunning()){}

        System.out.println("done");
        c.close();

    }
}
