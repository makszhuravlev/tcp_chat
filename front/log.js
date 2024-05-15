document.getElementById('loginForm').addEventListener('submit', function(event) {
    event.preventDefault();
    const username = document.getElementById('loginUsername').value;
    const password = document.getElementById('loginPassword').value;
    // формирование json
    const data = {
        type: 'log',
        username: username,
        password: password
    };
    // отправка
    fetch('URL_TO_LOGIN_API', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json' 
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
});
