package com.company;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Rainfall {

    //default constructor
    public Rainfall(){};

    // initialize element to hold average rainfall
    private double averageRainfall;

    // initialize elements to hold parsed rainfall data
    private ArrayList monthlyAverages = new ArrayList();
    private ArrayList monthList = new ArrayList();
    private ArrayList yearList = new ArrayList();
    private ArrayList precipList = new ArrayList();

    //Scanner fileReader = new Scanner(new FileInputStream("atlanta.txt"));
    Scanner _scanner = new Scanner("atlanta.txt");

    ArrayList<String> months = new ArrayList<>(List.of(
            "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"));

    // method to read rainfall data into an array
    public void readData() {
        this._scanner.nextLine();
        while(this._scanner.hasNextLine()){
            System.out.println(this._scanner.nextLine());
            this.monthList.add(this._scanner.next());
            this.yearList.add(this._scanner.next());
            this.precipList.add(this._scanner.next());
        }
    }

    public void calculateAverage(){
        double counter = 0;
        double sum = 0;
        for(int i = 0; i < precipList.size(); i++){
            sum += (Double) precipList.get(i);
            counter += 1;
        }
        this.averageRainfall = sum/counter;
    }

    public void monthlyAverages(){
        for(int i = 0; i < 12; i++){
            double monthlySum = 0;
            double counter = 0;
            double monthlyAverage = 0;
            for (int j = 0; j < monthList.size(); j++){
                if (monthList.get(j) == months.get(i)) {
                    monthlySum += (Double) precipList.get(j);
                    counter += 1;
                }
            }
            monthlyAverage = monthlySum/counter;
            monthlyAverages.add(monthlyAverage);
        }
    }

    public void writeFile(ArrayList months, ArrayList monthlyAverages) throws FileNotFoundException {
        PrintWriter out = new PrintWriter(new FileOutputStream("outFile.txt"));
        for(int i = 0; i < 12; i++) {
            out.println("The average rainfall amount for " + months.get(i) + "is " + out.format("%.3f", monthlyAverages.get(i)) + " inches");
        }
    }

}
