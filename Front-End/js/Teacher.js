function Teacher(name) {
    this.name = name;
}
Teacher.prototype.getName = function () { return this.name; };
Teacher.prototype.setName = function (name) { this.name = name; };