package com.synthesizer.Helpers;

import javafx.event.EventHandler;
import javafx.scene.Node;
import javafx.scene.input.MouseEvent;

public class HandleDragEvent{
    double sceneX, sceneY;
    public static boolean draggable = false;

    public HandleDragEvent(){}

    public void handleMousePressed(MouseEvent mouseEvent)  {
        sceneX = mouseEvent.getSceneX();
        sceneY = mouseEvent.getSceneY();
    }

    public void handleMouseDrag(MouseEvent mouseEvent, Node node) {
        node.setOnMouseDragged((MouseEvent e) -> {
            Node node1 = e.getPickResult().getIntersectedNode();
            //System.out.println("Dragging widget " + node1.getClass().toString() );
            if (draggable)
                return;
            double offsetX = e.getSceneX() - sceneX;
            double offsetY = e.getSceneY() - sceneY;
            double newTranslateX = node.getLayoutX() + offsetX;
            double newTranslateY = node.getLayoutY() + offsetY;

            node.setLayoutX(newTranslateX);
            node.setLayoutY(newTranslateY);

            sceneX = e.getSceneX();
            sceneY = e.getSceneY();
        });
    }


    EventHandler<MouseEvent> filter = new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent mouseEvent){
            System.out.println("Filtering out event " + mouseEvent.getEventType());
            mouseEvent.consume();
        }
    };

}
