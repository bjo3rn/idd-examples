// nodejs server that reads sensor data from an attached Arduino board and publishes it 
// Arduino must run code "nodeSerialServerArduino.ino"
// Uses static pages that have to be reloaded to update sensor data or toggle

// "http://localhost/" renders the page; 
// "http://localhost/?led=on" toggles the LED on
// "http://localhost/?led=off" toggles the LED off


var sys = require("sys"); // to print debug messages

// SETUP SERIAL PORT
var portName = "/dev/tty.usbmodem1421"; //TODO: change for your local system
var serialport = require("serialport");
var SerialPort = serialport.SerialPort; // localize object constructor
var sp = new SerialPort(portName, {
  baudrate: 57600,
  parser: serialport.parsers.readline("\n")
});

sp.on('open',function() {
  console.log('Port open');
});

sp.on("data", function (data) {
  sys.puts("received value: "+data);
  sensorReading = data;
});

var sensorReading="not yet available";
var ledState="not yet available";


// Set Up HTTP Server
var express = require('express');
var app = express();
app.set('views', __dirname + '/views');
app.set('view engine', 'jade');

app.get('/', function(req, res){
  if(req.query.led != undefined) {
    sys.puts("found led query parameter: "+req.query.led);
    if(req.query.led.toLowerCase()=="off") {
            sys.puts("case off");
      sp.write("0", function(err, results) {
          console.log('err ' + err);
          console.log('results ' + results);
        });
      ledState="off";
        
    } else if (req.query.led.toLowerCase()=="on") {
      sys.puts("case on");
      sp.write("1", function(err, results) {
          console.log('err ' + err);
          console.log('results ' + results);
        });
      ledState="on";
    }
  } else {
    sys.puts("no led query parameter");
  }
  
  //render the index.jade template with the provided variables
  res.render('index',
  { sensorReading : sensorReading,
    ledState      : ledState }
  );
});


// Start listening on port 80
app.listen(80);
console.log('Listening on port 80');

// If you get the following error:
// ERROR: events.js:2877: Uncaught TypeError: Uncaught, unspecified "error" event.
// Then you probably misspelled the port name.
// Error: listen EACCES - need to execute server w/ sudo
