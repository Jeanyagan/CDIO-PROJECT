module com.example.cdioproject {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.xml;
    requires java.desktop;


    opens com.example.cdioproject to javafx.fxml;
    exports com.example.cdioproject;
}