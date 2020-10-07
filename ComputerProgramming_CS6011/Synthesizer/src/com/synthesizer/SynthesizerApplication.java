package com.synthesizer;

import com.synthesizer.Factories.ModelFactory;
import com.synthesizer.Views.ViewHandler;
import com.synthesizer.Factories.ViewModelFactory;
import javafx.application.Application;
import javafx.stage.Stage;

public class SynthesizerApplication extends Application {

    public static void main(String[] args) {
        launch(args);
        //Application.launch(SynthesizerApplication);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        ModelFactory modelFactory = new ModelFactory();
        ViewModelFactory viewModelFactory = new ViewModelFactory(modelFactory);
        ViewHandler viewHandler = new ViewHandler(primaryStage, viewModelFactory);
        viewHandler.start();
    }


}
