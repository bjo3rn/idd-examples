// node.js server that receives data via HTTP requests (e.g., from a CC3000 board) and publishes is live
// data should be encoded in the URL like so: "http://localhost/update?value=xyz"
// uses socket.io to communicate with a single page without reloads
// "http://localhost/" renders the page;

var sys = require("sys"); // to print debug messages
var io = require('socket.io');

// Set Up HTTP Server
var express = require('express');
var app = express();

// look in the "public/" directory for HTML files to serve
// this takes care of rendering index.html when a request for "/" comes in
app.use(express.static(__dirname + '/public'));

// Start listening on port 8080
var server = app.listen(8080);
var io = require('socket.io').listen(server);

// a global variable: value
var value = 0;

// when data is received via a HTTP GET request to /update
app.get('/update', function(req,res){
  console.log('Received update request');
  value = req.param('value');
  console.log(value);
  //update connected web sockets
  io.sockets.emit("sensorReading",value);
  //send back a response
  res.set('Content-Type', 'text/plain');
  res.send('OK\n');
});

// path to get value
app.get('/value', function(req,res){
  res.set('Content-Type', 'text/plain');
  res.send(value);
});

console.log('Listening on port 8080');
