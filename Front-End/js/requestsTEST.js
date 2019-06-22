ajaxRequest('GET', 'https://localhost:8080/login', test); // verify user is connected

function test(response) {
    console.log(response);
}