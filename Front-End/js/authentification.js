function ajaxLogin(type, request, callback, login ,password, data = null)
{
    var xhr;
    // Create XML HTTP request.
    xhr = new XMLHttpRequest();
    xhr.open(type, request, true);
    xhr.setRequestHeader('Authorization','Basic ' + btoa(login +':'+ password));

    // Add the onload function.
    xhr.onload = function ()
    {
        switch (xhr.status)
        {
            case 200:
            case 201:
                callback(xhr.responseText);
                ajaxRequest('GET', 'php/request.php/login/', isConnected);
                break;
            default:
                httpErrors(xhr.status);
        }
    };
    // Send XML HTTP request.
    xhr.send(data);
}

function setTokenCookie(token)
{
    Cookies.set('token', token);
}

function validateLogin(event) {
    event.preventDefault();
    let login = document.getElementById('login').value;
    let password = document.getElementById('password').value;
    ajaxLogin('GET', 'php/request.php/authenticate/', setTokenCookie, login, password);
}

function isConnected()
{
    $('#errors').html('');
    $('#connect').html('<div class="alert alert-success text-center" role="alert"> Your are connected! </div>');
    //setTimeout(1000, $('#connect').html('') );
    ajaxRequest('GET', 'php/request.php/groups/', displayGroups);
}


// verify user is connected
ajaxRequest('GET', 'php/request.php/login/', isConnected);
document.getElementById('authentication-send').onclick = validateLogin;

