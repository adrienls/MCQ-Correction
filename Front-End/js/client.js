function displayPromotions(promotions)
{
    let data = JSON.parse(promotions);
    let text = '<div class="form-group mr-2"><select id="promotion" class="form-control">'
    for (let i = 0; i < data.length; i++) {
        text += '<option id='+data[i].id+'>'+data[i].name+'</option>';
    }
    text += '</select></div>';
    sessionStorage.setItem("idPromotion", data[0].id);
    $('#top-form').append(text);
}

function displayExaminations(examinations)
{
    //let data = [{"id":"1","name":"examination1"},{"id":"2","name":"examination2"},];
    let data = JSON.parse(examinations);
    let text = '<div class="form-group mr-2"><select id="examination" class="form-control">'
    for (let i = 0; i < data.length; i++) {
        text += '<option id='+data[i].id+'>'+data[i].name+'</option>';
    }
    text += '</select></div><button id="chooseExamination" type="submit" class="btn btn-primary">Choose</button>';
    $('#top-form').append(text);
}

function displayStudents(students)
{
    let data = JSON.parse(students);
    //let data = [{"id":"1","firstname":"jean","lastname":"tomate"},{"id":"2","firstname":"sophie","lastname":"fraise"},{"id":"3","firstname":"jacques","lastname":"patate"},];
    //let data = false;
    if (data) {
        let studentsTable = document.getElementById("studentsTBody");
        studentsTable.innerText = "";
        for(let item of data)
        {
            tr = document.createElement('tr');
            tr.innerHTML = "<td id=\"idStudent"+item.id+"\">" + item.id_student + "</td>" +
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
        '            <div class="card-text">Student: '+ sessionStorage.getItem('nameStudent') +' - Promotion '+ sessionStorage.getItem('idPromotion') +' - Examination '+ sessionStorage.getItem('idExamination') +'</div>\n' +
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
        '            <div class="card-text">Student: '+ sessionStorage.getItem('nameStudent') +' - Promotion '+ sessionStorage.getItem('idPromotion') +' - Examination '+ sessionStorage.getItem('idExamination') +'</div>\n' +
        '        </div>\n' +
        '    </form><br><br>');
    let urlImage = "http://10.0.1.49/"+sessionStorage.getItem('idExamination')+'/'+sessionStorage.getItem('idStudent')+".jpg";

    let text =
        '<div class="row align-content-center">' +
            '<div class="col-md-6">' +
                '<p>Unedited questionnaire returned by the student</p>' +
            '</div>' +
            '<div class="col-md-6">' +
                '<p>Answers saved in the database</p>' +
            '</div>' +
        '</div>' +
        '<div class="row align-content-center">' +
            '<div class="col-md-6">' +
                '<img id="img" class="img-fluid img-thumbnail mx-auto d-block" style="width: 100%" src="'+urlImage+'" alt="img-examination">' +
            '</div>\n' +
        '<div class="col-md-6">\n' +
        '<form>\n'+'<div id="checkboxes" class="form-row">\n';

    let data = [{"id":"1","1":"true","2":"false", "3":"false","4":"true", "5":"true"},{"id":"2","1":"true","2":"false", "3":"false","4":"true", "5":"true"},{"id":"3","1":"true","2":"false", "3":"false","4":"true", "e":"true"},];
    let nbResponses = 0;
    for(let key in data[0])
        if(data[0].hasOwnProperty(key))
            nbResponses++;
    for (let item of data)
    {
        text += '<div class="form-group col-md-2">Q'+item.id+': </div>\n';
        for(let i = 1; i < nbResponses; i++)
        {
            text += '<div class="form-group col-md-2">\n';
            if (item[i] === "true")  {
                text += '<input id="checkbox'+i+'" class="form-check-input" type="checkbox" name="response" checked>';
            }
            else {
                text += '<input id="checkbox'+i+'" class="form-check-input" name="response" type="checkbox">';
            }
            text += '<label class="form-check-label">R'+ i +'</label>\n' + '</div>\n';
        }
    }
        text +=
            '</div>' +
        '<button type="submit" id="saveCoorection" class="btn btn-primary">Save the correction</button>\n' +
        '</form>\n' +
        '</div>\n' +
        '</div>' +
        '</div>';
    $('#center-div').html(text);
    document.getElementById('saveCoorection').onclick = function saveTheCorrection(event) {
        event.preventDefault();
        updateTheCorrection(data.length, nbResponses-1);
    }
}

function updateTheCorrection(nbQuestions, nbResponses)
{
    let jsonData = [{"idExamination":sessionStorage.getItem('idExamination'), "idStudent":sessionStorage.getItem('idStudent'), "idPromotition":sessionStorage.getItem('idPromotion')},];
    let tab = [];
    $("input:checkbox[name=response]").each(function()
    {
        tab.push((this).checked);
    });
    for (let i = 1; i <= nbQuestions; i++)
    {
        let row = [];
        i === 1 ? row = tab.splice(0,i+nbResponses-1) : row =tab.splice(0,i+nbResponses-2);
        jsonData["q"+i] = row;
    }
    console.log(jsonData);
}