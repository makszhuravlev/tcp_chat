document.getElementById('registerForm').addEventListener('submit', function(event) {
    event.preventDefault();
    const password = document.getElementById('registerPassword').value;
    const confirmPassword = document.getElementById('confirmPassword').value;
    const errorMessage = document.getElementById('error');

    if (password !== confirmPassword) {
        errorMessage.textContent = 'Пароли не совпадают';
    } else {
        errorMessage.textContent = '';
        // Продолжить регистрацию
        console.log('Регистрация прошла успешно');
        // Здесь можно добавить код для отправки данных формы на сервер
    }
});