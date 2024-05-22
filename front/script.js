let username = sessionStorage.getItem('username');
let password = sessionStorage.getItem('password');
console.log(username, password);
console.log(username, password);


let currentChatId = 1;
var socket = new WebSocket('ws://localhost:8080');
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
                loadChatMessages(currentChatId);
            });
    
            chatListElement.appendChild(chatItem);
        });
    });


    
}
function loadChatMessages(chatId) {
    var socket = new WebSocket('ws://localhost:8080');
    socket.addEventListener('message', function (event) {
        console.log('Message from server ', event.data);
        const response = event.data;
        response.forEach(message => {
            console.log(message.content);
            const messageContainer = document.createElement('div');
            messageContainer.textContent = message.content;
            if (message.author_id === username) {
                messageContainer.classList.add('message', 'message-sent');
            } else{
                messageContainer.classList.add('message', 'message-received');
            }

            messagesElement.appendChild(messageContainer);
        });

    });

    scrollToBottom();
}

function sendMessage() {
    const input = document.getElementById('messageInput');
    const message = input.value.trim();

    if (message !== '') {
        const chat = chatData.find(c => c.id === currentChatId);
        console.log(input)
        if (chat) {
            chat.messages.push({"sender": "sent", "text": message});

            const messageContainer = document.createElement('div');
            messageContainer.classList.add('message', 'message-sent', 'sent');
            messageContainer.textContent = message;

            document.querySelector('.messages').appendChild(messageContainer);
            input.value = '';
            input.focus();
            
            scrollToBottom();
        }
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
    var socket = new WebSocket('ws://localhost:8080');
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
    loadChatMessages(currentChatId);
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
