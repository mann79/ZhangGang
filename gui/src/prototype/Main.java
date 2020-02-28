package prototype;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

import java.io.IOException;

public class Main extends Application {
    private Stage primaryStage;
    private BorderPane rootLayout;

    @Override
    public void start(Stage primaryStage) throws Exception{
        this.primaryStage = primaryStage;
        this.primaryStage.setTitle("Chi-Square Prototype");

        initRootLayout();
        showMainView();
    }

    private void initRootLayout() {
        try {
            // Load RootLayout from fxml file
            this.rootLayout = FXMLLoader.load(getClass().getResource("view/RootLayout.fxml"));

            // Show the scene containing RootLayout
            primaryStage.setScene(new Scene(rootLayout));
            primaryStage.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void showMainView() {
        try {
            AnchorPane mainView = FXMLLoader.load(getClass().getResource("view/MainView.fxml"));

            this.rootLayout.setCenter(mainView);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}
