import java.util.concurrent.Future;

import com.pi4j.io.gpio.BananaPiPin;
import com.pi4j.io.gpio.GpioController;
import com.pi4j.io.gpio.GpioFactory;
import com.pi4j.io.gpio.GpioPinDigitalOutput;
import com.pi4j.io.gpio.Pin;
import com.pi4j.io.gpio.PinState;
import com.pi4j.io.gpio.event.GpioPinDigitalStateChangeEvent;
import com.pi4j.io.gpio.event.GpioPinListenerDigital;
import com.pi4j.platform.Platform;
import com.pi4j.platform.PlatformAlreadyAssignedException;
import com.pi4j.platform.PlatformManager;
import com.pi4j.util.CommandArgumentParser;
import com.pi4j.util.Console;
import com.pi4j.util.ConsoleColor;

public class Gpio {

	public static void main(String[] args) throws InterruptedException, PlatformAlreadyAssignedException {
		PlatformManager.setPlatform(Platform.BANANAPI);
		
		final Console console = new Console();
		
		console.title("<-- The Pi4J Project -->", "GPIO Output Example");
		
		console.promptForExit();
		
		final GpioController gpio = GpioFactory.getInstance();
		
		Pin pin = CommandArgumentParser.getPin(BananaPiPin.class, BananaPiPin.GPIO_01, args);
		
		final GpioPinDigitalOutput output = gpio.provisionDigitalOutputPin(pin, "My Output", PinState.HIGH);
		
		output.setShutdownOptions(false, PinState.LOW);
		
		output.addListener(new GpioPinListenerDigital() {
			
			@Override
			public void handleGpioPinDigitalStateChangeEvent(GpioPinDigitalStateChangeEvent event) {
				console.println(" --> GPIO PIN STATE CHANGE: " + event.getPin() + " = " + 
						ConsoleColor.conditional(
								event.getState().isHigh(),
								ConsoleColor.GREEN,
								ConsoleColor.RED,
								event.getState()));
			}
		});
		
		console.println("... Successfully provisioned output pin: " + output.toString());
		console.emptyLine();
		console.box("The GPIO output pin states will cycle HIGH and LOW states now");
		console.emptyLine();
		
		
		console.println("--> [" + output.toString() + "] state was provisioned with state = " +
				ConsoleColor.conditional(output.getState().isHigh(), 
						ConsoleColor.GREEN, 
						ConsoleColor.RED, 
						output.getState()));
		
		Thread.sleep(500);
		
		console.emptyLine();
		console.println("Setting output pin state is set to LOW");
		output.low();
		
		Thread.sleep(500);
		
		console.emptyLine();
		console.println("Setting output pin state from LOW to HIGH");
		output.high();
		
		Thread.sleep(500);
		
		console.emptyLine();
		console.println("Toggling output pin state from HIGH to LOW");
		output.toggle();
		
		Thread.sleep(500);
		
		console.emptyLine();
		console.println("Pulsing output pin state HIGH for 1 second");
		output.pulse(1000, true);
		
		Thread.sleep(50);
		
		console.emptyLine();
		console.println("Blinking output pin state between HIGH and LOW for 3 seconds with a blink rate of 250ms");
		Future future = output.blink(250, 3000);
		
		while(!future.isDone()){
			Thread.sleep(50);
		}
		
		gpio.shutdown();	
	}
}
