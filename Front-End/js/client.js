//group
document.getElementById("chooseGroup").addEventListener("click", function()
{
    let option = document.querySelector("#group > option:checked");
    ajaxRequest('GET', 'php/request.php/students?groupId='+option.id, displayStudents);
});
//student
document.getElementById("chooseStudent").addEventListener("click", function()
{
    let option = document.querySelector("#student > option:checked");
    ajaxRequest('GET', 'php/request.php/grades?studentId='+option.id, displayGrades);
});
//modify grade
document.getElementById("chooseGrade").addEventListener("click", function()
{
    //erreur recupération gradeId mais fonction php implementée
    let option = document.querySelector("#grade");

    console.log(option.children);
    ajaxRequest('PUT', 'php/request.php/grades/' + option, displayModifyGrade);

});


function displayGroups(groups)
{

    let text = '<div class="panel panel-default"><div class="panel-body"><div class="form-inline"><label for="group">Promotion </label><select id="group" class="form-control">'

    let data = JSON.parse(groups);
    for (let i = 0; i < data.length; i++) {
        text += '<option id='+data[i].id+'>'+data[i].name+'</option>';
    }
    text += '</select><button class="btn btn-success" id="chooseGroup">Choisir</button></div></div></div>';
    $('#chooseGroup').html(text);

}

function displayStudents(students) {
    let text = '<div class="panel panel-default"><div class="panel-body"><div class="form-inline"><label for="student">Etudiant </label><select id="student" class="form-control">'

    let data = JSON.parse(students);
    for (let i = 0; i < data.length; i++) {
        text += '<option id='+data[i].id+'>' + data[i].firstname + " " + data[i].lastname+'</option>';
    }
    text += '</select><button class="btn btn-success" id="chooseGroup">Choisir</button></div></div></div>';
    $('#chooseStudent').html(text);
}

function displayGrades(grades) {
    let text = '<div class="panel panel-default"><div class="panel-body"><table class="table table-striped"><thead><tr><th scope="col">Matière</th><th scope="col">Note</th><th scope="col"></th><th scope="col"></th></tr></thead><tbody>';
    let data = JSON.parse(grades);
    for (let i = 0; i < data.length; i++) {
        text += '<tr id="grade">';
        text += '<td>' + data[i].course + '</td>';
        text += '<td><input id='+data[i].gradeId+' class="form-control" type="number" value="' + data[i].grade + '"/></td>';
        text += '<td><button class="btn btn-success" >Modifier</button></td>';
        text += '<td><button class="btn btn-danger" id="deleteGrade">Supprimer</button></td>';
        text += '</tr>'
    }
    text += '</tbody></table></div></div>';
    $('#chooseGrade').html(text);
}

function displayModifyGrade(response)
{
    if (response)
    {
        console.log("OK!")
        $('#alertGrade').html('<div class="alert alert-success text-center" role="alert"> La note a bien été modifiée! </div>');

    }
    else
    {
        $('#alertGrade').html('<div class="alert alert-danger text-center" role="alert"> Erreur note! </div>');
    }
}