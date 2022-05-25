module com.example.cdioproject {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.cdioproject to javafx.fxml;
    exports com.example.cdioproject;
}