var express = require('express');
var app = express();

app.get('/hello', function(req, res){
	res.set('Content-Type', 'text/plain');
	res.send('Hello, CC3000!\n');
});
app.get('/json', function(req,res){
	res.json({msg:'Hello CC3000 from JSON'});
});

app.listen(80);
console.log('Listening on port 80');