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
        $('#studentsTBody').html('');
        for (let i = 0; i < data.length; i++) {
            text += '<tr id=studentId' + data[i].id + '>';
            text += '<td id="nameStudent" colspan="2">'+ data[i].firstname + ' ' + data[i].lastname + '</td>';
            text += '<td><button id="btnConsult" class="btn btn-success">Consult</button></td>';
            text += '<td><button id="btnCorrect" class="btn btn-danger">Correct</button></td>';
            text += '</tr>';
        }
        $('#studentsTBody').append(text);

        document.getElementById('btnConsult').onclick = function consultAStudent(event) {
            event.preventDefault();
            document.location.href="index.html#consultStudent";
            console.log("idStudent = " + document.getElementById('studentId'));
            sessionStorage.setItem("idStudent", "1");
            sessionStorage.setItem("nameStudent", document.getElementById('nameStudent').innerText);
            displayConsultStudent();
        };
        document.getElementById('btnCorrect').onclick = function correctAStudent(event) {
            event.preventDefault();
            document.location.href="index.html#correctStudent";
            displayCorrectStudent();
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
        '            <div class="card">firstName lastName - promotionName - examinationName</div>\n' +
        '        </div>\n' +
        '        <button id="btnCorrect" class="btn btn-danger">Correct</button>\n' +
        '    </form>');
    $('#center-div').html('    <img class="img-fluid img-thumbnail mx-auto d-block" style="width: 50%" src="http://10.0.1.49/1/19.jpg" alt="img-examination">\n')
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
        '            <div class="card">Student: Pierre Tabou - Promotion 1 - Examination 1</div>\n' +
        '        </div>\n' +
        '    </form><br><br>');
    $('#center-div').html('<div class="row align-content-center">\n' +
        '            <div class="col-md-6">\n' +
        '                <img id="img" class="img-fluid img-thumbnail mx-auto d-block" style="width: 100%" src="http://10.0.1.49/1/19.jpg" alt="img-examination">            </div>\n' +
        '            <div class="col-md-6">\n' +
        '                <form>\n' +
        '                <div class="form-row">\n' +
        '                    <div class="form-group col-md-2">Q1: </div>\n' +
        '                    <div class="form-group col-md-2">\n' +
        '                        <input class="form-check-input" type="checkbox">\n' +
        '                        <label class="form-check-label">R1</label>\n' +
        '                    </div>\n' +
        '                    <div class="form-group col-md-2">\n' +
        '                        <input class="form-check-input" type="checkbox" checked>\n' +
        '                        <label class="form-check-label">R2</label>\n' +
        '                    </div>\n' +
        '                    <div class="form-group col-md-2">\n' +
        '                        <input class="form-check-input" type="checkbox" checked>\n' +
        '                        <label class="form-check-label">R3</label>\n' +
        '                    </div>\n' +
        '                    <div class="form-group col-md-2">\n' +
        '                        <input class="form-check-input" type="checkbox">\n' +
        '                        <label class="form-check-label">R4</label>\n' +
        '                    </div>\n' +
        '                    <div class="form-group col-md-2">\n' +
        '                        <input class="form-check-input" type="checkbox">\n' +
        '                        <label class="form-check-label">R5</label>\n' +
        '                    </div>\n' +
        '                </div>\n' +
        '                    <div class="form-row">\n' +
        '                        <div class="form-group col-md-2">Q2: </div>\n' +
        '                        <div class="form-group col-md-2">\n' +
        '                            <input class="form-check-input" type="checkbox">\n' +
        '                            <label class="form-check-label">R1</label>\n' +
        '                        </div>\n' +
        '                        <div class="form-group col-md-2">\n' +
        '                            <input class="form-check-input" type="checkbox">\n' +
        '                            <label class="form-check-label">R2</label>\n' +
        '                        </div>\n' +
        '                        <div class="form-group col-md-2">\n' +
        '                            <input class="form-check-input" type="checkbox" checked>\n' +
        '                            <label class="form-check-label">R3</label>\n' +
        '                        </div>\n' +
        '                        <div class="form-group col-md-2">\n' +
        '                            <input class="form-check-input" type="checkbox" checked>\n' +
        '                            <label class="form-check-label">R4</label>\n' +
        '                        </div>\n' +
        '                        <div class="form-group col-md-2">\n' +
        '                            <input class="form-check-input" type="checkbox">\n' +
        '                            <label class="form-check-label">R5</label>\n' +
        '                        </div>\n' +
        '                    </div>\n' +
        '                    <div class="form-row">\n' +
        '                        <div class="form-group col-md-2">Q3: </div>\n' +
        '                        <div class="form-group col-md-2">\n' +
        '                            <input class="form-check-input" type="checkbox">\n' +
        '                            <label class="form-check-label">R1</label>\n' +
        '                        </div>\n' +
        '                        <div class="form-group col-md-2">\n' +
        '                            <input class="form-check-input" type="checkbox" checked>\n' +
        '                            <label class="form-check-label">R2</label>\n' +
        '                        </div>\n' +
        '                        <div class="form-group col-md-2">\n' +
        '                            <input class="form-check-input" type="checkbox">\n' +
        '                            <label class="form-check-label">R3</label>\n' +
        '                        </div>\n' +
        '                        <div class="form-group col-md-2">\n' +
        '                            <input class="form-check-input" type="checkbox">\n' +
        '                            <label class="form-check-label">R4</label>\n' +
        '                        </div>\n' +
        '                        <div class="form-group col-md-2">\n' +
        '                            <input class="form-check-input" type="checkbox" checked>\n' +
        '                            <label class="form-check-label">R5</label>\n' +
        '                        </div>\n' +
        '                    </div>\n' +
        '                    <div class="form-row">\n' +
        '                        <div class="form-group col-md-2">Q4: </div>\n' +
        '                        <div class="form-group col-md-2">\n' +
        '                            <input class="form-check-input" type="checkbox">\n' +
        '                            <label class="form-check-label">R1</label>\n' +
        '                        </div>\n' +
        '                        <div class="form-group col-md-2">\n' +
        '                            <input class="form-check-input" type="checkbox" checked>\n' +
        '                            <label class="form-check-label">R2</label>\n' +
        '                        </div>\n' +
        '                        <div class="form-group col-md-2">\n' +
        '                            <input class="form-check-input" type="checkbox" checked>\n' +
        '                            <label class="form-check-label">R3</label>\n' +
        '                        </div>\n' +
        '                        <div class="form-group col-md-2">\n' +
        '                            <input class="form-check-input" type="checkbox">\n' +
        '                            <label class="form-check-label">R4</label>\n' +
        '                        </div>\n' +
        '                        <div class="form-group col-md-2">\n' +
        '                            <input class="form-check-input" type="checkbox" checked>\n' +
        '                            <label class="form-check-label">R5</label>\n' +
        '                        </div>\n' +
        '                    </div>\n' +
        '                    <div class="form-row">\n' +
        '                        <div class="form-group col-md-2">Q5: </div>\n' +
        '                        <div class="form-group col-md-2">\n' +
        '                            <input class="form-check-input" type="checkbox">\n' +
        '                            <label class="form-check-label">R1</label>\n' +
        '                        </div>\n' +
        '                        <div class="form-group col-md-2">\n' +
        '                            <input class="form-check-input" type="checkbox" checked>\n' +
        '                            <label class="form-check-label">R2</label>\n' +
        '                        </div>\n' +
        '                        <div class="form-group col-md-2">\n' +
        '                            <input class="form-check-input" type="checkbox">\n' +
        '                            <label class="form-check-label">R3</label>\n' +
        '                        </div>\n' +
        '                        <div class="form-group col-md-2">\n' +
        '                            <input class="form-check-input" type="checkbox" checked>\n' +
        '                            <label class="form-check-label">R4</label>\n' +
        '                        </div>\n' +
        '                        <div class="form-group col-md-2">\n' +
        '                            <input class="form-check-input" type="checkbox">\n' +
        '                            <label class="form-check-label">R5</label>\n' +
        '                        </div>\n' +
        '                    </div>\n' +
        '                    <button type="submit" class="btn btn-primary">Save the correction</button>\n' +
        '                </form>\n' +
        '            </div>\n' +
        '    </div>');
}