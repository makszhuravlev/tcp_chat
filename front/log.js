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

    socket.addEventListener('message', function (event) {
        console.log('Message from server ', event.data);
        const response = JSON.parse(event.data);
        if (event.data === "true") {
            console.log('забавный челик проходи')
        }
        if (event.data === "false") {
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
        document.getElementById("error").textContent="Ошибка соединения с сервером";

    });


    socket.addEventListener('close', function (event) {
        console.log('WebSocket connection closed: ', event);
    });
});
