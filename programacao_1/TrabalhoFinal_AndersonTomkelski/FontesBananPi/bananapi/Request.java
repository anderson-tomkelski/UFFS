package bananapi;
import java.io.ObjectInputStream;
import java.io.Serializable;
import java.net.ServerSocket;
import java.net.Socket;

import com.pi4j.io.gpio.BananaPiPin;
import com.pi4j.io.gpio.GpioController;
import com.pi4j.io.gpio.GpioFactory;
import com.pi4j.io.gpio.GpioPinDigitalOutput;
import com.pi4j.io.gpio.GpioPinPwmOutput;
import com.pi4j.io.gpio.Pin;
import com.pi4j.io.gpio.PinState;
import com.pi4j.platform.Platform;
import com.pi4j.platform.PlatformAlreadyAssignedException;
import com.pi4j.platform.PlatformManager;
import com.pi4j.util.CommandArgumentParser;


public class Request implements Serializable{
	public static void main(String[] args) throws InterruptedException, PlatformAlreadyAssignedException {
		try{
			PlatformManager.setPlatform(Platform.BANANAPI);
			final GpioController gpio = GpioFactory.getInstance();
			Pin lamp1 = CommandArgumentParser.getPin(BananaPiPin.class, BananaPiPin.GPIO_01, args);
			Pin lamp2 = CommandArgumentParser.getPin(BananaPiPin.class, BananaPiPin.GPIO_02, args);
			GpioPinPwmOutput lampPWM = gpio.provisionPwmOutputPin(BananaPiPin.GPIO_07);
			
			final GpioPinDigitalOutput output1 = gpio.provisionDigitalOutputPin(lamp1);
			final GpioPinDigitalOutput output2 = gpio.provisionDigitalOutputPin(lamp2);
			
			
			ServerSocket server = new ServerSocket(12341);
			while(true){
				// O método accept bloqueia a execução até que seja recebido um pedido de execução
				Socket client = server.accept();
				ObjectInputStream recept = new ObjectInputStream(client.getInputStream());
				
				String[] received = (String[]) recept.readObject();
				
				String tmp = received[0];
				
				String[] array = tmp.split(";");
				
				switch(array[0]){
				case "1":
					output1.toggle();
					break;
				case "2":
					output2.toggle();
					break;
				case "-1":
					int value = Integer.parseInt(array[1]);
					lampPWM.setPwm(value);
					break;
				}
				
				recept.close();
				client.close();
			}
		}catch (Exception e){
			System.out.println("Falha ao receber o pacote: "+ e.getMessage());
		}
	}
}
