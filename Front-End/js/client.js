function displayPromotions(groups)
{
    let data = JSON.parse(groups);
    let text = '<div class="form-group mr-2"><select id="promotion" class="form-control">'
    for (let i = 0; i < data.length; i++) {
        text += '<option id='+data[i].id+'>'+data[i].name+'</option>';
    }
    text += '</select></div>';
    console.log(document.getElementById('promotion'));
    $('#top-form').append(text);
}

function displayExaminations(examinations)
{
    //let data = JSON.parse(examinations);
    let data = [{"id":"1","name":"examination1"},{"id":"2","name":"examination2"},];
    let text = '<div class="form-group mr-2"><select id="examination" class="form-control">'
    for (let i = 0; i < data.length; i++) {
        text += '<option id='+data[i].id+'>'+data[i].name+'</option>';
    }
    text += '</select></div><button id="chooseExamination" type="submit" class="btn btn-primary">Choose</button>';
    $('#top-form').append(text);
}

function displayStudents(students)
{
    //let data = JSON.parse(students);
    let data = [{"id":"1","firstname":"jean","lastname":"tomate"},{"id":"2","firstname":"sophie","lastname":"fraise"},{"id":"3","firstname":"jacques","lastname":"patate"},];
    //let data = false;
    if (data) {
        let text;
        let studentsTable = document.getElementById("studentsTBody");
        for(let item of data)
        {
            tr = document.createElement('tr');
            tr.innerHTML = "<td id=\"idStudent"+item.id+"\">" + item.id + "</td>" +
                "<td><span id=\"nameStudent"+item.id+"\"  >"+item.firstname + ' ' +  item.lastname+ "\</td>" +
                "<td><button id=\"consult"+item.id+"\" class=\"btn btn-success\">Consult</button></td>" +
                "<td><button id=\"correct"+item.id+"\" class=\"btn btn-danger\">Correct</button></td>";
            studentsTable.appendChild(tr);

            document.getElementById("consult" + item.id).addEventListener("click", function (event) {
                //let button = event.target;
                sessionStorage.setItem("idStudent", document.getElementById('idStudent'+item.id).innerText);
                sessionStorage.setItem("nameStudent", document.getElementById('nameStudent'+item.id).innerText);
                displayConsultStudent();
            });
            document.getElementById("correct" + item.id).addEventListener("click", function (event) {
                //let button = event.target;
                sessionStorage.setItem("idStudent", document.getElementById('idStudent'+item.id).innerText);
                sessionStorage.setItem("nameStudent", document.getElementById('nameStudent'+item.id).innerText);
                displayCorrectStudent();
            });
        }
    }
    else {
        $('#studentsTBody').html('<tr><td colspan="4" style="color: red">No students</td></tr>');

    }
}

function displayConsultStudent()
{
    $('#page-top').html('<h1 class="d-flex align-items-center justify-content-center h-100">Consult student</h1><br>\n' +
        '    <form class="form-inline d-flex justify-content-around h-100">\n' +
        '        <div class="form-group mr-2">\n' +
        '            <a class="btn btn-primary" href="index.html">Go home </a>\n' +
        '        </div>\n' +
        '        <div id="studentInformations" class="form-group mr-2">\n' +
        '            <div class="card">Student: '+ sessionStorage.getItem('nameStudent') +' - Promotion '+ sessionStorage.getItem('idPromotion') +' - Examination '+ sessionStorage.getItem('idExamination') +'</div>\n' +
        '        </div>\n' +
        '        <button id="btnCorrect" class="btn btn-danger">Correct</button>\n' +
        '    </form>');
    let urlImage = "http://10.0.1.49/"+sessionStorage.getItem('idExamination')+'/'+sessionStorage.getItem('idStudent')+".jpg";
    $('#center-div').html('    <img class="img-fluid img-thumbnail mx-auto d-block" style="width: 50%" src="'+urlImage+'" alt="img-examination">\n')
    document.getElementById('btnCorrect').onclick = function correctAStudent(event) {
        event.preventDefault();
        document.location.href="index.html#correctStudent";
        displayCorrectStudent();
    }
}

function displayCorrectStudent()
{
    $('#page-top').html('    <h1 class="d-flex align-items-center justify-content-center h-100">Correct student</h1><br>\n' +
        '    <form class="form-inline d-flex justify-content-center h-100">\n' +
        '        <div class="form-group mr-2">\n' +
        '            <a class="btn btn-primary" href="index.html">Go home </a>\n' +
        '        </div>\n' +
        '        <div class="form-group mr-2">\n' +
        '            <div class="card">Student: '+ sessionStorage.getItem('nameStudent') +' - Promotion '+ sessionStorage.getItem('idPromotion') +' - Examination '+ sessionStorage.getItem('idExamination') +'</div>\n' +
        '        </div>\n' +
        '    </form><br><br>');
    let urlImage = "http://10.0.1.49/"+sessionStorage.getItem('idExamination')+'/'+sessionStorage.getItem('idStudent')+".jpg";

    let text =
        '<div class="row align-content-center">' +
            '<div class="col-md-6">' +
                '<p>questionnaire rendu par létudiant non modifiée</p>' +
            '</div>' +
            '<div class="col-md-6">' +
                '<p>réponses enregistrées dans la bdd</p>' +
            '</div>' +
        '</div>' +
        '<div class="row align-content-center">' +
            '<div class="col-md-6">' +
                '<img id="img" class="img-fluid img-thumbnail mx-auto d-block" style="width: 100%" src="'+urlImage+'" alt="img-examination">' +
            '</div>\n' +
        '<div class="col-md-6">\n' +
        '<form>\n'+'<div class="form-row">\n';

    let data = [{"id":"1","1":"true","2":"false", "3":"false","4":"true", "5":"true"},{"id":"2","1":"true","2":"false", "3":"false","4":"true", "5":"true"},{"id":"3","1":"true","2":"false", "3":"false","4":"true", "e":"true"},];
    let nbResponses = 0;
    for(let key in data[0])
        if(data[0].hasOwnProperty(key))
            nbResponses++;
    console.log("nbResponses: " + (nbResponses-1));
    for (let item of data)
    {
        text += '<div class="form-group col-md-2">Q'+item.id+': </div>\n';
        for(let i = 1; i < nbResponses; i++)
        {
            text += '<div class="form-group col-md-2">\n';
            if (item[i] === "true")  {
                text += '<input class="form-check-input" type="checkbox" checked>';
            }
            else {
                text += '<input class="form-check-input" type="checkbox">';
            }
            text += '<label class="form-check-label">R'+ i +'</label>\n' + '</div>\n';
        }
    }
        text +=
            '</div>' +
        '<button type="submit" class="btn btn-primary">Save the correction</button>\n' +
        '</form>\n' +
        '</div>\n' +
        '</div>' +
        '</div>';
    $('#center-div').html(text);

}