var net = require('net');

var client = new net.Socket();

client.connect(27015, 'localhost', function() {
	console.log('Connected');
	client.write('real_time_data');
});

client.on('data', function(data) {
	console.log('\nReceived: ' +  data + ' at '+ new Date().getTime());
	client.write('real_time_data');
	
});

client.on('close', function() {
	console.log('Connection closed');
});

client.on('error', function(err){
	// console.log('Im in error');
	// console.log(tmp);
	console.log(err);
});