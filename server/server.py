import asyncio
import websockets
import json
import psycopg2

# Database connection parameters
DB_HOST = 'localhost'
DB_NAME = 'chat'
DB_USER = 'nyashka'
DB_PASSWORD = 'cmd'

def connect_to_db():
    conn = None
    try:
        conn = psycopg2.connect(
            host=DB_HOST,
            dbname=DB_NAME,
            user=DB_USER,
            password=DB_PASSWORD
        )
        print("Connected to PostgreSQL database")
    except Exception as e:
        print(f"An error occurred: {e}")
    return conn

async def handle_message(websocket, path):
    async for message in websocket:
        # Attempt to decode the message as JSON
        try:
            data = json.loads(message)
            print(f"Received JSON message: {data}")
            
            # Check for a specific action in the JSON message
            if data.get('action') == 'query':
                conn = connect_to_db()
                cursor = conn.cursor()
                
                # Example query: Select all rows from a table named 'messages'
                cursor.execute("SELECT * FROM chats")
                rows = cursor.fetchall()
                
                # Print the results
                for row in rows:
                    print(row)
                    
                cursor.close()
                conn.close()
        except json.JSONDecodeError:
            print(f"Received non-JSON message: {message}")

start_server = websockets.serve(handle_message, "localhost", 8080)

asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()

