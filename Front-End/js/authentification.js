let ajax = new Ajax('localhost', '8080', '10.0.1.19');

ajaxRequest('GET', 'https://' + ajax.getIp() + ':' + ajax.getPort() + '/login?login:' + sessionStorage.getItem('login_teacher'), displayStudentsTable);

document.getElementById('authentication-send').onclick = validateLogin;
function validateLogin(event)
{
    event.preventDefault();
    let login = document.getElementById('inputLogin').value;
    let password = document.getElementById('inputPassword').value;
    sessionStorage.setItem('login_teacher', login);
    ajaxLogin('GET', 'https://' + ajax.getIp() + ':' + ajax.getPort() + '/authenticate?login:'+btoa(login)+'&password:'+btoa(password), setTokenCookie, login, password);
}

function ajaxLogin(type, request, callback)
{
    let xhr;
    xhr = new XMLHttpRequest();
    xhr.open(type, request, true);
    xhr.withCredentials = true;
    xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    xhr.onload = function ()
    {
        switch (xhr.status)
        {
            case 200:
            case 201:
                callback(xhr.responseText);
                ajaxRequest('GET', 'https://' + ajax.getIp() + ':' + ajax.getPort() + '/login?login:' + sessionStorage.getItem('login_teacher'), displayStudentsTable);
                break;
            default:
                httpErrors(xhr.status);
        }
    };
    xhr.send();
}

function setTokenCookie(token)
{
    Cookies.set('token', token, {expires: 1/48}); //30min
}

function displayStudentsTable(response)
{
    $('#errors').html('');
    $('#page-top').html('<h1 class="d-flex align-items-center justify-content-center h-100">Welcome ' + sessionStorage.getItem('login_teacher') + '!</h1><div id="formChooseExamination"> <form id="top-form" class="form-inline d-flex align-items-center justify-content-center h-100"> </form> </div>');
    $('#center-div').html('<div class="panel panel-default"><br>\n' +
        '            <div class="panel-body text-center m-0 d-flex flex-column justify-content-center">\n' +
        '                <form>\n' +
        '                    <div class="form-group row justify-content-center">\n' +
        '                        <div class="col-lg-6">\n' +
        '                            <input type="text" class="form-control text-center" id="searchInput" onkeyup="searchTable()" placeholder="Search for names...">\n' +
        '<div class="form-group mr-2"><button id="correctPromotion" type="submit" class="btn btn btn-primary">Correct Promotion</button></div>' +
        '                        </div>\n' +
        '                    </div>\n' +
        '                </form>\n' +
        '                <table id="studentsTable" class="table table-striped">\n' +
        '                    <thead id="studentsTHead">\n' +
        '                    </thead>\n' +
        '                    <tbody id="studentsTBody">\n' +
        '                        <tr><td colspan="4" style="color: dodgerblue">Please select a promotion and a examination</td></tr>\n' +
        '                    </tbody>\n' +
        '                </table>\n' +
        '            </div>\n' +
        '    </div>');

    ajaxRequest('GET', 'https://' + ajax.getIp() + ':' + ajax.getPort() + '/promotion', displayPromotions);
    ajaxRequest('GET', 'https://' + ajax.getIp() + ':' + ajax.getPort() + '/examination?id_promotion:1&login_teacher:' + sessionStorage.getItem('login_teacher'), displayExaminations);

    document.getElementById('correctPromotion').addEventListener("click", function (event) {
        event.preventDefault();
        console.log('a');
        ajaxRequest('GET', 'https://' + ajax.getIp() + ':' + ajax.getPort() + '/correctionPromotion?id_examination:'+ sessionStorage.getItem('idExamination') + '&id_promotion:' + sessionStorage.getItem('idPromotion'), a);

    });
    document.getElementById("top-form").addEventListener("click", function(event)
    {
        event.preventDefault();
        let promotion = document.querySelector("#promotion > option:checked");
        let examination = document.querySelector("#examination > option:checked");
        sessionStorage.setItem("idPromotion", promotion.id);
        sessionStorage.setItem("idExamination", examination.id);
        $('#studentsTHead').html('<tr><th colspan="4">Students for the promotion '+ promotion.value +' and the ' + examination.value + '</th></tr>');
        ajaxRequest('GET', 'https://' + ajax.getIp() + ':' + ajax.getPort() + '/student?id_promotion:' + sessionStorage.getItem('idPromotion'), displayStudents);
    });
}