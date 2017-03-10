var net=require('net');
var server=net.createServer();
server.on('connection',function(client){
	console.info("client connected");
	client.on('data',function(buff){
		console.info(buff);
		client.write(buff);
	});
	client.on('close',function(){
        console.info('client close');
    });
});

server.listen(9898, function(){
	console.info("server start on 9898");
});