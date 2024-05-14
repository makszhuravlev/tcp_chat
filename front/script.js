document.getElementById('sendButton').addEventListener('click', function() {
    const input = document.getElementById('messageInput');
    const message = input.value.trim();

    if (message !== '') {
        const messageContainer = document.createElement('div');
        messageContainer.classList.add('message', 'sent');
        messageContainer.textContent = message;

        document.querySelector('.messages').appendChild(messageContainer);
        input.value = '';
        input.focus();
    }
});
