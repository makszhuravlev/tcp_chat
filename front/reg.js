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
        var socket = new WebSocket('ws://localhost:8080');

        socket.addEventListener('open', function (event) {
            console.log('Connected to WS Server');
            
            // Prepare JSON data to send
            var jsonData = {
                type: 0,
                username: username,
                email: email,
                password: password
            };
            
            var jsonString = JSON.stringify(jsonData);
            
            console.log("Sending:", jsonString);
            socket.send(jsonString);
        });

        socket.addEventListener('message', function (event) {
            console.log('Message from server ', event.data);
            const response = JSON.parse(event.data);
            if (response.success) {
                errorMessage.textContent = 'Регистрация успешна';
            } else {
                errorMessage.textContent = response.message;
            }
        });

        socket.addEventListener('error', function (event) {
            console.error('WebSocket error: ', event);
            errorMessage.textContent = 'Ошибка соединения с сервером';
        });

        socket.addEventListener('close', function (event) {
            console.log('WebSocket connection closed: ', event);
        });
    }
});