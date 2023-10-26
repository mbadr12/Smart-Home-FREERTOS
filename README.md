# Smart Home Project

This is a README file for the Smart Home project implemented using FreeRTOS. The project focuses on creating a fully controlled home system where the user can interact with the system through a username and password authentication process. The password is the reverse of the username, and the user has a maximum of three attempts to enter the correct credentials. If the maximum number of attempts is exceeded, a buzzer is activated. Once authenticated, the system opens the door.

## System Overview

The Smart Home project utilizes FreeRTOS to create a comprehensive home automation system. The system incorporates various sensors and actuators to control different aspects of the home environment. The following hardware components are used:

- AVR Microcontroller: The AVR microcontroller acts as the main processing unit, responsible for coordinating the inputs from the sensors and controlling the actuators.

- LCD Display: The LCD display module is used to show important information such as the current temperature and system states.

- Keypad: The keypad serves as the input interface for the user to enter the username and password.

- LM35 Temperature Sensor: The LM35 temperature sensor measures the temperature of the home environment.

- LDR (Light Dependent Resistor): The LDR senses the ambient light intensity in the home.

- Buzzer: The buzzer is used to provide audio feedback, such as indicating incorrect login attempts.

- Servo Motor: The servo motor controls the opening and closing of the home's door.

- DC Motor: The DC motor is used for various purposes, such as Fan.

- LEDs: The LEDs are used for visual feedback and status indication.

## User Authentication

The system starts by prompting the user to enter a username and password. The password is the reverse of the username. The user has a maximum of three attempts to enter the correct credentials. If the maximum number of attempts is exceeded, the buzzer is activated as a warning.

## Home Automation

Once the user is successfully authenticated, the Smart Home system provides full control over various aspects of the home environment. The implemented features are as follows:

- Light Control: The LDR sensor continuously monitors the light intensity in the home. Based on the measured intensity, the system automatically adjusts the light intensity to ensure optimal lighting conditions.

- Temperature Control: The LM35 temperature sensor measures the temperature of the home. The system uses this information to control a fan, maintaining a comfortable temperature level.

- Door Control: The system incorporates a servo motor to control the opening and closing of the home's door. Once the user is authenticated, the door is automatically opened.

## Installation and Setup

To set up and run the Smart Home project, follow these steps:

1. Hardware Connections: Connect the AVR microcontroller, LCD display, keypad, LM35 temperature sensor, LDR sensor, buzzer, servo motor, DC motor, and LEDs according to the hardware specifications and pin mappings.

2. Software Dependencies: Install the necessary software dependencies for programming the AVR microcontroller and interfacing with the LCD, keypad, sensors, and actuators.

3. Code Compilation: Compile and upload the provided source code to the AVR microcontroller using your preferred programming environment.

4. Power On: Power on the system by connecting the appropriate power supply to the AVR microcontroller and the connected components.

5. User Authentication: When the system starts, enter the username and password as prompted. Remember that the password is the reverse of the username.

6. Home Automation: Once authenticated, the system will automatically control the lights based on the ambient light intensity, maintain the temperature using the temperature sensor and fan control, and open the door.

7. Enjoy: Explore and experience the convenience of a fully controlled smart home environment. Observe how the system adjusts the lighting and maintains a comfortable temperature level. Interact with the system using the keypad and monitor the system states on the LCD display.

## Troubleshooting

If you encounter any issues while setting up or running the Smart Home project, consider the following troubleshooting steps:

1. Hardware Connections: Verify that all the hardware components are properly connected according to the specifications and pin mappings.

2. Power Supply: Ensure that the power supply is supplying sufficient power to the AVR microcontroller and the connected components.

3. Code Verification: Double-check the uploaded code for any errors or compatibility issues with the AVR microcontroller and the connected components.

4. Keypad and LCD: Check the keypad and LCD connections and confirm that they are functioning correctly. Verify that the displayed information on the LCD is accurate.

5. Sensor and Actuator Connections: Verify the connections of the LM35 temperature sensor, LDR sensor, buzzer, servo motor, DC motor, and LEDs to ensure they are properly wired and connected to the corresponding pins of the AVR microcontroller.

6. Input Validation: Validate user inputs to prevent unexpected behavior or erroneous actions. Ensure that the username and password authentication process is working as expected.

7. Debugging: Utilize debugging tools and techniques to identify any potential issues in the code or hardware connections. Consider using serial communication or additional debugging outputs to monitor the system's behavior and identify any errors or malfunctions.

## Conclusion

The Smart Home project implemented using FreeRTOS provides a comprehensive home automation system. By leveraging an AVR microcontroller and various sensors and actuators, the system offers features such as user authentication, light control based on ambient light intensity, temperature control using a temperature sensor and fan control, and door automation. Follow the installation and setup instructions to enjoy the convenience of a fully controlled smart home. Experience the comfort and efficiency of an automated home environment.
