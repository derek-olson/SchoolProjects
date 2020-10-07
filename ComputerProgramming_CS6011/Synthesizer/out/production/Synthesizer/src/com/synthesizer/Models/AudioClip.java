package com.synthesizer.Models;

public class AudioClip {
    public static final int TOTAL_SAMPLES = 100;

    public AudioClip(){};

    public static double duration = 1.0;
    public static int sampleRate = 44100;
    public byte[] bytes = new byte[88200];

    public AudioClip(int value){
        for(int i = 0; i < sampleRate; i++)
            bytes[i] = (byte) value;
    }


    // return the sample passed as an int
    public short getSample(int index){
        short sample;
        byte rhs = bytes[index * 2 + 1];
        int lhs = bytes[index * 2] & 0xff;
        sample = (short)((rhs << 8) | lhs);
        return sample;
    }

    // set the sample passed as an int
    public void setSample(int index, short value){
        byte x = (byte) value;
        byte y = (byte) (value >> 8);
        bytes[2 * index] = x;
        bytes[2 * index + 1] = y;
    }

    public byte[] getData(){
        byte[] temp = new byte[88200];
        for(int i = 0; i < 88200; i++){
            temp[i] = bytes[i];
        }
        return temp;
    }
}
