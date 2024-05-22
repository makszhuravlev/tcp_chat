let username = sessionStorage.getItem('username');
let password = sessionStorage.getItem('password');
let CURRCHID = null;
console.log(username, password);
console.log(username, password);
let smski = null;


function startNonBlockingLoop() {
    // Use setInterval to call a function every 1000 milliseconds (1 second)
    const intervalId = setInterval(() => {
        console.log('This runs every second without blocking the UI.');
        loadChatMessages()
        // Perform your operations here
    }, 1000);

    return intervalId;
}

const loopId = startNonBlockingLoop();



let currentChatId = null;
var socket = new WebSocket('ws://217.197.240.93:8080');
        socket.addEventListener('open', function (event) {
        console.log('Connected to WS Server');
        
        var jsonData = {
            type: 4,
            username: username,
            password: password
        };
        
        var jsonString = JSON.stringify(jsonData);
        
        console.log("Sending:", jsonString);
        socket.send(jsonString);

        

        socket.addEventListener('error', function (event) {
            console.error('WebSocket error: ', event);
            document.getElementById("error").textContent="Ошибка соединения с сервером";
        });
    });

    
function loadChatList() {

    const chatListElement = document.getElementById('chatList');
    chatListElement.innerHTML = '';
    socket.addEventListener('message', function (event) {
        console.log('Message from server:', event.data);
        const response = JSON.parse(event.data);
        chats = response;     
        chats.forEach(chat => {
            const chatItem = document.createElement('div');
            chatItem.classList.add('chat-item');
            chatItem.setAttribute('data-chat-id', chat.chat_id);
    
            const chatAvatar = document.createElement('div');
            chatAvatar.classList.add('chat-avatar');
    
            const chatInfo = document.createElement('div');
            chatInfo.classList.add('chat-info');
    
            const chatName = document.createElement('div');
            chatName.classList.add('chat-name');
            chatName.textContent = chat.name;
    
            chatInfo.appendChild(chatName);
            chatItem.appendChild(chatAvatar);
            chatItem.appendChild(chatInfo);
    
            chatItem.addEventListener('click', () => {
                currentChatId = chat.id;
                loadChatMessages();
                CURRCHID = chat.chat_id;
                console.log(chat.chat_id);
                
                

            });
    
            chatListElement.appendChild(chatItem);
        });
    });


    
}
function loadChatMessages() {
    
    var socket = new WebSocket('ws://217.197.240.93:8080');
    socket.addEventListener('open', function (event) {
    console.log('Connected to WS Server');
    
    var jsonData = {
        type: 1,
        password:password,
        chatID: CURRCHID,
        username: username
    };
    
    
    var jsonString = JSON.stringify(jsonData);
    
    console.log("Sending:", jsonString);
    socket.send(jsonString);
});
    socket.addEventListener('message', function (event) {
        const messagesElement = document.getElementById('messages');
        messagesElement.innerHTML = '';
        smski = JSON.parse(event.data)
        JSON.parse(event.data).forEach(element => {
            const messageContainer = document.createElement('div');
            messageContainer.textContent = element["content"];
            if (element["author_id"] === username) {
                console.log(11)
                messageContainer.classList.add('message', 'message-sent');
            } else{
                messageContainer.classList.add('message', 'message-received');
            }

            messagesElement.appendChild(messageContainer);
        });

    });

    scrollToBottom();
    socket.addEventListener('error', function (event) {
        console.error('WebSocket error: ', event);
        document.getElementById("error").textContent="Ошибка соединения с сервером";
    });
  
}

    
function sendMessage() {
    const input = document.getElementById('messageInput');
    const message = input.value.trim();
    if (message !== '') {

        var socket = new WebSocket('ws://217.197.240.93:8080');
        socket.addEventListener('open', function (event) {
        console.log('Connected to WS Server');
        
        var jsonData = {
            type: 2,
            password:password,
            message: message,
            chatID: CURRCHID,
            username: username
        };
        
        var jsonString = JSON.stringify(jsonData);
        
        console.log("Sending:", jsonString);
        socket.send(jsonString);

        const messageContainer = document.createElement('div');
        messageContainer.classList.add('message', 'message-sent', 'sent');
        messageContainer.textContent = message;

        document.querySelector('.messages').appendChild(messageContainer);
        input.value = '';
        input.focus();
        document.getElementById('messageInput').value = '';
        console.log("hui piska")
        scrollToBottom();
    });

        socket.addEventListener('error', function (event) {
            console.error('WebSocket error: ', event);
            document.getElementById("error").textContent="Ошибка соединения с сервером";

        });
        const chat = CURRCHID
        

}
}



function scrollToBottom() {
    const messagesElement = document.getElementById('messages');
    messagesElement.scrollTop = messagesElement.scrollHeight;
}

document.getElementById('sendButton').addEventListener('click', sendMessage);

document.getElementById('messageInput').addEventListener('keydown', function(event) {
    if (event.key === 'Enter' && !event.shiftKey) {
        event.preventDefault();
        sendMessage();
    }
});
document.getElementById('chatinput').addEventListener('keydown', function(event) {
    if (event.key === 'Enter' && !event.shiftKey) {
        sendReqNewChat();
    }
});

document.getElementById('sendButtonChat').addEventListener('click', sendReqNewChat);

function sendReqNewChat(){
    var socket = new WebSocket('ws://217.197.240.93:8080');
        socket.addEventListener('open', function (event) {
            console.log('Connected to WS Server');
            
            var jsonData = {
                type: 3,
                username: username,
                password: password,
                members:[username, document.getElementById('chatinput').value.trim()],
                name:document.getElementById('chatinputName').value.trim()
            };
            
            var jsonString = JSON.stringify(jsonData);
            
            console.log("Sending:", jsonString);
            socket.send(jsonString);
            console.log(event.data + "+++++++++++++")
            
    
            socket.addEventListener('error', function (event) {
                console.error('WebSocket error: ', event);
                document.getElementById("error").textContent="Ошибка соединения с сервером";
            });
            window.location.assign('main.html')
        });
        
        event.preventDefault();
        
    }

window.onload = function() {
    loadChatList();
    loadChatMessages();
};

document.getElementById('settingsButton').addEventListener('click', function() {
    document.getElementById('settingsModal').style.display = 'flex'; 
});

document.querySelector('.close-button').addEventListener('click', function() {
    document.getElementById('settingsModal').style.display = 'none';
});


// Закрывает модальное окно при клике вне его
window.onclick = function(event) {
    if (event.target == document.getElementById('settingsModal')) {
        document.getElementById('settingsModal').style.display = 'none';
    }
}
