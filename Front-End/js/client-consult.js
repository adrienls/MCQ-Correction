function displayStudent() {
    $('#studentInformations').html('<div class="card"> firstName lastName - promotionName - examinationName </div>');
    console.log(Cookies.get());
}

displayStudent();