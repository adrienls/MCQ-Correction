function Student(id, name, idPromotion, idExamination) {
    this.id = id;
    this.name = name;
    this.idPromotion = idPromotion;
    this.idExamination = idExamination;
}
Student.prototype.getId = function () { return this.id; };
Student.prototype.setId = function (id) { this.di = id; };
Student.prototype.getName = function () { return this.name; };
Student.prototype.setName = function (name) { this.name = name; };
Student.prototype.getIdPromotion = function () { return this.idPromotition; };
Student.prototype.setIdPromotion = function (IdPromotion) { this.idPromotion = IdPromotion; };
Student.prototype.getIdExamination = function () { return this.idExamination; };
Student.prototype.setIdExamination = function (IdExamination) { this.idExamination = IdExamination; };