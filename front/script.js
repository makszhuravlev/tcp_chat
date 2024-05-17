const chatData = [
    {
        "id": 1,
        "name": "Лох лохов",
        "messages": [
            {"sender": "received", "text": "почему?"},
            {"sender": "sent", "text": "покачену"}
        ]
    },
    {
        "id": 2,
        "name": "Другой чат",
        "messages": [
            {"sender": "received", "text": "Привет!"},
            {"sender": "sent", "text": "Здравствуй!"}
        ]
    }
];

let currentChatId = 1;

function loadChatList() {
    const chatListElement = document.getElementById('chatList');
    chatListElement.innerHTML = '';

    chatData.forEach(chat => {
        const chatItem = document.createElement('div');
        chatItem.classList.add('chat-item');
        chatItem.setAttribute('data-chat-id', chat.id);

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
}

function loadChatMessages(chatId) {
    const messagesElement = document.getElementById('messages');
    messagesElement.innerHTML = '';

    const chat = chatData.find(c => c.id === chatId);

    if (chat) {
        chat.messages.forEach(message => {
            const messageContainer = document.createElement('div');
            messageContainer.textContent = message.text;
            if (message.sender === "received") {
                messageContainer.classList.add('message', 'message-received');
            } else if (message.sender === "sent") {
                messageContainer.classList.add('message', 'message-sent');
            }

            messagesElement.appendChild(messageContainer);
        });
    }
    scrollToBottom();
}

function sendMessage() {
    const input = document.getElementById('messageInput');
    const message = input.value.trim();

    if (message !== '') {
        const chat = chatData.find(c => c.id === currentChatId);

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