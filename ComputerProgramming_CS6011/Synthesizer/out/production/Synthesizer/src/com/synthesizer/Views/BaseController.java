package com.synthesizer.Views;

import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.layout.BorderPane;

public abstract class BaseController {

    @FXML
    BorderPane borderPane;

    @FXML
    Label label;

    BaseController(String type){

    }


}
