/*********
 * IDD Particle Cloud example
 */

// READ STATE
// curl https://api.particle.io/v1/devices/{DEVICEID}/ledstate?access_token={TOKEN}
// WRITE STATE
// curl https://api.particle.io/v1/devices/{DEVICEID}/led -d access_token={TOKEN} -d "args=on"

     
#if defined(ARDUINO) 
SYSTEM_MODE(AUTOMATIC);
#endif
STARTUP(WiFi.selectAntenna(ANT_INTERNAL));

int led1 = D7;
int ledstate = LOW;
void setup()
{

   // Here's the pin configuration, same as last time
   pinMode(led1, OUTPUT);

   // We are also going to declare a Particle.function so that we can turn the LED on and off from the cloud.
   Particle.function("led",ledToggle);
   // This is saying that when we ask the cloud for the function "led", it will employ the function ledToggle() from this app.

    // We are going to declare a Particle.variable() here so that we can access the value of the LED from the cloud.
    Particle.variable("ledstate", &ledstate, INT);

   // For good measure, let's also make sure both LEDs are off when we start:
   digitalWrite(led1, ledstate);

}


/* Last time, we wanted to continously blink the LED on and off
Since we're waiting for input through the cloud this time,
we don't actually need to put anything in the loop */

void loop()
{
   // Nothing to do here
}

// We're going to have a super cool function now that gets called when a matching API request is sent
// This is the ledToggle function we registered to the "led" Particle.function earlier.

int ledToggle(String command) {
     /* Particle.functions always take a string as an argument and return an integer.
    Since we can pass a string, it means that we can give the program commands on how the function should be used.
    In this case, telling the function "on" will turn the LED on and telling it "off" will turn the LED off.
    Then, the function returns a value to us to let us know what happened.
    In this case, it will return 1 for the LEDs turning on, 0 for the LEDs turning off,
    and -1 if we received a totally bogus command that didn't do anything to the LEDs.
    */

    if (command=="on") {
        ledstate = HIGH;
        digitalWrite(led1,ledstate);
        return 1;
    }
    else if (command=="off") {
        ledstate=LOW;
        digitalWrite(led1,ledstate);
        return 0;
    }
    else {
        return -1;
    }
}



