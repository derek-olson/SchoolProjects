package com.synthesizer.Helpers;

import com.synthesizer.Views.ContainerController;
import javafx.beans.property.DoubleProperty;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;

import java.io.IOException;

public class HandleCableDraw {
    public DoubleProperty startX = new SimpleDoubleProperty();
    public DoubleProperty startY = new SimpleDoubleProperty();

    public HandleCableDraw(){}

    public void getLineBeginCoordinates(Pane pane, Circle circle, MouseEvent e){
        System.out.println(circle);
        startX.setValue(circle.getCenterX() + e.getX());
        startY.setValue(circle.getCenterY() + e.getY());
    }

    public void drawLine(Line line, Circle circle, Pane pane){
        circle.setOnMouseDragged((MouseEvent e) -> {
            line.setStartX(startX.getValue());
            line.setStartY(startY.getValue());
            line.setVisible(true);
            double endX = e.getSceneX();
            double endY = e.getSceneY();
            line.setEndX(endX);
            line.setEndY(endY);
            line.setVisible(true);
        });
        pane.getChildren().add(line);
    }

    public void bindStartCoords(Circle circle){
        startX.bind(circle.centerXProperty());
        startY.bind(circle.centerYProperty());
    }


}
