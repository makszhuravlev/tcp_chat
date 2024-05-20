document.getElementById('loginForm').addEventListener('submit', function(event) {
    event.preventDefault();
    const username = document.getElementById('loginUsername').value;
    const password = document.getElementById('loginPassword').value;
    localStorage.setItem('username', username);
    localStorage.setItem('password', password);
    // формирование json
        var socket = new WebSocket('ws://localhost:8080');
        socket.addEventListener('open', function (event) {
        console.log('Connected to WS Server');
        
        var jsonData = {
            type: 1,
            username: username,
            password: password
        };
        
        var jsonString = JSON.stringify(jsonData);
        
        console.log("Sending:", jsonString);
        socket.send(jsonString);
        
    });

    
    socket.addEventListener('error', function (event) {
        console.error('WebSocket error: ', event);
        alert("Ошибка соединения с сервером. Попробуйте ещё раз или зайдите позже!");
        document.getElementById("error").textContent="Ошибка соединения с сервером";

    });


    socket.addEventListener('close', function (event) {
        console.log('WebSocket connection closed: ', event);
    });
});
