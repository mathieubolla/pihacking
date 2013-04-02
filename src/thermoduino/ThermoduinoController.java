/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package thermoduino;

import com.pi4j.io.serial.Serial;
import com.pi4j.io.serial.SerialDataEvent;
import com.pi4j.io.serial.SerialDataListener;
import com.pi4j.io.serial.SerialFactory;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.text.Text;

/**
 *
 * @author mathieu
 */
public class ThermoduinoController implements Initializable {
    
    @FXML
    private Text output;
    
    /**
     *
     * @param url
     * @param rb
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        output.setText("19.0°C");
        
        Serial serial = SerialFactory.createInstance();
        serial.addListener(new SerialDataListener() {

            @Override
            public void dataReceived(SerialDataEvent event) {
                output.setText(event.getData());
            }
            
        });
        serial.open("/dev/ttyAMA0", 9600);
    }    
}
