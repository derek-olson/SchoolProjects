package com.synthesizer.Tests;

import com.synthesizer.Models.AudioClip;

import static org.junit.jupiter.api.Assertions.*;

class AudioClipTest {

    @org.junit.jupiter.api.Test
    void getSample() {
        AudioClip ac = new AudioClip(0);
        ac.setSample(0, (short)513);
        assertEquals(ac.getSample(0), 513);
    }

    @org.junit.jupiter.api.Test
    void setSample() {
        AudioClip ac = new AudioClip(0);
        ac.setSample(0,  (short)1);
        assertEquals(ac.bytes[0] == 1, 1);
    }

    @org.junit.jupiter.api.Test
    void getData() {
    }
}