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
        var socket = new WebSocket('ws://217.197.240.93:8080');

        socket.addEventListener('open', function (event) {

            var jsonData = {
                type: 0,
                username: username,
                email: email,
                password: password
            };
            
            var jsonString = JSON.stringify(jsonData);
            
            socket.send(jsonString);
        });

        socket.addEventListener('message', function (event) {
            console.log('Message from server ', event.data);
            const response = JSON.parse(event.data);
            if (event.data === "true") {
                window.location.assign('main.html')
                sessionStorage.setItem('username', username);
                sessionStorage.setItem('password', password);
                console.log('забавный челик проходи');
            }
            else if (event.data === "false") {
                console.log('отказ')
            } 
            else {
                console.log('ЕБАТЬ КОПАТЬ')
                console.log(event.data)
            }
        });

        socket.addEventListener('error', function (event) {
            console.error('WebSocket error: ', event);
            alert("Ошибка соединения с сервером. Попробуйте ещё раз или зайдите позже!");
        });
        socket.addEventListener('close', function (event) {
            console.log('WebSocket connection closed: ', event);
        });
    }
});