var http = require("http");
var url = require("url");

var votos = 0,
    soma = 0;

var port = process.env.PORT || 3000;

var server = http.createServer(function(req, res) {
  var response = (votos < 1) ? (0) : (Math.round(soma / votos));
  console.log("média = " + response);

  if(req.url.match(/\?voto=[1-5]$/)) {
    response = parseInt(url.parse(req.url, true).query.voto);
    soma += Math.min(Math.max(response, 1), 5);
    votos += 1;
    console.log("votos = " + votos + " ; soma = " + soma);
  }

  res.writeHead(200, {
    'Content-Type': 'text/plain',
    'Content-Length': 1
  });

  res.end(String(response));
});

server.listen(port, function() {
  console.log("ouvindo");
});
