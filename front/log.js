document.getElementById('loginForm').addEventListener('submit', function(event) {
    event.preventDefault();
    const username = document.getElementById('loginUsername').value;
    const password = document.getElementById('loginPassword').value;
    // формирование json
        var socket = new WebSocket('ws://localhost:8080');
        socket.addEventListener('open', function (event) {
        console.log('Connected to WS Server');
        
        // Prepare JSON data to send
        var jsonData = {
            type: 1,
            username: username,
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
            errorMessage.textContent = 'Вы успешно вошли в систему';
        } else {
            errorMessage.textContent = response.message;
        }
    });

    socket.addEventListener('error', function (event) {
        console.error('WebSocket error: ', event);
        alert("Ошибка соединения с сервером. Попробуйте ещё раз или зайдите позже!");
        document.getElementById("error").textContent="Ошибка соединения с сервером";

    });

    // это самый гениальный комит
    socket.addEventListener('close', function (event) {
        console.log('WebSocket connection closed: ', event);
    });
});
