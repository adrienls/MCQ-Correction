function Ajax(ip, port) {
    this.ip = ip;
    this.port = port;
}
Ajax.prototype.getIp = function () { return this.ip; };
Ajax.prototype.setIp = function (ip) { this.ip = ip; };
Ajax.prototype.getPort = function() { return this.port; };
Ajax.prototype.setPort = function(port) { this.port = port; };

let ajax = new Ajax('localhost', '8080');