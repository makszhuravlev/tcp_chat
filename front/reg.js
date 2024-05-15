document.getElementById('registerForm').addEventListener('submit', function(event) {
    event.preventDefault();
    const username = document.getElementById('registerUsername').value;
    const email = document.getElementById('email').value;
    const password = document.getElementById('registerPassword').value;
    const confirmPassword = document.getElementById('confirmPassword').value;
    const errorMessage = document.getElementById('error');

    if (password !== confirmPassword) {
        errorMessage.textContent = 'Пароли не совпадают';
    } else {
        errorMessage.textContent = '';
        // формирование json
        const data = {
            type:'reg',
            username: username,
            email: email,
            password: password
        };
        console.log('Отправка данных регистрации:', JSON.stringify(data));
        // отправка
        fetch('URL_TO_REGISTER_API', {
            method: 'POST',
            headers: {
            },
            body: JSON.stringify(data)
        })
        // проверка 
        .then(response => response.json())
        .then(data => {
            console.log('Успех:', data);
        })
        .catch((error) => {
            console.error('Ошибка:', error);
        });
    }
});
