var http = require("http");
function getRandomInt(min, max) {
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min)) + min;
}

var server = http.createServer(function(req, res) {
    console.log("Request recebido");
    res.writeHead(200, {
        'Content-Type': 'text/plain',
        'Content-Length': 1
    });
    var response = getRandomInt(1, 4);
    var payload = new Buffer([String(response).charCodeAt()]);
    res.end(payload);
});

server.listen(3000, function() {
    console.log('ouvindo');
});