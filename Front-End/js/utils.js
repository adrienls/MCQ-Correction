// https://www.w3schools.com/howto/howto_js_filter_table.asp
function searchTable()
{
    let input = document.getElementById("searchInput");
    let filter = input.value.toUpperCase();
    let table = document.getElementById("studentsTable");
    let tr = table.getElementsByTagName("tr");

    let td, txtValue;
    for (let i = 0; i < tr.length; i++) {
        td = tr[i].getElementsByTagName("td")[1];
        if (td) {
            txtValue = td.textContent || td.innerText;
            if (txtValue.toUpperCase().indexOf(filter) > -1) {
                tr[i].style.display = "";
            } else {
                tr[i].style.display = "none";
            }
        }
    }
}

function signout()
{
    Cookies.remove('token');
    sessionStorage.clear();
    document.location.href="index.html";
}
