package com.synthesizer.Views;

import com.synthesizer.Factories.ViewModelFactory;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import java.io.IOException;

public class ViewHandler {
    private Stage stage;
    private ViewModelFactory viewModelFactory;

    public ContainerController containerController;
    public SineWaveController sineWaveController;
    public SquareWaveController squareWaveController;
    public MixerController mixerController;
    public VolumeFilterController volumeFilterController;
    public SpeakerController speakerController;

    public ViewHandler(Stage stage, ViewModelFactory viewModelFactory){
        this.stage = stage;
        this.viewModelFactory = viewModelFactory;

        //this.containerController = new ContainerController(viewModelFactory.getContainerViewModel());
        //this.sineWaveController = new SineWaveController(viewModelFactory.getSineWaveViewModel());
        //this.squareWaveController = new SquareWaveController(viewModelFactory.getSquareWaveViewModel());
        //this.mixerController = new MixerController(viewModelFactory.getMixerViewModel());
        //this.volumeFilterController = new VolumeFilterController(viewModelFactory.getVolumeViewModel());
        //this.speakerController = new SpeakerController(viewModelFactory.getSpeakerViewModel());
    }

    public void start() throws Exception{
        openView();
    }

    private void openView()throws IOException{
        Scene scene;
        FXMLLoader loader = new FXMLLoader();
        Parent root;

        loader.setLocation(getClass().getResource("Container.fxml"));
        root = loader.load();
        ContainerController view = loader.getController();
        view.init();
        stage.setTitle("Synthesizer");

        scene = new Scene(root);
        scene.getStylesheets().addAll(this.getClass().getResource("styles.css").toExternalForm());
        stage.setScene(scene);
        stage.show();
    }
}
