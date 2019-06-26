function removeLastComma(string)
{
    let regex = /\,(?!\s*?[\{\[\"\'\w])/g;
    return string.replace(regex, '');
}
function displayPromotions(promotions)
{
    promotions = removeLastComma(promotions);
    promotions = JSON.parse(promotions);
    let text = '<div class="form-group mr-2"><button onclick="signOut()" id="signout" type="submit" class="btn btn-danger">Sign out</button></div>';
    text += '<div class="form-group mr-2"><select id="promotion" class="form-control">'
    for (let i = 0; i < promotions.length; i++) {
        text += '<option id='+promotions[i].id_promotion+'>'+promotions[i].name+'</option>';
    }
    text += '</select></div>';
    sessionStorage.setItem("idPromotion", promotions[0].id_promotion);
    $('#top-form').append(text);
}

function displayExaminations(examinations)
{
    examinations = removeLastComma(examinations);
    let data = JSON.parse(examinations);
    let text = '<div class="form-group mr-2"><select id="examination" class="form-control">'
    for (let i = 0; i < data.length; i++) {
        text += '<option id='+data[i].id_examination+'>'+data[i].name+'</option>';
    }
    text += '</select></div><button id="chooseExamination" type="submit" class="btn btn-primary">Choose</button>';
    $('#top-form').append(text);
}

function displayStudents(students)
{
    students = removeLastComma(students);
    let data = JSON.parse(students);
    if (data) {
        let studentsTable = document.getElementById("studentsTBody");
        studentsTable.innerText = "";
        for(let item of data)
        {
            tr = document.createElement('tr');
            tr.innerHTML = "<td id=\"idStudent"+item.id_student+"\" hidden='true'>"+ item.id_student +"</td>" +
                "<td><span id=\"nameStudent"+item.id_student+"\"  >"+item.firstname + ' ' +  item.lastname+ "\</td>" +
                "<td><button id=\"consult"+item.id_student+"\" class=\"btn btn-success\">Consult</button></td>" +
                "<td><button id=\"correct"+item.id_student+"\" class=\"btn btn-danger\">Correct</button></td>";
            studentsTable.appendChild(tr);

            document.getElementById("consult" + item.id_student).addEventListener("click", function () {
                sessionStorage.setItem("idStudent", document.getElementById('idStudent'+item.id_student).innerText);
                sessionStorage.setItem("nameStudent", document.getElementById('nameStudent'+item.id_student).innerText);
                displayConsultStudent();
            });
            document.getElementById("correct" + item.id_student).addEventListener("click", function () {
                sessionStorage.setItem("idStudent", document.getElementById('idStudent'+item.id_student).innerText);
                sessionStorage.setItem("nameStudent", document.getElementById('nameStudent'+item.id_student).innerText);
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
        '<div class="form-group mr-2">\n' +
        '            <button onclick="signOut()" id="signout" type="submit" class="btn btn-danger">Sign out</button>\n' +
        '        </div>\n' +
        '        <div id="studentInformations" class="form-group mr-2">\n' +
        '            <div class="card-text">Student: '+ sessionStorage.getItem('nameStudent') +' - Promotion '+ sessionStorage.getItem('idPromotion') +' - Examination '+ sessionStorage.getItem('idExamination') +'</div>\n' +
        '        </div>\n' +
        '        <button id="btnCorrect" class="btn btn-danger">Correct</button>\n' +
        '    </form>');
    let urlImage = "http://" + ajax.getServerImages() +"/" + sessionStorage.getItem('idExamination') + '/' + sessionStorage.getItem('idStudent') + ".jpg";
    $('#center-div').html('    <img class="img-fluid img-thumbnail mx-auto d-block" style="width: 50%" src="'+urlImage+'" alt="img-examination">\n')
    document.getElementById('btnCorrect').onclick = function correctAStudent(event) {
        event.preventDefault();
        document.location.href="index.html#correctStudent";
        //displayCorrectStudent('');
        ajaxRequest('GET', 'https://' + ajax.getIp() + ':' + ajax.getPort() + '/correction?id_examination:' + sessionStorage.getItem('idExamination') + '&id_student:' + sessionStorage.getItem('idStudent'), displayCorrectStudent);
    }
}

function displayCorrectStudent(responses)
{
    console.log(responses);
    let data = JSON.parse(responses);
    $('#page-top').html('    <h1 class="d-flex align-items-center justify-content-center h-100">Correct student</h1><br>\n' +
        '    <form class="form-inline d-flex justify-content-center h-100">\n' +
        '        <div class="form-group mr-2">\n' +
        '            <a class="btn btn-primary" href="index.html">Go home </a>\n' +
        '        </div>\n' +
        '<div class="form-group mr-2">' +
        '<button onclick="signOut()" id="signout" type="submit" class="btn btn-danger">Sign out</button>' +
        '</div>'+
        '        <div class="form-group mr-2">\n' +
        '            <div class="card-text">Student: '+ student.getName() +' - Promotion '+ student.getIdPromotion() +' - Examination '+ student.setIdExamination() +'</div>\n' +
        '        </div>\n' +
        '    </form><br><br>');
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
        '<img id="img" class="img-fluid img-thumbnail mx-auto d-block" style="width: 100%" src="data:image/png;base64, '+ data[0].image + '" alt="img-examination">' +
        '</div>\n' +
        '<div class="col-md-6">\n' +
        '<form>\n'+'<div id="checkboxes" class="form-row">\n';
    let nbResponses = 0;
    for(let key in data[1]) {
        if(data[1].hasOwnProperty(key))
        {
            nbResponses++;
        }
    }
    let nbElement = Object.keys(data).length -1 ;
    for (let i = 1; i<= nbElement; i++)
    {
        text += '<div class="form-group col-md-2">Q'+data[i].id_question+': </div>\n';
        for(let j = 1; j < nbResponses; j++)
        {
            text += '<div class="form-group col-md-2">\n';
            if (data[i][j] === "1")  {
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
        '<button type="submit" id="saveCorrection" class="btn btn-primary">Save the correction</button>\n' +
        '</form>\n' +
        '</div>\n' +
        '</div>' +
        '</div>';
    $('#center-div').html(text);
    document.getElementById('saveCorrection').onclick = function saveTheCorrection(event) {
        event.preventDefault();
        updateTheCorrection(data.length, nbResponses-1);
    }
}

function updateTheCorrection(nbQuestions, nbResponses)
{
    let jsonData = [{"idExamination":sessionStorage.getItem('idExamination'), "idStudent":sessionStorage.getItem('idStudent'), "idPromotion":sessionStorage.getItem('idPromotion')},];
    let tab = [];
    $("input:checkbox[name=response]").each(function()
    {
        tab.push((this).checked);
    });
    for (let i = 1; i <= nbQuestions; i++)
    {
        let row = [];
        //i === 1 ? row = tab.splice(0,i+nbResponses-1) :
        row =tab.splice(0,i+nbResponses-i);
        jsonData["q"+i] = row;
    }
    console.log(jsonData);
    ajaxRequest('PUT', 'https://' + ajax.getIp() + ':' + ajax.getPort() + '/sendCorrection?student_id='+ sessionStorage.getItem('idStudent') + '&responses='+jsonData, a);
}

function signOut() {
    Cookies.remove('token');
    sessionStorage.clear();
    document.location.href = "index.html";
}

function a() {
    window.alert("the promotion has been corrected!");
}

function b() {
    window.alert("the student has been corrected!");
    displayStudentsTable();
}