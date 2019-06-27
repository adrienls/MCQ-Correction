function Ajax(ip, port, server_images) {
    this.ip = ip;
    this.port = port;
    this.server_images = server_images;
}
Ajax.prototype.getIp = function () { return this.ip; };
Ajax.prototype.setIp = function (ip) { this.ip = ip; };
Ajax.prototype.getPort = function() { return this.port; };
Ajax.prototype.setPort = function(port) { this.port = port; };
Ajax.prototype.getServerImages = function() { return this.server_images; };
Ajax.prototype.setServerImages = function(server_images) { this.server_images = server_images; };
